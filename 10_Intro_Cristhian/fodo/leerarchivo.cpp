
#include "matrix_intro3.hpp"
//code using to transport a particle distribution in a FODO LINE
int main()
{
   
    //  NUMBERS  
    int ii=0;
    const int nn=1000;
    double x1,xp1,y1,yp1,a;
    float x[nn], y[nn],xp[nn], yp[nn];
       //HISTOGRAMS CANVAS AND GRAPH
  //  TCanvas *ca1 = new TCanvas("ca1","beamline size",200,100,1200,400);
  //  TH2* h123x = new TH2F("h123x", "Phase SPACEX", 100, -0.01,0.01, 100, -0.005, 0.005);
    
    //******************************************************************* 
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
        cout<<xp[ii]<<endl;
       //  h123x->Fill(x[ii],xp[ii]);
        
    }
    //plot file
       // h123x->Draw("colz");
        
           
    
    return 0;
}

