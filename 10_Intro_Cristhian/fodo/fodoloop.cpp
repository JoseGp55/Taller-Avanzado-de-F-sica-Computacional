#include <iomanip>
#include <sstream>
#include <limits.h>
#include <iostream>
#include <TMath.h>
#include <TString.h>
#include <TGraph2D.h>
#include <TH1.h>
#include <TRoot.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include "Riostream.h"
#include <TLegend.h>
#include "matrix_intro3.hpp"
//code using the matrixmultiplication one time to pass the FODO and create a LOOP
int fodoloop()
{
    gROOT->Reset();
    // Define variables here
    //double a[2][2];
    matrix mquadx,mquady, m4,m3,drift1,mtemp;
    matrix m6(2,2);
    matrix m1x(2,1);
    int r1,c1;
    r1=2;
    c1=1;
    double x [1000], xp [1000],z[1000]; 
    
    
    m1x.update(0,0,0.01);
    m1x.update(1,0,0.02);
    

    int i=0;
    int nn=10;
    double kq=0.8;
    double ld=0.3;    
    double x1,xp1,y1,yp1,a;
    x1=0;
    xp1=0;
    
    //createthefodomatrix
    m3.thin_quad(ld,kq);
    drift1.drift(ld);
    cout<<"mult"<<endl;
    m3=m4.multiply(drift1,m3);
    m4.thin_quad(ld,-kq);
    m3=m4.multiply(m4,m3);
    m3=m4.multiply(drift1,m3);
    m1x.display();
    m3.display();
    cout<<"***************************"<<endl;
    
    
    for(int i=0;i<200;++i){ 
        
        m1x=m4.multiply(m3,m1x);
        x[i] = m1x(0,0);
        xp[i] = m1x(1,0);
        z[i] = i*0.2;
    }
     TCanvas *ca1 = new TCanvas("ca1","beamline size",200,10,500,300);
    TGraph* gr = new TGraph(200,z,x); 
    gr->Draw("AC*"); 
    
    TCanvas *ca2 = new TCanvas("ca2","Phase space",700,10,900,300);
    TGraph* gr2 = new TGraph(200,x,xp); 
    gr2->Draw("AC*");
    
    
    
    
    
    
    
}

