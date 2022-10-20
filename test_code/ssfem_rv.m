%% Initialize library
addpath('../include');

ssfem = SSFEM;

ssfem.verbose = 0;
ssfem.LoadMesh('./models/Multi_Dielectric');
ssfem.meshStatistics();
Mat = [1, 9-0.018j, 6-0.012j, 6-0.012j, 6-0.012j, 1.2-0.0024j, 1.2-0.0024];

ssfem.setMaterials(Mat);
freq = linspace(2,4,100);
f = 2.5;

ssfem.init(100,'kle',false,'p_order',2);

ssfem.setSeed(1);
ssfem.assignRandomMaterialVariation([2 3 4], [0.8 0.5 0.4]);
ssfem.ssfemsimulation(f);

ssfem.plot('current')
