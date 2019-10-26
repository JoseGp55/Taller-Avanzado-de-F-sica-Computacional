#include<iostream>
//#include<conio>
#include<iomanip>
#include "C:\work\cursoprogramacion\intro\matrix_intro.hpp"
int matrix_basic_class2()
{
    matrix m1,m2,m3, m4;
    int r1,c1;
    cout<<"Enter the order of first matrix : ";
    cin>>r1>>c1;
    int r2,c2;
    cout<<"Enter the order of second matrix : ";
    cin>>r2>>c2;
    if(c1!=r2)
     	cout<<"Matrix multiplication not Possible\n";
    else
    {
        cout<<"Enter elements of first matrix:\n";
        m1.read(r1,c1);
        m1.display();
        cout<<"Enter elements of second matrix:\n";
        m2.read(r2,c2);
        m2.display();
        m4 = m3.multiply (m1,m2);
        cout<<"Resultant matrix is :\n";
        m4.display();
    }
    
    return 0;
}
