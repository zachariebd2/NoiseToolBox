# noiseToolBox


The noise tool box is a serie of applications coded in C made to produce a signal, add different kinds of noise to it, and plot it according to a configuration file.

a command window is necessary to use the executable files. An example of the toolbox utilisation is:

cat test_noError.txt | SigGen.exe | WhiteNoiseGen.exe | GaussianNoiseGen.exe | SigAmp.exe | SigPlot.exe | gnuplot.exe


SigGen produce a new signal and ignore the one already written in the configuration file. If a signal is already written in the configuration file it is not necessary to call SigGen.

WhiteNoiseGen adds a white noise to an already existing signal and send the result to the next application. 

GaussianNoiseGen adds a gaussian noise to an already existing signal and send the result to the next application. 

SigAmp amplifies and adds an offset to an already existing signal and send the result to the next application. 

WhiteNoiseGen, GaussianNoiseGen and SigAmp can be called in different orders, or be called multiple times, or be left out.


SigPlot write a new configuration text file containing the resulting signal and sends plotting instructions to gnuplot 

gnuplot makes a plot of the resulting signal

gnuplot cannot be called  without SigPlot


IMPORTANT: I didn't do the gnuplot.exe application, it was given to me as is