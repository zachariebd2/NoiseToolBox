#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <stdio.h>
#include "parsing.h"


//this application produces a gaussian noise from the parameters in the input file and adds it to the signal
// the result is sent to the next application 


//random value generator
double frand_a_b(double a, double b){
		double v=(double)rand()/(double)RAND_MAX ;
		double r=v* (b-a) + a;
		return ((double)rand()/(double)RAND_MAX ) * (b-a) + a;

	}

int main()
{   

//initialization of input parameters
    float Variance= 100;
    float Average= 10;    
    int Seed=1; //seed for srand
    int nbData=1; //number of data point
    int error=0;
    float *dataArray= NULL; //where the input signal will be
    


// recuperation of input parameters
		FILE* input;
		input=stdin;
		if(input==NULL)
		{
		printf("File not found\n");
		}
		else
		{

		dataArray = input_GaussianNoiseGen (input,&Average,&Variance, &Seed,&error,&nbData) ;
		}
	    fclose(input);



	// initialization of local parameters
	float BBG;
	float fe=0.2;// sampling frequency
	int n=20; // number of samples
	float var1;
	float var2;
	const double PI = 3.14;
	float r;
	int t=0;
int i = 0;


	
// we generate the gaussian noise and add it to the input signal
	srand(Seed);
	for (i = 0;i<nbData;i++)
	{
		// we stay in the interval [1,100]
		var1=frand_a_b(0,1);
		var2=frand_a_b(1,100);

		BBG= sqrt(-2*log(var1))*cos(2*PI*var2)*Variance+Average;
		dataArray[i] = dataArray[i] + BBG;

	}


// we send the resulting signal to the next application
	if (error == 0)
    {
    output_Data(dataArray,nbData,"stdout");
    }

	free(dataArray);
	dataArray= NULL;
	return 0;
}
