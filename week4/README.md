# Harmonic Oscillator Modelling

## What do you do here?

Research numerical methods of solving system of 1st order differential equations.

In this research next methods are compared:

+ [Analytical solution](https://en.wikipedia.org/wiki/Harmonic_oscillator)
+ [Euler method](https://en.wikipedia.org/wiki/Euler_method)
+ [Heun method](https://en.wikipedia.org/wiki/Heun%27s_method)

## Research solution

### Many samples
![](pictures/many_samples_solution.svg)

### Few samples

![](pictures/few_samples_solution.svg)


Euler method and Heun method are iterative processes that are used to get approximate solution.

As you can see on the pictures they do really approximate solution, but with an error.

Euler method increases amplitude of oscillations.
This fact can be observed better if we plot system energy.

## Research energy

### Many samples
![](pictures/many_samples_energy.svg)

### Few samples

![](pictures/few_samples_energy.svg)

Plot demonstrates that energy in the system increases.

But we model conservative system, so it's only called by error of Euler's method.

## Research phase portrait

### Many samples

![](pictures/many_samples_phase_diagram.svg)

### Few samples

![](pictures/few_samples_phase_diagram.svg)

Phase portrait of conservative system should look like a circle. But as Euler's method ruins energy balance we see unrolling spiral.

## Conclusions

For understanding results let's consider one more plot:

![](pictures/how_methods_deal_with_concave.svg)

This plots gives us answer. As initial solution function concaves greatly $A * sin(x) + b * cos(x)$ Euler's method does bad job.

Let's consider time samples with numbers 0 and 1. We will investigate solution for v. Initial value is 1. Original solution's v derivative smoothly decreases. But Euler's method take into account only derivative's value at start of time interval. And considers it constant for the whole interval. That's why Euler's solution is not goes enough down when we compare it with original solution in the end of interval.

Thus as velocity doesn't decrease properly it seems like energy in the system increases. That is proofed by plots in 'Research energy' section.

Otherwise, in Heun's method case it goes better. That's because Heun's method consider that function can concave. So the computed derivative depends on original derivative in both ends of time interval.
