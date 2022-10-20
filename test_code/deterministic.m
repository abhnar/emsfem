%deterministic.m
addpath('../include');

fem = EFEM;

fem.LoadMesh('./models/Iris_Filter');

fem.meshStatistics()
fem.setMaterials(1);
fem.buildSystem();
f = 11.3;

fem.solve(f);
trans = fem.calcTrans();

fprintf('Trans at %2.2f GHz is %.4f\n', f, trans);
