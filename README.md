# Space--, a monochrome space exploration game

## About

This is a game I'm doing to practice in C++. The goal is to do something resembling the original Elite (1984).

Work in progress. This document will be updated.

## Compilation from source

```
git clone git@github.com:k-kashapov/Space-.git
cd Space-
mkdir build
cd build
cmake -B . .. -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
make
```

## Running the game
```
make launch
OR
./bin/game
```

## Controls

```
Q/R - Control Yaw
W/S - Control Pitch
A/D - Control Roll
R/F - Accelerate/Decelerate ship
P   - Pause the game
```

## Used resources

* Font: https://fontesk.com/tecnica-typeface/
* SFML
