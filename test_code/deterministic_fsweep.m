addpath('../include');
addpath(path);

fem = EFEM;

freq = linspace(10.5,11.7,100);
trans = fem.fsweep('./models/Iris_Filter', 1, freq);
plot(freq,trans);