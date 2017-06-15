/*
 * parsing.c 
 * made according to specifications
 *
 *
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "parsing.h"


// the functions input_SigGen, input_SigAmp, input_WhiteNoiseGen and input_GaussianNoiseGen 
// they take as input a configuration file and the parameters whose values are decided by the configuration file
// they look for the sections which correspond to them and then look inside of those sections for the parameters
// they modify the input parameters with the value they find in the configuration file
// they send as output a new text file (for the next application)



//////////////////////////////////SIGGEN///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void input_SigGen(FILE *input,int *signal, float *phase, float *frequency, float *amplitude, float *sampling, int *nbSample, int *error)
{
    // text processing
    char buf[BUFSIZ] = {};     // this parameter will contain a whole line from the configuration file
    char *bufp = buf;          // this pointer will move along the line
    char secbuf[BUFSIZ] = {};  // this string will contain the whole section

    // markers
    int line =0;          // line number
    int Section =0;       // marker which tells if we are inside or outside the SigGen section
    int DataSection = 0;  // marker which tells if we are inside or outside the data section
    int isSection = 0;    // marker which tells if the SigGen section exists
    int p =0;             // marker which tells where we are on the line
    
    //those markers tell if a parameter has been read
    int signalMark = 0;   
    int phaseMark = 0;
    int frequencyMark = 0;
    int amplitudeMark = 0;
    int samplingMark = 0;
    int nbSampleMark = 0;
    
    // We read each lines until we find #BEGIN SigGen and #END SigGen
    while (fgets(buf, sizeof buf, input) != NULL)
    {
          line = line + 1;
          if ((strcmp(buf, "#BEGIN SigGen\n") == 0) & (Section == 0)) // if we read the #BEGIN line
          {
              Section = 1;
              isSection = 1;
              printf("%s",buf);
          }
          else if (((strcmp(buf, "#END SigGen\n") == 0 )|(strcmp(buf, "#END SigGen\0") == 0 ))& (Section == 1) ) // if we read the #END line
          {
          	  if (signalMark == 0) // if we didn't find the signal parameter
  	      	  {
  	      		    fprintf(stderr,"error in SigGen -> signal parameter missing\n"); // stderr
  	      		    *error = *error + 1;
  	      	  }
          	  if (phaseMark == 0) // if we didn't find the phase parameter
  	      	  {
  	      	      fprintf(stderr,"error in SigGen -> phase parameter missing\n"); // stderr
  	      	      *error = *error + 1;
  	      	  }
          	  if (frequencyMark == 0) // if we didn't find the frequency parameter
  	      	  {
  	      		    fprintf(stderr,"error in SigGen -> frequency parameter missing\n"); // stderr
  	      		    *error = *error + 1;
  	      	  }
          	  if (amplitudeMark == 0) // if we didn't find the amplitude parameter
  	      	  {
  	      	      fprintf(stderr,"error in SigGen -> amplitude parameter missing\n"); //en stderr
  	      	      *error = *error + 1;
  	      	  }
          	  if (samplingMark == 0) // if we didn't find the sampling frequency parameter
  	      	  {
  	      		    fprintf(stderr,"error in SigGen -> sampling_freq parameter missing\n"); //en stderr
  	      		    *error = *error + 1;
  	      	  }
          	  if (nbSampleMark == 0) // if we didn't find the sampling number parameter
  	      	  {
  	      	      fprintf(stderr,"error in SigGen -> n_sample parameter missing\n"); //en stderr
  	      	      *error = *error + 1;
  	      	  }
          	  if (*error == 0)  // if there is no error we write the section via stdout
          	  {
          		    printf("%s",secbuf); // stdout
          	  }
          	  else // if there is at least one error, we use default values for the section (according to the specifications)
          	  {
            		  printf("signal = sinus\nphase = 0\nfrequency = 0\namplitude = 0\nsampling_freq = 0\nn_sample = 1\n"); //stdout
            		  *signal = 1;
            		  *phase = 0;
            		  *frequency = 0;
            		  *amplitude = 0;
            		  *sampling = 0;
            		  *nbSample = 1;
          	  }
                  Section = 0; // end of the section
                  printf("%s",buf);  // we write the END line via stdout
          }
          else if ((strcmp(buf, "#BEGIN Data\n") == 0 )& (DataSection == 0) ) //if we read the BEGIN Data line
          {
              DataSection = 1;
          }
          else if ((Section == 0 ) & (DataSection == 0))  // if we read a line outside of the SigGen section and outside of the Data section
          {
              printf("%s",buf);
          }
          else if (Section == 1)  // if we read a line inside the Data section
          {
          	  if (strstr(buf, "%") == buf) //if we read a commented line
          	  {
          		    strcat(secbuf, buf);
          	  }
          	  else  // if we don't read a commented line
          	  {
          		    lower_string(buf); // we put everything in lower case
                 // here we look for for the signal parameters
          		    if ((strstr(buf, "signal") == buf) & (signalMark == 0))   // if the current line correspond to the signal parameter
        		      {
                      p = 0;
                      while (*bufp == ' ')   //we jump an unknown number of space
                      {
                        bufp = bufp + 1;
                        p = p + 1;
                      }
    		      		  	bufp = bufp + strlen("signal"); //we move the pointer to read the rest of the line
    		      		  	p =  p + strlen("signal");
    		      		  	while (*bufp == ' ')   //we jump an unknown number of space
    		      		  	{
    		      		  		bufp = bufp + 1;
    		      		  		p = p + 1;
    		      		  	}
    		      		  	if (*bufp == '=')    //we look for a '=' symbol
    		      		  	{
    		      		  	    bufp = bufp + 1;
    		      		  	    p = p + 1;
    		      		  		  while (*bufp == ' ')        //we jump an unknown number of space
    		      		  		  {
    		      		  			    bufp = bufp + 1;
    		      		  			    p = p + 1;
    		      		  		  }
    		      		  		  // we see if the line end with the sinus parameter
    		      		  		  if (strstr(bufp, "sinus") == bufp)
    		      		  		  {
    		      		  			    signalMark = 1;
                              bufp = bufp + strlen("sinus"); 
                              p =  p + strlen("sinus");
                              while (*bufp == ' ')   //we jump an unknown number of space
                              {
                                  bufp = bufp + 1;
                                  p = p + 1;
                              }
                              if (*bufp == '\n')
                              { 
        		      		  		      strcat(secbuf, buf);
                                  *signal = 1;
                              }
                              else
                              {
                                  fprintf(stderr,"signal error in line %d -> value absent or bad\n",line); //stderr
                                  *error = *error + 1;
                              }
    		      		  		  }
    		      		  		  // we see if the line end with the square parameter
    		      		  		  else if (strstr(bufp, "square") == bufp)
    		      		  		  {
        		      		  		  signalMark = 1;
                              bufp = bufp + strlen("square");
                              p =  p + strlen("square");
                              while (*bufp == ' ')   //we jump an unknown number of space
                              {
                                  bufp = bufp + 1;
                                  p = p + 1;
                              }
                              if (*bufp == '\n')
                              { 
                                  strcat(secbuf, buf);
                                  *signal = 2;
                              }
                              else
                              {
                                  fprintf(stderr,"signal error in line %d -> value absent or bad\n",line); //stderr
                                  *error = *error + 1;
                              }
    		      		  		  }
    		      		  		  // we see if the line end with the impulse parameter
    		      		  		  else if (strstr(bufp, "impulse") == bufp)
    		      		  		  {
        		      		  		  signalMark = 1;
                              bufp = bufp + strlen("impulse");
                              p =  p + strlen("impulse");
                              while (*bufp == ' ')   //we jump an unknown number of space
                              {
                                  bufp = bufp + 1;
                                  p = p + 1;
                              }
                              if (*bufp == '\n')
                              { 
                                  strcat(secbuf, buf);
                                  *signal = 3;
                              }
                              else
                              {
                                  fprintf(stderr,"signal error in line %d -> value absent or bad\n",line); //stderr
                                  *error = *error + 1;
                              }
    		      		  		  }
                          else   //if the parameter at the end of the line is not good
    		      		  		  {
        		      		  		  fprintf(stderr,"signal error in line %d -> value absent or bad\n",line); //stderr
        		      		  		  signalMark = 1;
        		      		  		  *error = *error + 1;
    		      		  		  }
    		      		  	}
                      else // if there is no "="
    		      		  	{
    		      		  	    fprintf(stderr,"signal error in line %d -> unreadable line\n",line); //stderr
    		      		  		  signalMark = 1;
    		      		  		  *error = *error + 1;
    		      		  	}
        		      		bufp = bufp - p;
        		      }
                  else if ((strstr(buf, "signal") == buf) & (signalMark == 1))   // if the parameter is defined more than once in the input configuration file
          		    {
          			      fprintf(stderr,"error at line %d -> signal parameter already called\n",line); //stderr
          			      *error = *error + 1;
          		    }
          		    
                  // we look for the phase parameter
          		    else if((strstr(buf, "phase") == buf) & (phaseMark == 0))
          		    {
          			      *error = *error + param_float(buf, "phase", &*phase,line,&phaseMark);
          			      if (*error == 0)
                      {
          			    	    strcat(secbuf, buf);
          			    	}
          		    }
                  else if ((strstr(buf, "phase") == buf) & (phaseMark == 1))   // if the parameter is defined more than once in the input configuration file
          		    {
          		      	fprintf(stderr,"error at line %d -> phase parameter already called\n",line); // stderr
          		      	*error = *error + 1;
          		    }
                  // we look for the frequency parameter (same as the phase)
          		    else if((strstr(buf, "frequency") == buf) & (frequencyMark == 0))
          		    {
          			      *error = *error + param_float(buf, "frequency", &*frequency,line,&frequencyMark);
          			      if (*error == 0)
                      {
          			          strcat(secbuf, buf);
          			      }
          		    }
          		    else if ((strstr(buf, "frequency") == buf) & (frequencyMark == 1))   
          		    {
          		      	fprintf(stderr,"error at line %d -> frequency parameter already called\n",line);
          		      	*error = *error + 1;
          		    }
          		    
          		    // we look for the amplitude
          		    else if((strstr(buf, "amplitude") == buf) & (amplitudeMark == 0))
          		    {
          			      *error = *error + param_float(buf, "amplitude", &*amplitude,line,&amplitudeMark);
          			      if (*error == 0)
                      {
          			          strcat(secbuf, buf);
          			      }
          		    }
          		    else if ((strstr(buf, "amplitude") == buf) & (amplitudeMark == 1))   
          		    {
          		      	fprintf(stderr,"error at line %d -> amplitude parameter already called\n",line);
          		      	*error = *error + 1;
          		    }
                  //we look for the sampling frequency
                  else if((strstr(buf, "sampling_freq") == buf) & (samplingMark == 0))
                  {
                  	  *error = *error + param_float(buf, "sampling_freq", &*sampling,line,&samplingMark);
                  	  if (*error == 0)
                      {
                  	      strcat(secbuf, buf);
                  	  }
                  }
          		    else if ((strstr(buf, "sampling_freq") == buf) & (samplingMark == 1))   
          		    {
          		      	fprintf(stderr,"error at line %d -> sampling_freq parameter already called\n",line);
          		      	*error = *error + 1;
          		    }
                  // we look for the sampling number
                  else if((strstr(buf, "n_sample") == buf) & (nbSampleMark == 0))
                  {
                      *error = *error + param_int(buf, "n_sample", &*nbSample,line,&nbSampleMark);
                      if (*error == 0)
                      {
                          strcat(secbuf, buf);
                      }
                  }
                  else if ((strstr(buf, "n_sample") == buf) & (nbSampleMark == 1))   
                  {
                      fprintf(stderr,"error at line %d -> n_sample parameter already called\n",line);
                      *error = *error + 1;
                  }
                  // we look for empty lines and unreadable lines
                  else  if (strlen(buf) == 1)
                  {
                      fprintf(stderr,"SigGen warning at line %d -> empty line\n",line); // stderr
                  }
                  else
                  {
                      fprintf(stderr,"SigGen error at line %d -> unreadable line\n",line); //stderr
                      *error = *error + 1;
                  }
                  
          	  } 
          }


    } 
    if (isSection == 0) // if the section didn't exist, we use default values
    {
      	*error = *error + 1;
      	*signal = 1;
      	*phase = 0;
      	*frequency = 0;
      	*amplitude = 0;
      	*sampling = 0;
      	*nbSample = 1;
      	fprintf(stderr,"SigGen error in SigGen section-> #BEGIN and/or #END line badly specified or not found\n"); //stderr
    }
    return;
}


//////////////////////////////////SIGAMP///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *input_SigAmp(FILE *input,float *gain,float *offset,int *error,int *n)
{


    // text processing
    char buf[BUFSIZ];          // this parameter will contain a whole line from the input text file
    char *bufp = buf;          // this pointer will move along the line
    char secbuf[BUFSIZ] = {};  // this string will contain the whole section

    // markers
    int line =0;             // line number
    int Section =0;          // marker which tells if we are inside or outside the SigGen section
    int isSection = 0;       // marker which tells if the SigGen section exists
    int isDataSection = 0;   // marker which tells if the Data section exist
    int DataSection = 0;     // marker which tells if we are inside or outside the data section
    int p = 0;               // marker which tells where we are on the line
    int i = 0;               // marker for loop

    //markers for SigAmp parameters
    int gainMark =0;
    int offsetMark = 0;
    int dataMark = 0;

    // data section processing
    char dataValueC[BUFSIZ] ;  // string which will contain a data value
    float dataValueF = 0;      // this variable will contain the data value converted as a float
    float *dataArray = NULL;   // table which will contain all the data values


    
    while (fgets(buf, sizeof buf, input) != NULL)
    {
        line = line + 1;
        if ((strcmp(buf, "#BEGIN SigAmp\n") == 0) & (Section == 0)) 
        {
            Section = 1;
            isSection = 1;
            printf("%s",buf);
        }
        else if (((strcmp(buf, "#END SigAmp\n") == 0 )|(strcmp(buf, "#END SigAmp\0") == 0 ))& (Section == 1) ) 
        {
      	    if (gainMark == 0)
      	    {
      	      	fprintf(stderr,"error in SigAmp -> gain parameter missing\n"); 
      	      	*error = *error + 1;
      	    }
      	    if (offsetMark == 0)
      	    {
      	      	fprintf(stderr,"error in SigAmp -> offset parameter missing\n"); 
      	      	*error = *error + 1;
      	    }
      	    if (*error == 0)
      	    {
      		      printf("%s",secbuf); 
      	    }
      	    else
      	    {
      		      printf("gain = 0\noffset = 0\n");
      		      *gain = 0;
      		      *offset = 0;
      	    }
            Section = 0;
            printf("%s",buf);
        }
        else if ((strcmp(buf, "#BEGIN Data\n") == 0 )& (DataSection == 0) ) 
        {
            DataSection = 1;
            isDataSection = 1;

        }
        else if (((strcmp(buf, "#END Data") == 0 )|(strcmp(buf, "#END Data\n") == 0 ))& (DataSection == 1) )  
        {
        	  if (*error != 0)
        	  {
          		  free (dataArray) ;
          		  dataArray = init_tab(1);
          		  *n = 1;
        	  }
        	  else if (dataMark == 0)
        	  {
          		  *error = *error + 1;
          		  fprintf(stderr,"error in Data section -> section is empty");
          		  free (dataArray) ;
          		  dataArray = init_tab(1);
          		  *n = 1;
        	  }
            DataSection = 0;

        }
        else if ((Section == 0 ) & (DataSection == 0))  
        {
            printf("%s",buf);
        }
        else if (Section == 1)  
        {
        	  if (strstr(buf, "%") == buf)
        	  {
        		    strcat(secbuf, buf);
        	  }
        	  else  
        	  {
        		    lower_string(buf); 
                
          		  if((strstr(buf, "gain") == buf) & (gainMark == 0))
          		  {
          			    *error = *error + param_float(buf, "gain", &*gain,line,&gainMark);
          			    if (*error == 0)
                    {
          			        strcat(secbuf, buf);
          			    }
          		  }
          		  else if ((strstr(buf, "gain") == buf) & (gainMark == 1))  
          		  {
          		      fprintf(stderr,"error at line %d -> gain parameter already called\n",line); 
          		      *error = *error + 1;
          		  }
          		  
          		  
          		  else if((strstr(buf, "offset") == buf) & (offsetMark == 0))
          		  {
          			    *error = *error + param_float(buf, "offset", &*offset,line,&offsetMark);
          			    if (*error == 0)
                    {
          			        strcat(secbuf, buf);
          			    }
          		  }
          		  else if ((strstr(buf, "offset") == buf) & (offsetMark == 1))   
          		  {
          		      fprintf(stderr,"error at line %d -> offset parameter already called\n",line);
          		      *error = *error + 1;
          		  }
          		  
                
                else  if (strlen(buf) == 1)
                {
                    fprintf(stderr,"warning at line %d -> empty line\n",line); 
                }
                else
                {
                    fprintf(stderr,"error at line %d -> unreadable line\n",line); 
                    *error = *error + 1;
                }
                
        	  }
        }
        // we read the data section
        else if (DataSection == 1)  
        {
            if (strlen(buf) == 1) //if the line is empty
            {
                fprintf(stderr,"warning at line %d -> empty line\n",line);
            }
            else if (dataMark == 0)  //if the line contains something, we see if it contains float values separated by tabulations
            {
                p = 0;
                *n = 0;
                dataMark = 1;
            	  while (sscanf(bufp,"%s\t",dataValueC) == 1) // the line is scanned for floats
            	  {
            		    if (isFloat(dataValueC) == 0)
            		    {
                  		  bufp = bufp + strlen(dataValueC) + 1;
                  		  p = p + strlen(dataValueC) + 1;
                  		  *n = *n + 1;
            		    }
            		    else  //if there is something other than float
            		    {
                  			fprintf(stderr,"SigAmp error in Data section at line %d -> unreadable line\n",line); 
                  			*error = *error + 1;
                  		  break;
            		    }
            	  }
            	  bufp = bufp - p;
            	  if (*error == 0)  // the line of data is put in an array
            	  {
            		    dataArray = init_tab(*n);
            		    for (i = 0 ; i < *n ; i++)
                		{
                		    sscanf(bufp,"%s\t",dataValueC);
                		    sscanf(dataValueC,"%f",&dataValueF);
                		    bufp = bufp + strlen(dataValueC) + 1;
                		    dataArray[i]= dataValueF;
                		}
            	  }
            }
            else
            {
          	    fprintf(stderr,"SigAmp error in Data section at line %d -> more than one line of Data\n",line); 
          	    *error = *error + 1;
            }
        } 
    }

    if (isSection == 0) //if the SigAmp section didn't exist
    {
      	*error = *error + 1;
      	*gain = 0;
      	*offset = 0;
      	*n = 1;
        free (dataArray) ;
      	dataArray = init_tab(*n);
      	fprintf(stderr,"SigAmp error -> SigAmp section not found\n"); 
    }
    if (isDataSection == 0) //if te data section didn't exist
    {
        *error = *error + 1;
        *n = 1;
        free (dataArray) ;
        dataArray = init_tab(*n);
        fprintf(stderr,"SigAmp error -> Data section not found\n"); 
    }
    return dataArray;
}


///////////////////////////////////WHITENOISEGEN//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *input_WhiteNoiseGen(FILE *input,float *amp,int *seed,int *error,int *n)
{

    
    char buf[BUFSIZ];          
    char *bufp = buf;          
    char secbuf[BUFSIZ] = {};  
   

    
    int line =0;             
    int Section =0;          
    int isSection = 0;       
    int isDataSection = 0;   
    int DataSection = 0;     
    int p = 0;               
    int i = 0;               

    
    int ampMark =0;
    int seedMark = 0;
    int dataMark = 0;

    
    char dataValueC[BUFSIZ] ;  
    float dataValueF = 0;      
    float *dataArray = NULL;   


    
    while (fgets(buf, sizeof buf, input) != NULL)
    {
        line = line + 1;
        if ((strcmp(buf, "#BEGIN WhiteNoiseGen\n") == 0) & (Section == 0)) 
        {
            Section = 1;
            isSection = 1;
            printf("%s",buf);
        }
        else if (((strcmp(buf, "#END WhiteNoiseGen\n") == 0 )|(strcmp(buf, "#END WhiteNoiseGen\0") == 0 ))& (Section == 1) ) 
        {
            if (ampMark == 0)
            {
                fprintf(stderr,"error in WhiteNoiseGen -> amp parameter missing\n"); 
                *error = *error + 1;
            }
            if (seedMark == 0)
            {
                *seed = 0;
                strcat(secbuf, "seed = 0\n");
            }
            if (*error == 0)
            {
                printf("%s",secbuf); 
            }
            else
            {
                printf("amp = 0\nseed = 0\n");
                *amp = 0;
                *seed = 0;
            }
            Section = 0;
            printf("%s",buf);
        }
        else if ((strcmp(buf, "#BEGIN Data\n") == 0 )& (DataSection == 0) ) 
        {
            DataSection = 1;
            isDataSection = 1;

        }
        else if (((strcmp(buf, "#END Data") == 0 )|(strcmp(buf, "#END Data\n") == 0 ))& (DataSection == 1) )  
        {
            if (*error != 0)
            {
                free (dataArray) ;
                dataArray = init_tab(1);
                *n = 1;
            }
            else if (dataMark == 0)
            {
                *error = *error + 1;
                fprintf(stderr,"error in Data section -> section is empty");
                free (dataArray) ;
                dataArray = init_tab(1);
                *n = 1;
            }
            DataSection = 0;

        }
        else if ((Section == 0 ) & (DataSection == 0))  
        {
            printf("%s",buf);
        }
        else if (Section == 1)  
        {
            if (strstr(buf, "%") == buf) 
            {
                strcat(secbuf, buf);
            }
            else  
            {
                lower_string(buf); 
                
                if((strstr(buf, "amp") == buf) & (ampMark == 0))
                {
                    *error = *error + param_float(buf, "amp", &*amp,line,&ampMark);
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "amp") == buf) & (ampMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> amp parameter already called\n",line);
                    *error = *error + 1;
                }
                
                else if((strstr(buf, "seed") == buf) & (seedMark == 0))
                {
                    *error = *error + param_int(buf, "seed", &*seed,line,&seedMark);
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "seed") == buf) & (seedMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> seed parameter already called\n",line);
                    *error = *error + 1;
                }
                
                else  if (strlen(buf) == 1)
                {
                    fprintf(stderr,"warning at line %d -> empty line\n",line); 
                }
                else
                {
                    fprintf(stderr,"error at line %d -> unreadable line\n",line); 
                    *error = *error + 1;
                }
                
            }
        }
        
        else if (DataSection == 1)  
        {
            if (strlen(buf) == 1) 
            {
                fprintf(stderr,"warning at line %d -> empty line\n",line);
            }
            else if (dataMark == 0)  
            {
                p = 0;
                *n = 0;
                dataMark = 1;
                while (sscanf(bufp,"%s\t",dataValueC) == 1) 
                {
                    if (isFloat(dataValueC) == 0)
                    {
                        bufp = bufp + strlen(dataValueC) + 1;
                        p = p + strlen(dataValueC) + 1;
                        *n = *n + 1;
                    }
                    else  
                    {
                        fprintf(stderr,"WhiteNoiseGen error in Data section at line %d -> unreadable line\n",line); 
                        *error = *error + 1;
                        break;
                    }
                }
                bufp = bufp - p;
                if (*error == 0)  
                {
                    dataArray = init_tab(*n);
                    for (i = 0 ; i < *n ; i++)
                    {
                        sscanf(bufp,"%s\t",dataValueC);
                        sscanf(dataValueC,"%f",&dataValueF);
                        bufp = bufp + strlen(dataValueC) + 1;
                        dataArray[i]= dataValueF;
                    }
                }
            }
            else
            {
                fprintf(stderr,"WhiteNoiseGen error in Data section at line %d -> more than one line of Data\n",line); 
                *error = *error + 1;
            }
        } 
    }

    if (isSection == 0) 
    {
        *error = *error + 1;
        *amp = 0;
        *seed = 0;
        *n = 1;
        free (dataArray) ;
        dataArray = init_tab(*n);
        fprintf(stderr,"WhiteNoiseGen error -> WhiteNoiseGen section not found\n"); 
    }
    if (isDataSection == 0) 
    {
        *error = *error + 1;
        *n = 1;
        free (dataArray) ;
        dataArray = init_tab(*n);
        fprintf(stderr,"WhiteNoiseGen error -> Data section not found\n"); 
    }
    return dataArray;
}




///////////////////////////////////GAUSSIANNOISEGEN//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *input_GaussianNoiseGen(FILE *input,float *average,float *variance,int *seed,int *error,int *n)
{

    
    char buf[BUFSIZ];          
    char *bufp = buf;          
    char secbuf[BUFSIZ] = {};  

    
    int line =0;             
    int Section =0;          
    int isSection = 0;       
    int isDataSection = 0;   
    int DataSection = 0;     
    int p = 0;               
    int i = 0;               

    
    int averageMark =0;
    int varianceMark =0;
    int seedMark = 0;
    int dataMark = 0;

    
    char dataValueC[BUFSIZ] ;  
    float dataValueF = 0;      
    float *dataArray = NULL;   


    
    while (fgets(buf, sizeof buf, input) != NULL)
    {
        line = line + 1;
        if ((strcmp(buf, "#BEGIN GaussianNoiseGen\n") == 0) & (Section == 0)) 
        {
            Section = 1;
            isSection = 1;
            printf("%s",buf);
        }
        else if (((strcmp(buf, "#END GaussianNoiseGen\n") == 0 )|(strcmp(buf, "#END GaussianNoiseGen\0") == 0 ))& (Section == 1) ) 
        {
            if (averageMark == 0)
            {
                fprintf(stderr,"error in GaussianNoiseGen -> average parameter missing\n"); 
                *error = *error + 1;
            }
            if (varianceMark == 0)
            {
                fprintf(stderr,"error in GaussianNoiseGen -> variance parameter missing\n"); 
                *error = *error + 1;
            }
            if (seedMark == 0)
            {
                *seed = 0;
                strcat(secbuf, "seed = 0\n");
            }
            if (*error == 0)
            {
                printf("%s",secbuf); 
            }
            else
            {
                fprintf(stderr,"average = 0\nvariance = 0\nseed = 0\n");
                *average = 0;
                *variance = 0;
                *seed = 0;
            }
            Section = 0;
            printf("%s",buf);
        }
        else if ((strcmp(buf, "#BEGIN Data\n") == 0 )& (DataSection == 0) ) 
        {
            DataSection = 1;
            isDataSection = 1;

        }
        else if (((strcmp(buf, "#END Data") == 0 )|(strcmp(buf, "#END Data\n") == 0 ))& (DataSection == 1) )  
        {
            if (*error != 0)
            {
                free (dataArray) ;
                dataArray = init_tab(1);
                *n = 1;
            }
            else if (dataMark == 0)
            {
                *error = *error + 1;
                fprintf(stderr,"error in Data section -> section is empty");
                free (dataArray) ;
                dataArray = init_tab(1);
                *n = 1;
            }
            DataSection = 0;

        }
        else if ((Section == 0 ) & (DataSection == 0))  
        {
            printf("%s",buf);
        }
        else if (Section == 1)  
        {
            if (strstr(buf, "%") == buf) 
            {
                strcat(secbuf, buf);
            }
            else  
            {
                
                
                if((strstr(buf, "average") == buf) & (averageMark == 0))
                {

                    *error = *error + param_float(buf, "average", &*average,line,&averageMark);
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "average") == buf) & (averageMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> average parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "variance") == buf) & (varianceMark == 0))
                {
                    *error = *error + param_float(buf, "variance", &*variance,line,&varianceMark);
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "variance") == buf) & (varianceMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> variance parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "seed") == buf) & (seedMark == 0))
                {
                    *error = *error + param_int(buf, "seed", &*seed,line,&seedMark);
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "seed") == buf) & (seedMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> seed parameter already called\n",line);
                    *error = *error + 1;
                }
                
                
                else  if (strlen(buf) == 1)
                {
                    fprintf(stderr,"warning at line %d -> empty line\n",line); 
                }
                else
                {
                    fprintf(stderr,"error at line %d -> unreadable line\n",line); 
                    *error = *error + 1;
                }
               
            }
        }
        
        else if (DataSection == 1)  
        {
            if (strlen(buf) == 1) 
            {
                fprintf(stderr,"warning at line %d -> empty line\n",line);
            }
            else if (dataMark == 0)  
            {
                p = 0;
                *n = 0;
                dataMark = 1;
                while (sscanf(bufp,"%s\t",dataValueC) == 1) 
                {
                    if (isFloat(dataValueC) == 0)
                    {
                        bufp = bufp + strlen(dataValueC) + 1;
                        p = p + strlen(dataValueC) + 1;
                        *n = *n + 1;
                    }
                    else  
                    {
                        fprintf(stderr,"GaussianNoiseGen error in Data section at line %d -> unreadable line\n",line); 
                        *error = *error + 1;
                        break;
                    }
                }
                bufp = bufp - p;
                if (*error == 0)  
                {
                    dataArray = init_tab(*n);
                    for (i = 0 ; i < *n ; i++)
                    {
                        sscanf(bufp,"%s\t",dataValueC);
                        sscanf(dataValueC,"%f",&dataValueF);
                        bufp = bufp + strlen(dataValueC) + 1;
                        dataArray[i]= dataValueF;
                    }
                }
            }
            else
            {
                fprintf(stderr,"GaussianNoiseGen error in Data section at line %d -> more than one line of Data\n",line); 
                *error = *error + 1;
            }
        } 
    }

    if (isSection == 0) 
    {
        *error = *error + 1;
        *average = 0;
        *variance = 0;
        *seed = 0;
        *n = 1;
        free (dataArray) ;
        dataArray = init_tab(*n);
        fprintf(stderr,"GaussianNoiseGen error -> GaussianNoiseGen section not found\n"); 
    }
    if (isDataSection == 0) 
    {
        *error = *error + 1;
        *n = 1;
        free (dataArray) ;
        dataArray = init_tab(*n);
        fprintf(stderr,"GaussianNoiseGen error -> Data section not found\n"); 
    }
    return dataArray;
}






// the function input_SigPlot takes as input a configuration file and the parameters whose values are decided by the configuration file
// it looks for the section which correspond to it and then looks inside of this section for the parameters
// it then modifies the input parameters with the value it finds in the configuration file
// it then write a new configuration file containing the final signal

///////////////////////////////////SIGPLOT//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *input_SigPlot(FILE *input,char *title,char *x_label,char *y_label,char * image_name,char *out,char *scale,char *shape,char *color,char *image_type,int *error,int *n)
{



    
    char buf[BUFSIZ];          
    char *bufp = buf;          
    char secbuf[BUFSIZ] = {};  
    char confbuf[BUFSIZ] = {};  
    FILE* f =NULL; //output configuration file
    char outFile[100] = {};


    
    int line =0;             
    int Section =0;          
    int isSection = 0;       
    int isDataSection = 0;   
    int DataSection = 0;     
    int p = 0;               
    int i = 0;               

    
    int titleMark =0;
    int x_labelMark =0;
    int y_labelMark = 0;
    int image_nameMark =0;
    int outMark =0;
    int scaleMark = 0;
    int shapeMark = 0;
    int colorMark = 0;
    int image_typeMark = 0;
    int dataMark = 0;

    
    char dataValueC[BUFSIZ] ;  
    float dataValueF = 0;      
    float *dataArray = NULL;   


    
    while (fgets(buf, sizeof buf, input) != NULL)
    {
        line = line + 1;
        if ((strcmp(buf, "#BEGIN SigPlot\n") == 0) & (Section == 0)) 
        {
            Section = 1;
            isSection = 1;
            
            strcat(confbuf, buf);
        }
        else if (((strcmp(buf, "#END SigPlot\n") == 0 )|(strcmp(buf, "#END SigPlot\0") == 0 ))& (Section == 1) ) 
        {

            
            if (titleMark == 0)
            {


                sscanf("noTitle","%s",title);
                strcat(secbuf, "title = \"noTitle\"\n");
            }
            if (x_labelMark == 0)
            {

                sscanf("xAxis","%s",x_label);
                strcat(secbuf, "x_label = \"xAxis\"\n");
            }
            if (y_labelMark == 0)
            {

                sscanf("yAxis","%s",y_label);
                strcat(secbuf, "y_label = \"yAxis\"\n");
            }
            if (image_nameMark == 0)
            {

                sscanf("image_output","%s",image_name);
                strcat(secbuf, "image_name = \"image_output\"\n");
            }
            if (outMark == 0)
            {

                sscanf("config_output","%s",out);
                strcat(secbuf, "out = \"config_output\"\n");
            }
            if (scaleMark == 0)
            {

                sscanf("linear","%s",scale);
                strcat(secbuf, "scale = \"linear\"\n");
            }
            if (shapeMark == 0)
            {

                sscanf("line","%s",shape);
                strcat(secbuf, "shape = \"line\"\n");
            }
            if (colorMark == 0)
            {

                sscanf("black","%s",color);
                strcat(secbuf, "color = \"black\"\n");
            }
            if (image_typeMark == 0)
            {

                sscanf("jpg","%s",image_type);
                strcat(secbuf, "image_type = \"jpg\"\n");
            }
            if (*error == 0)
            {
                
              strcat(confbuf, secbuf);
            }
            else
            {


                
                strcat(confbuf, "title = \"noTitle\"\nx_label = \"xAxis\"\ny_label = \"yAxis\"\nimage_name = \"image_output\"\nout = \"config_output\"\nscale = \"linear\"\nshape = \"line\"\ncolor = \"black\"\nimage_type = \"jpg\"\n");

                sscanf("noTitle","%s",title);
                sscanf("xAxis","%s",x_label);
                sscanf("yAxis","%s",y_label);
                sscanf("image_output","%s",image_name);
                sscanf("config_output","%s",out);
                sscanf("linear","%s",scale);
                sscanf("line","%s",shape);
                sscanf("black","%s",color);
                sscanf("jpg","%s",image_type);


            }
            Section = 0;
            
            strcat(confbuf, buf);
        }
        else if ((strcmp(buf, "#BEGIN Data\n") == 0 )& (DataSection == 0) ) 
        {
            DataSection = 1;
            isDataSection = 1;

        }
        else if (((strcmp(buf, "#END Data") == 0 )|(strcmp(buf, "#END Data\n") == 0 ))& (DataSection == 1) )  
        {
            if (*error != 0)
            {
                free (dataArray) ;
                *n = 1;
                dataArray = NULL; 

            }
            else if (dataMark == 0)
            {
                *error = *error + 1;
                fprintf(stderr,"error in Data section -> section is empty");
                free (dataArray) ;
                *n = 1;
                dataArray = NULL; 

            }
            DataSection = 0;

        }
        else if ((Section == 0 ) & (DataSection == 0))  
        {
            
            strcat(confbuf, buf);
        }
        else if (Section == 1)  
        {
            if (strstr(buf, "%") == buf) 
            {
                strcat(secbuf, buf);
            }
            else  
            {
                lower_string(buf); 
                
                if((strstr(buf, "title") == buf) & (titleMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "title", &title,line,&titleMark); //we make sure that we only find a string between two quotation marks
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "title") == buf) & (titleMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> title parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "x_label") == buf) & (x_labelMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "x_label", &x_label,line,&x_labelMark);
                    if (*error == 0)
                    {

                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "x_label") == buf) & (x_labelMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> x_label parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "y_label") == buf) & (y_labelMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "y_label", &y_label,line,&y_labelMark);
                    if (*error == 0)
                    {

                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "y_label") == buf) & (y_labelMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> y_label parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "image_name") == buf) & (image_nameMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "image_name", &image_name,line,&image_nameMark);
                    if (*error == 0)
                    {

                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "image_name") == buf) & (image_nameMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> image_name parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "out") == buf) & (outMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "out", &out,line,&outMark);
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "out") == buf) & (outMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> out parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "scale") == buf) & (scaleMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "scale", &scale,line,&scaleMark);
                    if ((strcmp(scale,"linear")!=0)&(strcmp(scale,"log")!=0))
                    {
                        fprintf(stderr,"scale error in line %d -> parameter absent or bad\n",line); 
                        *error = *error + 1;
                    }
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "scale") == buf) & (scaleMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> scale parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "shape") == buf) & (shapeMark == 0))
                {

                    *error = *error + param_stringWithQuotes(buf, "shape", &shape,line,&shapeMark);

                    if ((strcmp(shape,"line") != 0)&(strcmp(shape,"point") != 0)&(strcmp(shape,"asterisk") != 0))
                    {

                        *error = *error + 1;
                        fprintf(stderr,"shape error in line %d -> parameter absent or bad\n",line); 
                    }
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "shape") == buf) & (shapeMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> shape parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "color") == buf) & (colorMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "color", &color,line,&colorMark);
                    if ((strcmp(color,"black") != 0)&(strcmp(color,"blue") != 0)&(strcmp(color,"red") != 0)&(strcmp(color,"green") != 0)&(strcmp(color,"yellow") != 0))
                    {
                        *error = *error + 1;
                        fprintf(stderr,"color error in line %d -> parameter absent or bad\n",line); 
                    }
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "color") == buf) & (colorMark == 1))   
                {
                    fprintf(stderr,"error at line %d -> color parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else if((strstr(buf, "image_type") == buf) & (image_typeMark == 0))
                {
                    *error = *error + param_stringWithQuotes(buf, "image_type", &image_type,line,&image_typeMark);
                    if ((strcmp(image_type,"jpg")!=0)&(strcmp(image_type,"bmp")!=0))
                    {
                        *error = *error + 1;
                        fprintf(stderr,"image_type error in line %d -> parameter absent or bad\n",line); 
                    }
                    if (*error == 0)
                    {
                        strcat(secbuf, buf);
                    }
                }
                else if ((strstr(buf, "image_type") == buf) & (image_typeMark == 1))  
                {
                    fprintf(stderr,"error at line %d -> image_type parameter already called\n",line); 
                    *error = *error + 1;
                }
                
                
                else  if (strlen(buf) == 1)
                {
                    fprintf(stderr,"warning at line %d -> empty line\n",line); 
                }
                else
                {
                    fprintf(stderr,"error at line %d -> unreadable line\n",line); 
                    *error = *error + 1;
                }
                
            }
        }
        
        else if (DataSection == 1)  
        {
            if (strlen(buf) == 1) 
            {
                fprintf(stderr,"warning at line %d -> empty line\n",line);
            }
            else if (dataMark == 0)  
            {
                p = 0;
                *n = 0;
                dataMark = 1;
                while (sscanf(bufp,"%s\t",dataValueC) == 1) 
                {
                    if (isFloat(dataValueC) == 0)
                    {
                        bufp = bufp + strlen(dataValueC) + 1;
                        p = p + strlen(dataValueC) + 1;
                        *n = *n + 1;
                    }
                    else  
                    {
                        fprintf(stderr,"SigPlot error in Data section at line %d -> unreadable line\n",line); 
                        *error = *error + 1;
                        break;
                    }
                }
                bufp = bufp - p;
                if (*error == 0)  
                {
                    dataArray = init_tab(*n);
                    for (i = 0 ; i < *n ; i++)
                    {
                        sscanf(bufp,"%s\t",dataValueC);
                        sscanf(dataValueC,"%f",&dataValueF);
                        bufp = bufp + strlen(dataValueC) + 1;
                        dataArray[i]= dataValueF;
                    }
                }
            }
            else
            {
                fprintf(stderr,"SigPlot error in Data section at line %d -> more than one line of Data\n",line); 
                *error = *error + 1;
            }
        } 
    }

    if (isSection == 0) 
    {
        *error = *error + 1;
        sscanf("noTitle","%s",title);
                sscanf("xAxis","%s",x_label);
                sscanf("yAxis","%s",y_label);
                sscanf("image_output","%s",image_name);
                sscanf("config_output","%s",out);
                sscanf("linear","%s",scale);
                sscanf("line","%s",shape);
                sscanf("black","%s",color);
                sscanf("jpg","%s",image_type);
        *n = 1;
        free (dataArray) ;
        dataArray = NULL; 
        fprintf(stderr,"SigPlot error -> SigPlot section not found\n"); 
    }
    if (isDataSection == 0) 
    {
        *error = *error + 1;
        *n = 1;
        free (dataArray) ;
        dataArray = NULL; 
        fprintf(stderr,"SigPlot error -> Data section not found\n"); 
    }

    strcat(outFile,out);
    strcat(outFile,".txt");

    f = fopen (outFile, "w") ;
    fprintf(f,"%s",confbuf); 
    fclose (f) ;
    f=NULL;
    return dataArray;
}




//the output_Data function either directly send the data section to the next application or write the Data section on an output text file



///////////////////////////////////DATA//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void output_Data(float *dataArray,int n,char* destination)
{
  int i = 0;

  if (strcmp(destination,"stdout") == 0) //the section is sent to the next application
  {
      printf("\n#BEGIN Data\n"); 
      for (i = 0;i<n;i++)
      {
         printf("%f",dataArray[i]);
         if (i < n-1)
         {
        	 printf("\t");
         }
         else
         {
            printf("\n");
         }
      }
      printf("#END Data"); 
  }
  else  //the section is written in a text file
  {
      FILE* f =NULL;
      f = fopen (strcat(destination,".txt"), "a") ;
      fprintf(f,"\n#BEGIN Data\n");
      for (i = 0;i<n;i++)
      {
         fprintf(f,"%f",dataArray[i]);
         if (i < n-1)
         {
        	fprintf(f,"\t");
         }
         else
         {
        	 fprintf(f,"\n");
         }
      }
      fprintf(f,"#END Data");
      fclose (f) ;
      f=NULL;
  }

  
  return;
}

//////////////////////////////////FONCTIONS///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//The functions param_stringWithQuotes and isStringWithQuotes were made for the input_SigPlot function because specifications 
//asked for the string parameters of the SigPlot section to start and end with quotation marks

int param_stringWithQuotes(char* buf, char* parameter, char **value, int line, int *marker) {


  int error = 0;
  char *bufp = buf;


  while (*bufp == ' ')   //we jump an unknown number of space
  {
    bufp = bufp + 1;
  }
  bufp = bufp + strlen(parameter); //we move the pointer to read the rest of the line
  while (*bufp == ' ')   //we jump an unknown number of space
  {
    bufp = bufp + 1;
  }
  if (*bufp == '=')    //we look for an "=" symbol
  {
    bufp = bufp + 1;
    while (*bufp == ' ')        //we jump an unknown number of space
    {
      bufp = bufp + 1;
    }
    // we verify that the line end with a string between two quotation marks
    if (isStringWithQuotes(bufp) == 0)
    {
      sscanf(bufp,"%*c%[^\"]",*value);

      *marker = 1;
    }
    else   //if we don't
    {
      fprintf(stderr,"%s error in line %d -> string absent or bad\n",parameter,line); 
      error = 1;
      *marker = 1;
    }
  }
  else // if there is no "="
  {
    fprintf(stderr,"%s error in line %d -> unreadable line\n",parameter,line); 
    error = 1;
    *marker = 1;
  }
  return error;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// this function determine if a string start and end with quotation marks
int isStringWithQuotes(char s[]) {

   int c = 0;
   int error = 0;
   int space = 0;
   int f = 0;

   
   if (s[strlen(s)-1] == '\n') //if there is a "\n" for a line break
   {
     f = 2;
   }
   else
   {
     f = 1;
   }
   
   if(strlen(s) <= f + 1)  //if the string is too short 
   {
     error = 1;
     return error;
   }
   
   if(s[0] != '\"')  //if the string doesn't start with a quotation mark
   {
     error = 1;
     return error;
   }
   //we count the number of spaces so we can ignore them
   space = 0;
   while (s[(strlen(s)-f) - space] == ' ')   
   {
    space = space + 1;
   }
   
   if(s[strlen(s) - f - space] != '\"') //if the string doesn't end with a quotation mark
   {
     error = 1;
     return error;
   }
   // we make sure the rest of the string doesn't contain ambiguous symbols
   for (c = 1; c < (strlen(s) - f - space); c++ )
   {
      if ((s[c] < ' ' )|( s[c] > '}')|( s[c] == '\"'))
      {
        error = 1;
        return error;
      }
   }
   return error;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function verify if the input parameter is an int
int param_int(char* buf, char* parameter, int *value, int line, int *marker) {

  int error = 0;
  char *bufp = buf;

  while (*bufp == ' ')   //we jump an unknown number of space
  {
    bufp = bufp + 1;

  }
  bufp = bufp + strlen(parameter); //we move the pointer to read the rest of the line
  while (*bufp == ' ')   //we jump an unkown number of space
  {
    bufp = bufp + 1;
  }
  if (*bufp == '=')    //we look for a "="
  {
      bufp = bufp + 1;
    while (*bufp == ' ')        //we jump an unknown number of space
    {
      bufp = bufp + 1;
    }
    // we verify that the line end with an acceptable parameter (an int)
    if (isInt(bufp) == 0)
    {
      sscanf(bufp,"%d",&*value);
        *marker = 1;
    }
    else   //if not
    {
      fprintf(stderr,"%s error in line %d -> value absent or bad\n",parameter,line); 
        error = 1;
        *marker = 1;
    }
  }
  else // if there is no "="
  {
    fprintf(stderr,"%s error in line %d -> unreadable line\n",parameter,line); 

      error = 1;
      *marker = 1;
  }
  return error;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function verify if the input parameter is a float
int param_float(char* buf, char* parameter, float *value, int line, int *marker) {

  int error = 0;
  char *bufp = buf;

  while (*bufp == ' ')   
  {
    bufp = bufp + 1;
  }
  bufp = bufp + strlen(parameter); 
  while (*bufp == ' ')   
  {
    bufp = bufp + 1;
  }
  if (*bufp == '=')    
  {
    bufp = bufp + 1;
    while (*bufp == ' ')        
    {
      bufp = bufp + 1;
    }
    
    if (isFloat(bufp) == 0)
    {
      sscanf(bufp,"%e",&*value);
      *marker = 1;
    }
    else   
    {
      fprintf(stderr,"%s error in line %d -> value absent or bad\n",parameter,line); 
      error = 1;
      *marker = 1;
    }
  }
  else 
  {
    fprintf(stderr,"%s error in line %d -> unreadable line\n",parameter,line); 
    error = 1;
    *marker = 1;
  }
  return error;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function convert higher-case to lower-case
void lower_string(char s[]) {

   int c = 0;

   while (s[c] != '\0')
   {
      if (s[c] >= 'A' && s[c] <= 'Z')
      {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function verify if the input string is an int
int isInt(char s[]) {
   int c = 0;
   int error = 0;
   int space = 0;
   int f = 0;

   
   if (s[strlen(s)-1] == '\n') //if the line end with a line break
   {
     f = 2;
   }
   else
   {
     f = 1;
   }
   // if the Int is made of only one number
   if((strlen(s) == f) & ((s[strlen(s)-f] < '0' )|( s[strlen(s)-f] > '9')))
   {
     error = 1;
     return error;
   }
   // we count the number of spaces so that we can ignore them
   space = 0;
   while (s[(strlen(s)-f) - space] == ' ')   
   {
    space = space + 1;
   }
   // we make sure the rest of the int doesn't contain non-numbers
   for (c = 0; c <= (strlen(s) - f - space); c++ )
   {
      if ((s[c] < '0' )|( s[c] > '9'))
      {
        error = 1;
        return error;
      }
   }
   return error;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function verify that the input string is a float
int isFloat(char s[]) {
   int c = 0;
   int error = 0;
   int sci = 0;
   int pt = 0;
   int space = 0;
   int f = 0;

   
   if (s[strlen(s)-1] == '\n') //if the line end with a line break
   {
	   f = 2;
   }
   else
   {
	   f = 1;
   }
   // on verifie le debut du flottant
   if ((s[0] == '\n')|(s[0] == '\0'))
   {
	   error = 1;
	   return error;
   }
   if (  ((s[0] < '0' )|( s[0] > '9') ) & (s[0] != '-')&(s[0] != 'e')&(s[0] != '.') &(s[0] != '+')  )//if the first character is not a number or negative/positive sign or exponential symbol or a dot
   {
	   error = 1;
	   return error;
   }
   else if (s[0] == 'e') //if the scientific notation is used
   {
	   sci = 1;
   }
   else if (s[0] == '.')
   {
	   pt = 1;
   }
   
   if((strlen(s) == f) & ((s[strlen(s)-f] < '0' )|( s[strlen(s)-f] > '9'))) //if the string is made of one non-number 
   {
     error = 1;
     return error;
   }
   
   if (   ((s[strlen(s)-f] < '0' )|( s[strlen(s)-f] > '9')) & (s[strlen(s)-f] != '.') & (s[strlen(s)-f] != ' ')    ) //if the end of the float does not end correctly
   {
	   error = 1;
	   return error;
   }
   // we count the number of spaces so that we can ignore them
   space = 0;
   while (s[(strlen(s)-f) - space] == ' ')
   {
    space = space + 1;
   }
   // we make sure the rest of the float doesn't contain aberrant symbols
   for (c = 1; c <= (strlen(s) - f - space); c++ )
   {
      if ((s[c] >= '0' )&( s[c] <= '9'))
      {
      }
      else if ((s[c] == 'e' )&( sci == 0)&(s[c-1] != '.'))
      {
    	  sci = 1;
      }
      else if ((s[c-1] == 'e' )&( (s[c] == '-')|(s[c] == '+')))
      {
      }
      else if ((s[c] == '.' )&( sci == 0)&( pt == 0))
      {
    	  pt = 1;
      }
      else
      {
    	  error = 1;
    	  return error;
      }
   }
   return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// function to allocate a 1D table
float *init_tab(int n)
{
 float *tab = NULL ;
 int i=0;

 tab = malloc ( n * sizeof (int *) ) ;
 if ( tab == NULL )
    {
      err(-1, "%s :%d malloc (%ld) failed", __FILE__, __LINE__,n * sizeof (int *) ) ;
    }
 /*initialisation*/
 for (i = 0 ; i < n ; i++)
     {

       tab[i] = 0 ;

     }
return tab;
}



