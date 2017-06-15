#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <stdio.h>
#include "parsing.h"


//this application creates a gain and an offset from the parameters in the input file and adds them to the signal
// the result is sent to the next application 



int main()

{   

//initialization of input parameters
	float gain= 0;
	float offset= 0;
	int error=0;
	int nbData = 0; //number of data point
	float *dataArray= NULL; //where the input signal will be


//initialization of local parameters
	int i = 0;
	


// recuperation of input parameters
		FILE* input;
		input=stdin;
		if(input==NULL)
		{
		printf("File not found\n");
		}
		else
		{

		     dataArray = input_SigAmp (input,&gain, &offset,&error,&nbData) ;


		}
	    fclose(input);





		  // amplification of the input signal

    for (i=0;i<nbData;i++)
     {


		 		dataArray[i] = (dataArray[i] + offset)*gain;

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
