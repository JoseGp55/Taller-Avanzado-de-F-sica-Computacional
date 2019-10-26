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
//code using to transport a particle distribution in a FODO LINE
int distribution()
{
    gROOT->Reset();
    
    matrix mquadx,mquady, m4,Fodox,Fodoy,drift1,mtemp;
    matrix m6(2,2);
    matrix qd(2,2);
    matrix qf(2,2);
    matrix m1x(2,1);
    matrix m1y(2,1);
    m1x.update(0,0,0.01);
    m1x.update(1,0,0.02);
    //  NUMBERS  
    int r1,c1;
    r1=2;
    c1=1;
    int ii=0;
    int aux=0;
    const int nn=2000;
    double kq=1.8;
    double ld=0.2;    
    double x1,xp1,y1,yp1,a;
    x1=0;
    xp1=0;
    float x[nn], y[nn],xp[nn], yp[nn];
    float z[2000],bszx[2000],bszy[2000];
    //HISTOGRAMS CANVAS AND GRAPH
    TCanvas *ca1 = new TCanvas("ca1","beamline size",200,100,1200,400);
    TH2* h123x = new TH2F("h123x", "PHASE SPACE X", 100, -0.01,0.01, 100, -0.005, 0.005);
    TH2* h123y = new TH2F("h123y", "PHASE SPACE Y", 100, -0.01,0.01, 100, -0.005, 0.005);
    TH2* h122 = new TH2F("h122", "BEAM PROFILE ", 100, -0.01,0.01, 100, -0.01, 0.01);
	///make it pretty
	h122->GetXaxis()->SetRangeUser(-0.1,0.1);
	h122->GetYaxis()->SetRangeUser(-0.1,0.1); 
	h122->GetXaxis()->SetNdivisions(5);
	h122->GetYaxis()->SetNdivisions(5);
	h122->GetYaxis()->SetTitle(" Y (m)");
	h122->GetXaxis()->SetTitle(" X (m)");
	h122->GetYaxis()->SetTitleOffset(1.2);
	//h122->GetXaxis()->CenterTitle();
	h123x->GetXaxis()->SetRangeUser(-0.1,0.1);
	h123x->GetYaxis()->SetRangeUser(-0.005,0.005);
	h123x->GetXaxis()->SetNdivisions(5);
	h123x->GetYaxis()->SetNdivisions(5);
	h123x->GetYaxis()->SetTitle(" X' (rad)");
	h123x->GetXaxis()->SetTitle(" X (m)");
	
    //*******************************************************************
    //CREATE THE TRANSPORT MATRIXS 
    
    drift1.drift(ld);
    qd.thin_quad(ld,-kq);
    qf.thin_quad(ld,kq);
    qd.display();
    qf.display();
    Fodox=m4.multiply(drift1,qf);
    Fodox=m4.multiply(qd,Fodox);
    Fodox=m4.multiply(drift1,Fodox);
    
    Fodoy=m4.multiply(drift1,qd);
    Fodoy=m4.multiply(qf,Fodoy);
    Fodoy=m4.multiply(drift1,Fodoy);
    mquadx=Fodox;
    mquady=Fodoy;
    mquadx.display();
    mquady.display();
    //READ THE FILE
    ifstream archivo("fodotestgaussiantilt.txt");
    string dummyLine;
    getline(archivo, dummyLine);
    while(!archivo.eof()){
        
        ii=ii+1;
        if(ii==nn){break;}
        //sol1
        archivo >> a;
        x[ii]=a;
        archivo >> a;
        xp[ii]=a;
        //size y
        archivo >> a;
        y[ii]=a;
        archivo >> a;
        yp[ii]=a;
        
    }
    archivo.close();
    aux=0;
    cout<<"***************************"<<endl;
    ca1->Divide(3,1);
    for(int i=0;i<50;i=i+1){ 
        
        h123x->Reset("");
        h123y->Reset("");
        h122->Reset("");
               
        for(int ll=0;ll<nn;++ll){ 
            
            m1x.update(0,0,x[ll]);
            m1x.update(1,0,xp[ll]);
            m1y.update(0,0,y[ll]);
            m1y.update(1,0,yp[ll]);
			
            m1x=m4.multiply(fodo,m1x);
            m1y=m4.multiply(fodo,m1y);
			//
			
            x1 = m1x(0,0);
            xp1 = m1x(1,0);
            y1 = m1y(0,0);
            yp1 = m1y(1,0);
			
            h123x->Fill(x1,xp1);
            h123y->Fill(y1,yp1);
            h122->Fill(x1,y1);
            
        }
        mquadx=m4.multiply(Fodox,mquadx);
        mquady=m4.multiply(Fodoy,mquady);
       // mquadx.display();
        
        double varxroot=h123x->GetRMS(1);
        double varyroot=h123y->GetRMS(1);
        z[aux]=i;
        bszx[aux]=varxroot;
        bszy[aux]=varyroot;
         aux+=1;
        ca1->cd(1);
        
        h123x->Draw("colz");
        ca1->cd(2);
        h123y->Draw("colz");
        ca1->cd(3);
        h122->Draw("colz");
         ca1->Modified();
    	 ca1->Update();
		 ca1->SaveAs("ddesl.png");
           }
    
    return 0;
}

