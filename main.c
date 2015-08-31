#include <wiringPi.h>
#include <softTone.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

#define SIZE 256

 #define PIN     0
 
 #define FRECUENCY 15000

int InhibirAhora(){
 
 softToneCreate (PIN);
 
 softToneWrite (PIN, FRECUENCY);

 return EXIT_SUCCESS;
}

int InhibirConTemporizador(){
 
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
 
 return EXIT_SUCCESS;
}

int ResetPin(){
 
  pinMode (PIN, OUTPUT) ;
  
  digitalWrite (PIN,  LOW) ;
  
  return EXIT_SUCCESS;
}

int main (int argc, char **argv, char **envp)
{
/*
  int f = 440;                //frequency
  int fs = 48000;             //sampling frequency

float buffer [fs];
*/


if(argc==1 || strcmp("-h", argv[1])==0)
{
    printf("Uso de %s\n",argv[0]);
printf("\n");
printf("%s -h => Ayuda.\n",argv[0]);
printf("%s -r => Apagado del módulo.\n",argv[0]);
printf("%s -i => Inhibir ahora.\n",argv[0]);
printf("%s -t <Hora inicio> <Hora Fin> => Inhibir entre dos horas con formato HH:mm.\n",argv[0]);
    return EXIT_FAILURE;
}
if(argc==2){
 
 wiringPiSetup () ;
 
 if(strcmp("-r", argv[1])==0){
 return  ResetPin();
 }
 else if(strcmp("-i", argv[1])==0){
   return  InhibirAhora();
 }
 
}



  
  
  /*
   printf("Sine tone at %dHz ",f);

        for (k=0; k<BUFFER_LEN; k++){

            buffer[k] = (sin(2*M_PI*f/fs*k));                 //sine wave value generation                        
            } 

*/


   



  /*
  for (;;)
  {
    digitalWrite (PIN, HIGH) ; delay (500) ;
    digitalWrite (PIN,  LOW) ; delay (500) ;
  }
  return 0 ;
  
  */
  
  return EXIT_SUCCESS;
}


