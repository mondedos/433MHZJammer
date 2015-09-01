#include <wiringPi.h>
#include <softTone.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<stdlib.h>

#define EXIT_SUCCESS 0

#define SIZE 256

 #define PIN     0
 
 #define FRECUENCY 5000
 #define MINFRECUENCY 1500
 #define MAXFRECUENCY 5000


int InhibirAhoraFrecuencia(int frecuencia){
 
 softToneCreate (PIN);
 
 softToneWrite (PIN, frecuencia);

 return EXIT_SUCCESS;
}
int InhibirConTemporizadorDelayStr(const char *inputStr){
 struct tm ltm = {0};
 
 char buf[255];
 
 puts(inputStr);
 
 strptime(inputStr, "%T", &ltm);
 mktime(&ltm);
 
 puts(buf);
 
 exit(EXIT_SUCCESS);
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
  
  softToneStop(PIN);
  
  return EXIT_SUCCESS;
}

int main (int argc, char **argv, char **envp)
{
 
if(argc==1 || strcmp("-h", argv[1])==0)
{
    printf("Uso de %s\n",argv[0]);
printf("\n");
printf("%s -h => Ayuda.\n",argv[0]);
printf("%s -r => Apagado del módulo.\n",argv[0]);
printf("%s -i => Inhibir ahora.\n",argv[0]);
printf("%s -i -f frecuencia => Inhibir ahora con una frecuenca en Hz.\n",argv[0]);
printf("%s -d HH:mm:ss => Inhibir dento de HH horas mm minutos y ss segundos.\n",argv[0]);
printf("%s -t <Hora inicio> <Hora Fin> => Inhibir entre dos horas con formato HH:mm.\n",argv[0]);
    return EXIT_FAILURE;
}
if(argc==2){
 
 wiringPiSetup () ;
 
 if(strcmp("-r", argv[1])==0){
 return  ResetPin();
 }
 else if(strcmp("-i", argv[1])==0){
   return InhibirAhoraFrecuencia(FRECUENCY);
 }
 else if(strcmp("-t", argv[1])==0){
  puts(argv[2]);
   return InhibirConTemporizadorDelayStr(argv[2]);
 }
 
}
else if(argc>2){
 if(argc==3 && strcmp("-d", argv[1])==0){
  //delay de timestamp
 }
 
 if(argc==4 && strcmp("-i", argv[1])==0 &&strcmp("-f", argv[2])==0){
  int frecuencia = atoi(argv[3]);
  
  if(frecuencia<MINFRECUENCY){
   printf("La frecuencia no puede ser inferior a %dHz ni superior a %dHz.\n",MINFRECUENCY,MAXFRECUENCY);
    return EXIT_FAILURE;
  }
  
   return InhibirAhoraFrecuencia(frecuencia);
 }
}

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


