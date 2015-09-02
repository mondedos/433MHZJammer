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
 
  softToneStop(PIN);delay (1500) ;
  
  pinMode (PIN, OUTPUT) ;delay (1500) ;
  
  digitalWrite (PIN,  LOW) ;delay (1500) ;
  
  return EXIT_SUCCESS;
}

int InhibirAhoraFrecuencia(int frecuencia){
 int rc;
 //char buffer[SIZE];
  
 pinMode (PIN, OUTPUT) ;delay (500) ;
  
 rc=softToneCreate (PIN);
 
 if (rc){
   fprintf(stdout, "ERROR; return code from pthread_create() is %d\n", rc);
   
   fflush( stdout) ; 
   return EXIT_FAILURE;
 }
 /**
 fprintf(stdout, "Generando tono a %dHz.\n", frecuencia);
   
   fflush( stdout) ; delay (500) ;
 */
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
  
  fprintf(stdout,"Empezará dentro de  = %ld (mllisegundos)\n", ms*1000);
  fflush( stdout) ; 
 
 delay(ms);
 
 fprintf(stdout,"Empieza la fiesta ;)");
 fflush( stdout) ; 
 
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
  
  fprintf(stdout,"Finalizara dentro de  = %ld (mllisegundos)\n", ms*1000);
  fflush( stdout) ; 
 
 delay(ms);
 
 fprintf(stdout,"Termino la fiesta :(\n");
 fflush( stdout) ; 
 
 return ResetPin();
}

int PinTest(){
 fprintf(stdout,"Pin ON\n");
 fflush( stdout) ; 
     digitalWrite (PIN, HIGH) ; delay (1500) ;
     
     fprintf(stdout,"Pin Off\n");
 fflush( stdout) ; 
    digitalWrite (PIN,  LOW) ; delay (1500) ;
    
     return EXIT_SUCCESS;
}
int SetValor(int valor){
 int nuevoValor=valor==1?HIGH:LOW;
 fprintf(stdout,nuevoValor==HIGH?"Pin ON\n":"Pin Off\n");
 fflush( stdout) ; 
     digitalWrite (PIN, nuevoValor) ; 
    
     return EXIT_SUCCESS;
}

int main (int argc, char **argv, char **envp)
{
 
if(argc==1 || strcmp("-h", argv[1])==0)
{
    printf("Uso de %s\n",argv[0]);
printf("\n");
printf("%s -h => Ayuda.\n",argv[0]);
printf("%s -pt => PIN Test en pin %d.\n",argv[0],PIN);
printf("%s -r => Apagado del módulo.\n",argv[0]);
printf("%s -i => Inhibir ahora.\n",argv[0]);
printf("%s -ct 1 => Inhibir ahora con pulso 1 o 0.\n",argv[0]);
printf("%s -i -f frecuencia => Inhibir ahora con una frecuenca en Hz.\n",argv[0]);
printf("%s -s HH:mm:ss => Inhibir dento de HH horas mm minutos y ss segundos.\n",argv[0]);
printf("%s -s HH:mm:ss -t HH:mm:ss  => Inhibir dento de HH horas mm minutos y ss segundos.\n",argv[0]);
    return EXIT_FAILURE;
}
if(argc==2){
 if(strcmp("-r", argv[1])==0){
  if (wiringPiSetup () < 0)
  {
    fprintf (stdout, "setup failed\n") ;
    fflush( stdout) ;
    exit (1) ;
  }
  return ResetPin();
 }
 else if(strcmp("-pt", argv[1])==0){
  if (wiringPiSetup () < 0)
  {
   fprintf (stdout, "setup failed\n") ;
    fflush( stdout) ;
    exit (1) ;
  }
 return  PinTest();
 }
 else if(strcmp("-i", argv[1])==0){
  if (wiringPiSetup () < 0)
  {
    fprintf (stdout, "setup failed\n") ;
    fflush( stdout) ;
    exit (1) ;
  }
   return InhibirAhoraFrecuencia(FRECUENCY);
 }
}
else if(argc>2){
 if(argc==3 && strcmp("-ct", argv[1])==0){
  if (wiringPiSetup () < 0)
  {
   fprintf (stdout, "setup failed\n") ;
    fflush( stdout) ;
    exit (1) ;
  }
  
  int valor = atoi(argv[2]);
  
  return SetValor(valor);
  
 }
 else if(argc==3 && strcmp("-s", argv[1])==0){
  if (wiringPiSetup () < 0)
  {
   fprintf (stdout, "setup failed\n") ;
    fflush( stdout) ;
    exit (1) ;
  }
   
   return InhibirConTemporizadorDelayStr(argv[2],FRECUENCY);
 }
 else if(argc==5 && strcmp("-s", argv[1])==0 && strcmp("-t", argv[3])==0){
  if (wiringPiSetup () < 0)
  {
   fprintf (stdout, "setup failed\n") ;
    fflush( stdout) ;
    exit (1) ;
  }
   
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


