%% Initialize library
clc;
clearvars;
addpath('../include');


mcs = MonteCarlo;

mcs.verbose = 0;
mcs.LoadMesh('./models/Multi_Dielectric');
mcs.meshStatistics();
Mat = [1, 9-0.018j, 6-0.012j, 6-0.012j, 6-0.012j, 1.2-0.0024j, 1.2-0.0024];

mcs.setMaterials(Mat);
mcs.buildSystem();

f = 2.5;

%% KLE Setup
kle = KLE3D;
kle.process(mcs,[2 3 4 ]);
kle.evaluate_Phi('nlambda',3);
kle.getKLEData(1);
kle.setSD([0.8 0.5 0.4]);
kle.setNKL([3 3 3]);

mcs.init(100,'kle',true);
mcs.setSeed(1);
mcs.assignEffectiveMaterialVariation(kle,'full');
mcs.MCSimulation(f);
mcs.plot('current');
