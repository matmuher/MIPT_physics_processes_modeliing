# Oscillator modelling

## What?

This is project for tasks of numerical simulation course (MIPT).

Here we numerically simulate systems, that are set by differential equations.

## Methods

Next methods for solving differential equations are used:

+ Heun
+ Euler
+ RK4

Comparision of this methods with analytical solution can be found here: [report for solvers comparison](solvers.md)

## Systems

Next systems are considered:

+ harmonic oscillator
+ damped oscillator
  + [Report about damped oscillator](damped.md)
+ damped driven oscillator
  + [General driven oscillator overview](driven.md)
  + [AFC for driven oscillator](AFC.md)
+ Double pendulum oscillator (soon...)
+ Kapitsy oscillator (soon...)

## Architecture

Project consists of 2 parts:

1. Simulator

As simulating is computationally expensive task, simulator is written in C++.

Features:

+ Easy to add new models and solvers (OOP design)
+ Easy to switch between float, double etc type values (templates)
+ Configurable from json file

Hierchahy is rather unstable at the moment. I'll dump it in the winter vacations.

2. Analyizer

Core modules for plotting and working with config files are moved to python modules. But analyze process is held in jupiter notebook, as it allows faster iterations.

It's used to research system's features:
+ Veloctiy and coordinates
+ Energy
+ AFC
+ Phase diagrams
