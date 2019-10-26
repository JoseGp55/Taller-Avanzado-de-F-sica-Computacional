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
#define esc 1e-9//mas definiciones, para calculo de la energia 
#define epce 8.85419e-12
#define qe 1.60219e-19

double alea(void);
void imprime_gdr(void);
void gdr(void);
void asigna_posiciones(void);
void salida3d(void);
void selecciona_ion(void);
void mueve_ion(void);
void condiciones_periodicas(void);
int signo(float a);
void metropolis(void);//nuevas funciones
float variacion_energia(void);
float distancia(int a, int b);

struct io{//estructura
	float x, y, z;
	int carga;
}ion [MAXPART];

int ni, n, np=100, nn=100;
int p, pasos=10000000, actu=1000;
float temp=300;
float m=1.67e-27, diam=1;//nueva definicion

float ancho=20;
float dl=ancho/CLASES;
float dx=2.0, dy=2.0, dz=2.0;

int aceptacion=0, rechazo=0, rechazo_traslape=0, rechazo_metropolis=0;//nuevas definiciones

long int gdxp[CLASES+1]={0}, gdyp[CLASES+1]={0}, gdzp[CLASES+1]={0}, gdxn[CLASES+1]={0}, gdyn[CLASES+1]={0}, gdzn[CLASES+1]={0};//positivos y negativos por separado
FILE *dat;

//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

system ("mkdir temp");
asigna_posiciones();
for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	selecciona_ion();
	mueve_ion();
	condiciones_periodicas();
	metropolis();			
	gdr();
	if(p%1==0)printf("\rPaso: %i Aceptacion=%f rechazo metropolis: %f rechazo traslape: %f", p, aceptacion*1.0/p, rechazo_metropolis*1.0/p, rechazo_traslape*1.0/p);
	if(p%actu==0){
		imprime_gdr();
		salida3d();
	}
}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gdr(void){//modificaciones
	int i;
	for(i=1; i<=n; i++){
		if(ion[i].carga==1){
			gdxp[int(ion[i].x/dl)+1]++;	
			gdyp[int(ion[i].y/dl)+1]++;	
			gdzp[int(ion[i].z/dl)+1]++;
		}else{
			gdxn[int(ion[i].x/dl)+1]++;	
			gdyn[int(ion[i].y/dl)+1]++;	
			gdzn[int(ion[i].z/dl)+1]++;	
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_gdr(void){//modificaciones
	int i;
	FILE *dat;
	char nombre[50];
	sprintf(nombre,"temp/gdr_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=CLASES; i++){
			fprintf(dat,"%f	%f	%f	%f	%f	%f	%f\n", (i-0.5)*dl, gdxp[i]/(1.0*p), gdyp[i]/(1.0*p), gdzp[i]/(1.0*p), gdxn[i]/(1.0*p), gdyn[i]/(1.0*p), gdzn[i]/(1.0*p));//distribucion en las tres componentes de r
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
	gdr();//importante llamada
	imprime_gdr();//salida 0
	gdxp[CLASES+1]={0};//reinicializar estadisticas
	gdyp[CLASES+1]={0};
	gdzp[CLASES+1]={0};
	gdxn[CLASES+1]={0};
	gdyn[CLASES+1]={0};
	gdzn[CLASES+1]={0};
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
				if(ion[m].carga==1)fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=%f\",\"SetColor[S%i,Blue]\"", m, ion[m].x, ion[m].y, ion[m].z, pow(diam/2,2), m);
				else fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=%f\",\"SetColor[S%i,Red]\"", m, ion[m].x, ion[m].y, ion[m].z, pow(diam/2,2), m);
				if(m<n)fprintf(dat, ",");
			}
		fprintf(dat, "}]");
		fclose(dat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void selecciona_ion(void){
	do{
		ni=int(alea()*n)+1;
	}while(ni>n);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mueve_ion(void){
	ion[0]=ion[ni];
	ion[ni].x+=(alea()-0.5)*dx;
	ion[ni].y+=(alea()-0.5)*dy;
	ion[ni].z+=(alea()-0.5)*dz;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void condiciones_periodicas(void){//check backwards
	if((ion[ni].x<0) || (ion[ni].x>=ancho)){
		ion[ni].x+=ancho*signo(-ion[ni].x);
	}
	if((ion[ni].y<0) || (ion[ni].y>=ancho)){
		ion[ni].y+=ancho*signo(-ion[ni].y);
	}
	if((ion[ni].z<0) || (ion[ni].z>=ancho)){
		ion[ni].z+=ancho*signo(-ion[ni].z);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int signo(float a){
	if(a>0) return(1);
	else if (a<0) return(-1);
	else return (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void metropolis(void){
	double argexp;
		argexp=(-1)*variacion_energia()/(kb*temp);
	if(rechazo==0){
		if (exp(argexp)>alea()){
			aceptacion++;
			//printf"
		}else{
			ion[ni]=ion[0];
			rechazo_metropolis++;
		}
	}else{//el programa solo entra aca si hubo traslape de esferas
		ion[ni]=ion[0];
		rechazo_traslape++;
		rechazo=0;//muy importante
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float variacion_energia(void){
	int i;
	float ecoul_i=0, ecoul_f=0, den, cte=qe*qe/(4*pi*epce*78.5);//aqui introduje la permitividad dielectrica relativa del agua a 300 K para suavizar las interacciones
	for (i=1; i<=n;i++){
		if((i!=ni)&&(distancia(ni,i)>=diam)){
			ecoul_i+=cte*ion[0].carga*ion[i].carga/(distancia(0,i)*esc);
			ecoul_f+=cte*ion[ni].carga*ion[i].carga/(distancia(ni,i)*esc);
			}/*else if((i!=ni)&&(distancia(ni,i)<diam)){//en esta parte se revisa si los iones se traslapan y de ser asi se rechaza el movimiento se corta el calculo y la variable rechazo cambia de valor para que no se efectue el algoritmo de Metropolis
			rechazo=1;
			return (den);
		}*/
	//condicion 1
		ecoul_i+=cte*ion[0].carga*1/(sqrt(pow((ion[0].x-10),2)+pow((ion[0].y-10),2)+pow((ion[0].z-10),2))*esc);//en estas dos lineas se pone una carga positiva de 1 carga electrica fundamental en el centro de la celda (10,10,10) la interaccion tiene simetria esferica
		ecoul_f+=cte*ion[ni].carga*1/(sqrt(pow((ion[ni].x-10),2)+pow((ion[ni].y-10),2)+pow((ion[ni].z-10),2))*esc);
	//condicion 2
		ecoul_i+=cte*ion[0].carga*1/(sqrt(pow((ion[0].x-10),2)+pow((ion[0].y-10),2))*esc);//en estas dos lineas se pone una carga positiva de 1 carga electrica fundamental en el centro de la celda (10,10,10) la interaccion tiene simetria cilindrica
		ecoul_f+=cte*ion[ni].carga*1/(sqrt(pow((ion[ni].x-10),2)+pow((ion[ni].y-10),2))*esc);
	//condicion 3	
		ecoul_i+=cte*ion[0].carga*1/(sqrt(pow((ion[0].z-10),2))*esc);//en estas dos lineas se pone una carga positiva de 1 carga electrica fundamental en el centro de la celda (x=10) la interaccion tiene simetria plana
		ecoul_f+=cte*ion[ni].carga*1/(sqrt(pow((ion[ni].z-10),2))*esc);		
	}
	den=ecoul_f-ecoul_i;
	//printf("Den=%1.6e\n",den);
	return(den);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float distancia(int a, int b){
	float dist, xx, yy, zz;
	xx=ion[b].x;
	yy=ion[b].y;
	zz=ion[b].z;
	if (fabs(ion[a].x-xx)>10)xx+=20*signo(ion[a].x-xx);
	if (fabs(ion[a].y-yy)>10)yy+=20*signo(ion[a].y-yy);
	if (fabs(ion[a].z-zz)>10)zz+=20*signo(ion[a].z-zz);
	dist=sqrt(pow((ion[a].x-xx),2)+pow((ion[a].y-yy),2)+pow((ion[a].z-zz),2));
	return(dist);
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





