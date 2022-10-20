# matlabfem
## Author: Abhijith B N
## email : abhijithbn@gmail.com
## created for the PhD thesis, "Stochastic Finite Element Modeling of Material and Geometric Uncertainties in Electromagnetics"
## The codes will be publisized after publication.

Note:
-------------------------------------- 
addpath 'matlabfem/include' folder before executing the codes.

Features
------------------------------------
Designing MATLAB Finite Element Tool for Elecctormagnetics.

Designed as a class EFEM, the fundamental finite element code.

Designed as a class SFEM, the stochastic FEM extension of EFEM.

Designed as a class SSFEM, the spectral stochastic FEM extension of SFEM.

Designed as a class MonteCarlo, the Monte Carlo Simulation extension of SFEM.

Designed as a class SC, the Stochastic Collocation implementation.

Designed as a class StochasticCollocation, the Stochastic Collocation Simulation extension of SFEM.

Tested Features
------------------
Determniistic EFEM									Tested
Stochastic FEM
	SSFEM
		random variable								Tested
		spatial variation							Tested
		effective spatial variation					Tested
	MCS
		random variable								Tested	
		spatial variation							Tested
		effective spatial variation					Tested
	SC
		random variable								NOT tested
		spatial variation							Tested
		effective spatial variation					NOT tested	
