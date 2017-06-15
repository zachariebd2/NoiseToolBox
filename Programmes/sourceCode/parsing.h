

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>



#ifndef PARSING_H_
#define PARSING_H_

//principal functions
void input_SigGen(FILE *input,int *, float *, float *, float *, float *, int *,int *);
float *input_SigAmp(FILE *input,float *,float *,int *,int *);
float *input_WhiteNoiseGen(FILE *input,float *,int *,int *,int *);
float *input_GaussianNoiseGen(FILE *input,float *,float *,int *,int *,int *);
float *input_SigPlot(FILE *input,char *,char *,char *,char * ,char *,char *,char *,char *,char *,int *,int *);
void output_Data(float *,int,char * );



//secundary functions
void lower_string(char*);
int isFloat(char*);
int isInt(char*);
int param_float(char*, char*, float *,int,int * );
int param_int(char* , char* , int *, int , int *);
float *init_tab(int n);
int param_stringWithQuotes(char* , char* , char **, int , int *);
int isStringWithQuotes(char*) ;

#endif /* PARSING_H_ */



