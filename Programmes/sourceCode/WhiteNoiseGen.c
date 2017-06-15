#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <stdio.h>
#include "parsing.h"

//this application produces a  white noise from the parameters in the input file and adds it to the signal
// the result is sent to the next application 


int main()

{   

	//initialization of input parameters
	float amp= 0;// amplitude
	int seed= 0;// seed for srand function
	int error=0;
	int nbData = 0; //number of data point
	float *dataArray= NULL; //where the input signal will be

	//initialization of local parameters
	int i = 0;
	float BB = 0;;
	float var = 0;

// recuperation of input parameters
		FILE* input;
		input=stdin;
		if(input==NULL)
		{
		printf("File not found\n");
		}
		else
		{
		     
		     dataArray = input_WhiteNoiseGen (input,&amp, &seed,&error,&nbData) ;


		}
	    fclose(input);





//noise production and addition to the signal
	srand(seed);

    for (i=0;i<nbData;i++)
     {
		 		 var=(double)rand()/(double)RAND_MAX;

		 		 BB= amp*(2*var-1);

		 		dataArray[i] = dataArray[i] + BB;

     }

//the result is sent to the next application
    if (error == 0)
    {
    output_Data(dataArray,nbData,"stdout");
    }


    free(dataArray);
    dataArray= NULL;
  return 0;
}
