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
 
 #define FRECUENCY 15000
 #define MINFRECUENCY 1500
 #define MAXFRECUENCY 5000


int ResetPin(){
 
  pinMode (PIN, OUTPUT) ;
  
  digitalWrite (PIN,  LOW) ;
  
  softToneStop(PIN);
  
  return EXIT_SUCCESS;
}

int InhibirAhoraFrecuencia(int frecuencia){
 
 softToneCreate (PIN);
 
 printf("Tono de frecuencia %dHz.\n",frecuencia);
 
 softToneWrite (PIN, frecuencia);

 return EXIT_SUCCESS;
}

int InhibirConTemporizadorDelayStr(const char *inputStr,int frecuencia){
 struct tm ltm = {0};
 long            ms; // Milliseconds
 
 strptime(inputStr, "%T", &ltm);
 mktime(&ltm);
 
 ms=(long)(ltm.tm_hour*60*60)+(long)(ltm.tm_min*60)+(long)ltm.tm_sec;
 //ms = round(timespan.tv_nsec / 1.0e6); 
 
  ms=ms*1000;
  
  printf("Empezará dentro de  = %ld (mllisegundos)\n", ms*1000);
 
 delay(ms);
 
 puts("Empieza la fiesta ;)");
 
 return InhibirAhoraFrecuencia(frecuencia);
}

int InhibirConTemporizadorDelayStartStopStr(const char *inputStrInicio,const char *inputStrFin,int frecuencia){
 int resultado;
  struct tm ltm = {0};
 long            ms; // Milliseconds
 
 strptime(inputStrFin, "%T", &ltm);
 mktime(&ltm);
 
 ms=(long)(ltm.tm_hour*60*60)+(long)(ltm.tm_min*60)+(long)ltm.tm_sec;
 //ms = round(timespan.tv_nsec / 1.0e6); 
 
  ms=ms*1000;
  
 resultado= InhibirConTemporizadorDelayStr(inputStrInicio,frecuencia);
  
  if(resultado!=EXIT_SUCCESS){
   return resultado;
  }
  
  printf("Finalizara dentro de  = %ld (mllisegundos)\n", ms*1000);
 
 delay(ms);
 
 puts("Termino la fiesta :(");
 
 return ResetPin();
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
printf("%s -s HH:mm:ss => Inhibir dento de HH horas mm minutos y ss segundos.\n",argv[0]);
printf("%s -s HH:mm:ss -t HH:mm:ss  => Inhibir dento de HH horas mm minutos y ss segundos.\n",argv[0]);
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
}
else if(argc>2){
 if(argc==3 && strcmp("-d", argv[1])==0){
  //delay de timestamp
 }
 else if(argc==3 && strcmp("-s", argv[1])==0){
   return InhibirConTemporizadorDelayStr(argv[2],FRECUENCY);
 }
 else if(argc==5 && strcmp("-s", argv[1])==0 && strcmp("-t", argv[3])==0){
   return InhibirConTemporizadorDelayStartStopStr(argv[2],argv[4],FRECUENCY);
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


