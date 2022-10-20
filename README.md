# matlabfem
##### Author: Abhijith B N
##### email : abhijithbn@gmail.com
### MATLAB based Finite element solver and Stochastic FEM solver for electromagnetics. Nedelec edge based finite element for 3D, specral stochastic FEM, stochastic collocation and Monte Carlo simulation.
> created for the PhD thesis, "Stochastic Finite Element Modeling of Material and Geometric Uncertainties in Electromagnetics"
> The codes will be publisized after publication.

Usage Notes:
-------------------------------------- 
addpath 'emsfem/include' folder before executing the codes.

If 'buildKLMatrices' throws error due to incompatible c/c++ runtime libs, please recompile 'buildKLMatrices.c' using mex.

Features
------------------------------------
Designed MATLAB Finite Element Tool for Elecctormagnetics.

Designed as a class EFEM, the fundamental finite element code.

Designed as a class SFEM, the stochastic FEM extension of EFEM.

Designed as a class SSFEM, the spectral stochastic FEM extension of SFEM.

Designed as a class MonteCarlo, the Monte Carlo Simulation extension of SFEM.

Designed as a class SC, the Stochastic Collocation implementation.

Designed as a class StochasticCollocation, the Stochastic Collocation Simulation extension of SFEM.

Tested Features
------------------
1. Determniistic EFEM								Tested
2. Stochastic FEM
	* SSFEM
		- random variable						Tested
		- spatial variation						Tested
		- effective spatial variation					Tested
	* MCS
		- random variable						Tested	
		- spatial variation						Tested
		- effective spatial variation					Tested
	* SC
		- random variable						NOT tested
		- spatial variation						Tested
		- effective spatial variation					NOT tested	
