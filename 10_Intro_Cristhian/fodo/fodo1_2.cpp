#include<iostream>
//#include<conio>
//#include<TCanvas>

#include<iomanip>
#include "matrix_intro3.hpp"
int main()
{
    matrix m1y,mquadx,mquady, m4,m3,drift1;
  
    int r1,c1;
     double kq=0.8;
    double ld=0.3; 
    //TGraph* gr = new TGraph(n,x,y); 
   // TCanvas ca1();
         //   ca1= cal.TCanvas("ca1","beamline size",200,100,1200,400);
   // matrix *m34= new matrix;
    //m34=new //
 
    //cout<<"Enter the order of first matrix : ";
    r1=2;
    c1=1;
      matrix mlx(r1,c1);
    mlx.update(0,0,0.01);
    mlx.update(1,0,0.02);
       mlx.display();
    cout<<"Enter elements of first matrix:\n";

    
     m3.thin_quad(ld,kq);
    drift1.drift(ld);
    cout<<"mult"<<endl;
    m3=m4.multiply(drift1,m3);
    m4.thin_quad(ld,-kq);
    m3=m4.multiply(m4,m3);
    m3=m4.multiply(drift1,m3);
    mlx.display();
    m3.display();
    cout<<"***************************"<<endl;
 		mlx=m4.multiply(m3,mlx);
 		mlx.display();
    
    return 0;
}
