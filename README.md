# knapsack-problem 01
Solved Knapsack problem 01 by backtracking, Dynamic Programming and Meet-in-the-Middle

## Table of contents
* [General info](#general-info)
* [Setup](#setup)

## General info
There are different solutions for Knapsack Problem 01: 
- Brute Force
- Backtracking
	- Naive
	- Optimality Cuts
	- Feasibility Cuts
- Meet in the Middle
- Dynamic Programming

Presented as part of a project for Algorithms and Data Structures III.

## Setup
To run this project, choose a posible resolutions res in {fb, bt,bt-ftb,bt-opt, bt-doublecut, bt-iter-bfs, bt-iter-dfs, mitm, dp}:

```
$ make
$ ./main res < sample.in
```

## test
To run minitest, choose a Capacity W and run:

```
$ make
$ ./runMiniTest.sh W
```
