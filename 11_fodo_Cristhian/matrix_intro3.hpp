#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include<iostream>
#include<iomanip>

using namespace std;

const int ROW=3;
const int COL=3;

class matrix
{
    double a[ROW][COL];
    int row;
    int col;
public:
    matrix (int row, int col) : row(row), col(col){}
      matrix () : row(0), col(0){}
    // ~matrix() ;
  //matrix  matrix(int r, int c);
    void read(int r, int c);
    void empty(int r, int c);
    void display();
    double& operator()(int r, int c);
    void  update(int r, int c,double d);
    matrix multiply (matrix m1, matrix m2);
    matrix thin_quad(double L, double K);
    void drift(double L);
    };



void matrix :: empty(int r, int c)
{
    row=r;
    col=c;
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
        {
            cout<<"A["<<i<<"]["<<j<<"] : ";
            a[i][j]=0;
        }
        
}

void matrix :: read(int r, int c)
{
    row=r;
    col=c;
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
        {
            cout<<"A["<<i<<"]["<<j<<"] : ";
            cin>>a[i][j];
        }
        
}

void matrix :: display()
{
    for(int i=0; i<row; i++)
    {
        for (int j=0; j< col; j++)
            cout<<setw(8)<<a[i][j];
        cout<<endl;
    }
}

matrix matrix :: multiply (matrix m1, matrix m2)
{
    matrix temp;
    temp.row=m1.row;
    temp.col=m2.col;
    for(int i=0; i<m1.row; i++)
 	for(int j=0; j<m2.col; j++)
 	{
            temp.a[i][j]=0;
            {            
                for (int k=0; k<m1.col; k++)
                    temp.a[i][j] += m1.a[i][k]*m2.a[k][j];
                        }
 	}
    return temp;
}

double& matrix::operator()(int r, int c) {
    return a[r][c];
}
void matrix::update(int r, int c,double d) {
    //if (row >= m.rows || column >= m_columns) {
    //  throw std::out_of_range("Index out of bounds");
    
    a[r][c]=d;
}

matrix matrix ::thin_quad(double L, double K)
{
    row=2;
    col=2;
    
    a[0][0]= 1;
    a[0][1]= 0;	
    a[1][0]= -L*K;
    a[1][1]= 1;
    
    
}


void matrix ::drift(double L)
{
    row=2;
    col=2;
    
    a[0][0]= 1;
    a[0][1]= L;	
    a[1][0]= 0;
    a[1][1]= 1;
    
    
    
}


