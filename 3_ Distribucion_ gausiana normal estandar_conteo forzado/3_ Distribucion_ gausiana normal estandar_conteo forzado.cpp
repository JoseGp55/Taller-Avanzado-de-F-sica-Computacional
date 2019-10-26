//Calculo del area debajo de una gausiana normal estandar
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define CLASES 500
#define pi 3.14159265358979323846

double alea(void);
void imprime_gdrx(void);

int p, pasos=10000000, actu=100000;
int conteos=0;

float dlx=8.0/CLASES;//flotante :P

long int gdrx[CLASES+1]={0};

FILE *dat;
//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

system ("mkdir temp");

float xi, fxi, yi;

for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	do{
		xi=alea()*8-4;
		fxi=exp(-pow(xi,2)/2)/sqrt(2*pi);
		yi=alea();
	}while(yi>fxi);
		conteos++;// podemos prescindir de esta variable
    	gdrx[int((xi+4)/dlx)+1]++;
	if(p%1==0)printf("\rPasos: %i conteos: %i", p, conteos);
	if(p%actu==0)imprime_gdrx();
}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_gdrx(void){
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdrx_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%i	%f\n", (i-0.5)*dlx-4, gdrx[i], gdrx[i]/(1.0*conteos));
		}
	fclose(dat);
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





