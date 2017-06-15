/*
 * SigPlot.c
 *
 *  
 *     
 */

//this application takes the input configuration file and copy it on a text file
//it also retreive the necessary plot parameters, format them, and send them to the GnuPlot application

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <stdio.h>
#include "parsing.h"



//parameters initialization
char x_label[100] = {}; //label of the x axis
char y_label[100] = {}; //label of the y axis
char title[100]= {};  //title
char scale[100] = {};  //scale of the plot

char shape[100] = {};  //shape (lines, point, asterix)
char color[100] = {};  //color used for the plot
char image_type[100] = {}; // jpg, bmp
char image_name[100] = {};
char Out[] = {100}; // name of the output text file
int error=0;
int nbData=0; //number of data point
float *dataArray= NULL;



// recuperation of input parameters
int main(int argc, char *argv[])
{


		FILE* input;
		input = stdin; 
		if(input==NULL)
		{
		   printf("stdin not found\n");
		}
		else
		{
			dataArray = input_SigPlot (input,title,x_label,y_label,image_name,Out,scale,shape,color,image_type,&error,&nbData) ;
		}
	    fclose(input);







//we send the parameters to GnuPlot (stdout)


if (strcmp(image_type,"jpg") == 0)
{
	sscanf("jpeg","%s",image_type);

}



	         printf("set xlabel \"%s\"\n",x_label);
	         printf("set ylabel \"%s\"\n",y_label);
	         printf("set title \"%s\"\n",title);
	         printf("set term \"%s\"\n",image_type);
	         printf("set output \"%s.%s\"\n",Out,image_type);
	         printf("plot '-' with lines lt rgb \"%s\"\n",color);

	         int i=0;
	                 for (i=0;i<nbData;i++)
	                 {
	                 printf("%f\n", dataArray[i]);
	                 }

	                 		printf("e");

	                 		
// we write the data in the text file
             if (error == 0)
             {
            	 output_Data(dataArray,nbData,Out);
             }



	    free(dataArray);
		dataArray= NULL;
	return 0;

}

