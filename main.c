#include <wiringPi.h>
#include <softTone.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define SIZE 256

 #define PIN     0
 
 #define FRECUENCY 15000

int main (void)
{

  int f = 440;                //frequency
  int fs = 48000;             //sampling frequency

float buffer [fs];

  char bufferTimmer[SIZE];
  time_t curtime;
  struct tm *loctime;

  /* Get the current time. */
  curtime = time (NULL);

  /* Convert it to local time representation. */
  loctime = localtime (&curtime);

  /* Print out the date and time in the standard format. */
  fputs (asctime (loctime), stdout);

  /* Print it out in a nice format. */
  strftime (bufferTimmer, SIZE, "Today is %A, %B %d.\n", loctime);
  fputs (bufferTimmer, stdout);
  strftime (bufferTimmer, SIZE, "The time is %I:%M %p.\n", loctime);
  fputs (bufferTimmer, stdout);
  
  /*
   printf("Sine tone at %dHz ",f);

        for (k=0; k<BUFFER_LEN; k++){

            buffer[k] = (sin(2*M_PI*f/fs*k));                 //sine wave value generation                        
            } 

*/

wiringPiSetup () ;
   /*
     softToneCreate (PIN);
     
     softToneWrite (PIN, FRECUENCY);
*/
/*
  wiringPiSetup () ;
  pinMode (PIN, OUTPUT) ;
  */
  pinMode (PIN, OUTPUT) ;
  digitalWrite (PIN, LOW) ;
  
  /*
  for (;;)
  {
    digitalWrite (PIN, HIGH) ; delay (500) ;
    digitalWrite (PIN,  LOW) ; delay (500) ;
  }
  return 0 ;
  
  */
}