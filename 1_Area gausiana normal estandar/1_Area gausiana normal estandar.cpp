//Calculo del area debajo de una gausiana normal estandar
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define pi 3.14159265358979323846

double alea(void);

int p;
int pasos=1000000000;

//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

int cont_area=0;
float xi, fxi, yi, area;//un cuadrado de 1X1 area total 1

for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	xi=alea()*1;
	fxi=exp(-pow(xi,2)/2)/sqrt(2*pi);
	yi=alea()*1;//cambiar area reducir a la mitad
	if(yi<=fxi){
    	cont_area++;
    }
	area=(float)cont_area*1/p;//cambiar area reducir a la mitad
	if(p%1==0)printf("\r%i %1.8f", p, area);
}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





