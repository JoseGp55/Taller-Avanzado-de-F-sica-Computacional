#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define pi 3.14159265359
#define max 4000

struct pelota{
	float x, y, z;
	float vx, vy, vz;//el el desplazamiento, no es velocidad
}ball[max];

void grafica(void);
void mueve(void);
double alea(void);
void crea(void);
void inicio(int a);
void choque(int a);
int signo(float a);
void lee_entrada(void);
void imprime_entrada(void);

//valores de entrada
int pasos, n_max;
float xc, yc, zc, r_grande, xf, yf, zf, alfa, beta;
//valores globales
int p, n=0, ni;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
main(){
	srand((unsigned)time(NULL));
	system ("mkdir pelotas");
	lee_entrada();
	imprime_entrada();
	for (p=1; p<=pasos; p++){	
		if(n<=n_max) crea();
		mueve();
		grafica();
		printf("\r%0.2f%%", p*100.0/pasos);
	}
	printf("\nFin");
	return(0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
	return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lee_entrada(void){
	FILE* dat;
	dat=fopen("Entrada.txt","r");
	fscanf(dat,"Pasos: %i", &pasos);
	fscanf(dat,"\nNumero de pelotas: %i", &n_max);
	fscanf(dat,"\nCamara: %f, %f, %f", &xc, &yc, &zc);
	fscanf(dat,"\nRadio de esfera: %f", &r_grande);
	fscanf(dat,"\nPosicion fuente: %f, %f, %f", &xf, &yf, &zf);
	fscanf(dat,"\nDireccion: %f, %f", &alfa, &beta);//alfa horizontal y beta vertical--- 0,0 es el eje x positivo
	fclose(dat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprime_entrada(void){
	printf("Pasos: %i", pasos);
	printf("\nNumero de pelotas: %i", n_max);
	printf("\nCamara: %f, %f, %f", xc, yc, zc);
	printf("\nRadio de esfera: %f", r_grande);
	printf("\nPosicion fuente: %f, %f, %f", xf, yf, zf);
	printf("\nDireccion: %f, %f\n", alfa, beta);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void crea(){
	float pln, vrt;
	n++;
	ball[n].x=xf;
	ball[n].y=yf;
	ball[n].z=zf;
	pln=(alfa+(alea()*10)-5)*pi/180;
	vrt=(beta+(alea()*10)-5)*pi/180;
	ball[n].vx=cos(pln)*cos(vrt)*0.5;
	ball[n].vy=cos(pln)*sin(vrt)*0.5;
	ball[n].vz=sin(pln)*0.5;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mueve(void){
	int i;
	for (i=1; i<=n; i++){
		ball[i].x+=ball[i].vx;
		ball[i].y+=ball[i].vy;
		ball[i].z+=ball[i].vz;
		choque(i);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void choque(int a){
	float dist, tiempo=0, vxt, vyt,vzt, dif, theta, phi, sint, sinp, cost, cosp, xx, yy, zz;
	dist=sqrt(pow(ball[a].x,2)+pow(ball[a].y,2)+pow(ball[a].z,2));
	if (dist<0.2+r_grande){
		do{//regresarla
			ball[a].x-=ball[a].vx*0.1;
			ball[a].y-=ball[a].vy*0.1;
			ball[a].z-=ball[a].vz*0.1;
			dist=sqrt(pow(ball[a].x,2)+pow(ball[a].y,2)+pow(ball[a].z,2));
			tiempo+=0.1;
		}while(dist<r_grande+0.2);
		xx=ball[a].x;
		yy=ball[a].y;
		zz=ball[a].z;
		//angulo theta
		if (zz>0) theta=atan(sqrt(xx*xx+yy*yy)/zz);
		else if (zz<0) theta=pi+atan(sqrt((xx*xx)+(yy*yy))/zz);
		else theta=pi/2;
		//angulo phi
		if (xx>0 && yy>0) phi=atan(yy/xx);
		else if (xx>0 && yy<0) phi=(2*pi)+atan(yy/xx);
		else if (xx==0) phi=pi*signo(yy)/2;
		else phi=pi+atan(yy/xx);
		//**********
		sint=sin(theta);
		cost=cos(theta);
		sinp=sin(phi);
		cosp=cos(phi);
		vxt=ball[a].vx-2*((ball[a].vx*sint*sint*cosp*cosp)+(ball[a].vy*sint*sint*sinp*cosp)+(ball[a].vz*cost*sint*cosp));
		vyt=ball[a].vy-2*((ball[a].vx*sint*sint*cosp*sinp)+(ball[a].vy*sint*sint*sinp*sinp)+(ball[a].vz*sint*sinp*cost));
		vzt=ball[a].vz-2*((ball[a].vx*sint*cosp*cost)+(ball[a].vy*sint*sinp*cost)+(ball[a].vz*cost*cost));
		ball[a].vx=vxt;
		ball[a].vy=vyt;
		ball[a].vz=vzt;
		ball[a].x+=ball[a].vx*tiempo;
		ball[a].y+=ball[a].vy*tiempo;
		ball[a].z+=ball[a].vz*tiempo;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int signo(float a){
	if(a>0) return(1);
	else if (a<0) return(-1);
	else return (0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void grafica(void){
	char nombre[10];
	int i;
	FILE *dat;
	sprintf(nombre,"pelotas/%i.pov", p);
	dat=fopen(nombre, "w");
	fprintf(dat,"#include \"colors.inc\"\ncamera{\n	location<%f,%f,%f>\n	look_at<-20,0,0>\n}\n", xc, yc, zc);
	fprintf(dat,"light_source{\n	<-20, 50, 0>\n	White\n}\n");
	fprintf(dat,"sphere{\n	<0,0,0> %f\n	pigment{ Gray }\n	finish {ambient 0.4}\n}\n", r_grande);
	fprintf(dat,"sky_sphere{\n	pigment{\n		gradient y\n		color_map{\n			[0 color White]\n			[1 color Blue]\n		}\n		scale 2\n		translate<0,1,0>\n	}\n}\n");
	for (i=1; i<=n; i++){	
		fprintf(dat,"sphere{\n	<%f,%f,%f> 0.2\n	pigment{ Red }\n	finish {ambient 0.4}\n}\n", ball[i].x, ball[i].y, ball[i].z);
	}
	fclose(dat);
}
