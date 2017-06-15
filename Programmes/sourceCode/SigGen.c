
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <stdio.h>
#include "parsing.h"



//this application creates a signal from the parameters in the input file and sends it to the next application as output


int main()
{

//initialization of the input parameters
	float A = 0; //amplitude of the signal
	float phase=0; //phase of the signal
	float fe=0; //sampling frequency
	float f=0; //signal frequency
	int n=0; //number of data point
	int signal = 0; //type of signal 
	int error = 0;
	float *dataArray= NULL; //where the input signal will be



//initialization of local parameters
	const double PI = 3.14159265358979323846;
	float t = 0;
	int k = 0 ;
     
	


//recuperation of input parameters
FILE* input;
	input = stdin;
			if(input==NULL)
			{
			   printf("stdin not found\n");
			}
			else
			{
				input_SigGen(input,&signal, &phase, &f, &A, &fe, &n, &error);
			}
		    fclose(input);




// Creation of the signal
		    dataArray = init_tab(n);

		    k = 0;
		    t = 0;


//type 1 signal
  if (signal == 1)
  {
	 for (k = 0;k<n;k++)
	 {
		 dataArray[k]=A*sin(2*PI*f*t+phase);
		 t=t+1.0/fe;
	 }
  }




//type 2 signal
  else if (signal == 2)
  {
	  for (k = 0;k<n;k++)
 	 {

 		 if (A*sin(2*PI*f*t+phase)>=0)
 		 {dataArray[k]=A;}
 		 else
 		 {dataArray[k]=-A;}
 		 t=t+1.0/fe;
 	 }
  }


//type 3 signal
  else if (signal == 3)
    {
	     for (k = 0;k<n;k++)
	  	 {
	  		 if (sin(2*PI*f*t+phase)==1)
	  		 {dataArray[k]=A;}
	  		 else
	  		 {dataArray[k]=0;}
	  		 t=t+1.0/fe;
	  	 }
    }



// the signal is sent to the next application
  if (error == 0)
   {
       output_Data(dataArray,n,"stdout");
   }




  return 0;
}
