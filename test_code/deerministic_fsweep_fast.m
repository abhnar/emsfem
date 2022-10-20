addpath('../include');

fem = EFEM;

freq = linspace(10.5,11.7,200);
trans = fem.fsweep_fast('./models/Iris_Filter', 1, freq);
plot(freq,trans);
xlabel('Frequency (GHz)');
ylabel('|S_{21}|');