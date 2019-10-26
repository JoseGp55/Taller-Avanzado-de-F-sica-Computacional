//distribución gaussiana de pariculas y de velocidades de Maxwell-Boltzmann
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define CLASES 500
#define MAXPART 500// particulas maximas a manejar
#define pi 3.14159265358979323846
#define kb 1.38062e-23

double alea(void);
void imprime_gdr(void);//cambiar gdr
void asigna_posiciones(void);//funciones nuevas
void salida3d(void);

struct io{//estructura
	float x, y, z;
	int carga;
}ion [MAXPART];

int n, np=100, nn=100;
int p, pasos=10000000, actu=100000;
float temp=300;
float m=1.67e-27;

float ancho=20;//nueva definicion
float dl=ancho/CLASES;

long int gdx[CLASES+1]={0}, gdy[CLASES+1]={0}, gdz[CLASES+1]={0};//
FILE *dat;

//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

system ("mkdir temp");
	
	asigna_posiciones();
	
//for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
//if(p%1==0)printf("\rPasos: %i", p);
	//if(p%actu==0){
	imprime_gdr();
	salida3d();
	//}
//}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_gdr(void){
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdr_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%i	%f	%i	%f	%i	%f\n", (i-0.5)*dl, gdx[i], gdx[i]/(1.0*p), gdy[i], gdy[i]/(1.0*p), gdz[i], gdz[i]/(1.0*p));//distribucion en las tres componentes de r
		}
	fclose(dat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void asigna_posiciones(void){
int i;
float xi, fxi;//declaramos i y novimos las otras declaraciones
	n=np+nn;
	for(i=1; i<=n; i++){
		if (i<=np) ion[i].carga=1;
		else ion[i].carga=-1;
		do{
			xi=alea()*ancho;
			fxi=exp(-pow(xi-ancho/2,2)/2)/sqrt(2*pi);
		}while(alea()>fxi);
		ion[i].x=xi;
		do{
			xi=alea()*ancho;
			fxi=exp(-pow(xi-ancho/2,2)/2)/sqrt(2*pi); 
		}while(alea()>fxi);
		ion[i].y=xi;
		do{
			xi=alea()*ancho;
			fxi=exp(-pow(xi-ancho/2,2)/2)/sqrt(2*pi);
		}while(alea()>fxi);
		ion[i].z=xi;
	}
	salida3d();
	p=n;//truco;
	imprime_gdr();//salida 0
	gdx[CLASES+1]={0};
	gdy[CLASES+1]={0};
	gdz[CLASES+1]={0};//reinicializar estadisticas
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void salida3d(void){
		int m;
		FILE *dat;
		char nombre[30];
		sprintf(nombre, "temp/salida3d%i.dat", p/actu);
			dat=fopen(nombre, "w");
			fprintf(dat, "Execute[{");
			for (m=1; m<=n;m++){
				if(ion[m].carga==1)fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=0.25\",\"SetColor[S%i,Blue]\"", m, ion[m].x, ion[m].y, ion[m].z, m);
				else fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=0.25\",\"SetColor[S%i,Red]\"", m, ion[m].x, ion[m].y, ion[m].z, m);
				if(m<n)fprintf(dat, ",");
			}
		fprintf(dat, "}]");
		fclose(dat);
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





