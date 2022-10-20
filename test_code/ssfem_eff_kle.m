%% Initialize library
addpath('../include');


ssfem = SSFEM;

ssfem.verbose = 0;
ssfem.LoadMesh('./models/Multi_Dielectric');
ssfem.meshStatistics();
Mat = [1, 9-0.018j, 6-0.012j, 6-0.012j, 6-0.012j, 1.2-0.0024j, 1.2-0.0024];

ssfem.setMaterials(Mat);
ssfem.buildSystem();

f = 2.5;

%% KLE Setup
kle = KLE3D;
kle.process(ssfem,[2  ]);
kle.evaluate_Phi('nlambda',10);
kle.getKLEData(0.5);
kle.setSD([0.8  ]);
kle.setNKL([3 ]);



ssfem.init(20000,'kle',true,'p_order',2);

ssfem.setSeed(1);
ssfem.assignEffectiveMaterialVariation(kle,'full');
ssfem.ssfemsimulation(f);
ssfem.plot('current');
hold on;