# CarND-Controls-MPC
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
  * Used version: 3.8.2
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
  * Used version: 0.6.2 Beta
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
  * Windows: Refer to the section "Windows Install Instructions" [here](https://github.com/swirlingsand/CarND-PID-Control-Project)
* Fortran Compiler
  * Mac: `brew install gcc` (might not be required)
  * Linux: `sudo apt-get install gfortran`. Additionall you have also have to install gcc and g++, `sudo apt-get install gcc g++`. Look in [this Dockerfile](https://github.com/udacity/CarND-MPC-Quizzes/blob/master/Dockerfile) for more info.
* [Ipopt](https://projects.coin-or.org/Ipopt)
  * Mac: `brew install ipopt`
  * Linux
    * You will need a version of Ipopt 3.12.1 or higher. The version available through `apt-get` is 3.11.x. If you can get that version to work great but if not there's a script `install_ipopt.sh` that will install Ipopt. You just need to download the source from the Ipopt [releases page](https://www.coin-or.org/download/source/Ipopt/) or the [Github releases](https://github.com/coin-or/Ipopt/releases) page.
    * Then call `install_ipopt.sh` with the source directory as the first argument, ex: `bash install_ipopt.sh Ipopt-3.12.1`. 
  * Windows: Refer to the structure [here](https://github.com/3omdawy/MPC-Quiz)
* [CppAD](https://www.coin-or.org/CppAD/)
  * Mac: `brew install cppad`
  * Linux `sudo apt-get install cppad` or equivalent.
  * Windows: Refer to the structure [here](https://github.com/3omdawy/MPC-Quiz)
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page). This is already part of the repo so you shouldn't have to worry about it.
* Simulator. You can download these from the [releases tab](https://github.com/udacity/self-driving-car-sim/releases).
* Not a dependency but read the [DATA.md](./DATA.md) for a description of the data sent back from the simulator.


## Basic Build Instructions


1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
OR
4. Build the project "mpc.vcxproj" using Visual Studio 17 (should work normally using `cmake .. && make` but it did on Windows using the original files in the project directory. I used the files [here](https://github.com/swirlingsand/CarND-PID-Control-Project) after asking on [forum](https://discussions.udacity.com/t/cmake-error-libuv-include-dir-and-libuv-library-not-found/244251/5))
5. Open the simulator in autonomous mode
6. Run mpc.exe

## Model

* Exactly as in MPC quiz
* State: state vector consists of the following:
  * Position `x`
  * Position `y`
  * Orientation angle `psi`
  * Velocity `v`
  * Cross-Track Error `cte`
  * Orientation Error `epsi`
* Actuators: simulator accepts only the following actuators:
  * Steering angle `delta`
  * Throttle, modeled by acceleration `a`
* Update equations:
```
  * x_[t+1] = x[t] + v[t] * cos(psi[t]) * dt
  * y_[t+1] = y[t] + v[t] * sin(psi[t]) * dt
  * psi_[t+1] = psi[t] + v[t] / Lf * delta[t] * dt
  * v_[t+1] = v[t] + a[t] * dt
  * cte[t+1] = f(x[t]) - y[t] + v[t] * sin(epsi[t]) * dt
  * epsi[t+1] = psi[t] - psides[t] + v[t] * delta[t] / Lf * dt
```
  * Where `dt` is a tuned parameter representing the time between current and next prediction
  * Where `Lf` is length from front to CoG that has a similar radius
  * Where `f(x(t))` is the predicted `y` value according to the trajectory fitting polynomial
  * Where `psides` is the atan of the differential of `f(x(t))` with respect to `x`

## Parammeters Tuning

* `N` (timestep length): was set to 10 according to the [helper video](https://www.youtube.com/watch?v=bOQuhpz3YfU&feature=youtu.be)
  * Having a larger `N` is better to predict more points but it consumes longer time for computing actuators (number of parameters to optimize is proportional to `N`)
  * But having a larger `N` may also make the outcomes unpredictable because the optimizer may override controls that decrease cost in the near future to decrease cost in the far future
  * Other experimented value: 25 (like in MPC quiz)
* `dt` (elapsed duration between timesteps): was set to 0.1 according to the [helper video](https://www.youtube.com/watch?v=bOQuhpz3YfU&feature=youtu.be)
  * Having a small `dt` is better to predict for more recent times but it increases computations
  * Having a large `dt` is worse because it makes the systen slower
  * Other experimented value: 0.05 (like in MPC quiz)
* So, we predict 1s into the future

## Polynomial Fitting
* We have 6 way points given by the simulator, we fit a 3rd order polynomial as done in the [helper video](https://www.youtube.com/watch?v=bOQuhpz3YfU&feature=youtu.be) and in all discussions

## Preprocessing
* Preprocessing is done to convert from map coordinates to vehicle coordinates. This is done on 2 steps: Translate to car coordinate system then rotate to the car's orientation
```
x = ptsx[i] - px;
x = ptsx[i] - px;
ptsx[i] = (x * cos(psi) + y * sin(psi));
ptsy[i] = (-x * sin(psi) + y * cos(psi));
```
* Consequently, `x`, `y`, and `psi` are always 0 in the state vector passed to MPC solver

## Adding Latency
* To account for 100ms latency between prediction and applying of controls, the idea of xperroni in the [forum](https://discussions.udacity.com/t/how-to-take-into-account-latency-of-the-system/248671/13) was done by taking the model outputs at t + 1 not at t. Since `dt` = 0.1, t + 1 is t + 100ms

## Did it work?
* Honestly on my machine it did not work. I posted [this](https://discussions.udacity.com/t/stuck-moving-in-circles/272063/22) on forum, applied all the known solutions to me but nothing worked. I also got some code on Github from students that completed the project and also did not work on my laptop. I think my laptop may be the reason because it is extremely slow.

## Notes

1. It's recommended to test the MPC on basic examples to see if your implementation behaves as desired. One possible example
is the vehicle starting offset of a straight line (reference). If the MPC implementation is correct, after some number of timesteps
(not too many) it should find and track the reference line.
2. The `lake_track_waypoints.csv` file has the waypoints of the lake track. You could use this to fit polynomials and points and see of how well your model tracks curve. NOTE: This file might be not completely in sync with the simulator so your solution should NOT depend on it.
3. For visualization this C++ [matplotlib wrapper](https://github.com/lava/matplotlib-cpp) could be helpful.
