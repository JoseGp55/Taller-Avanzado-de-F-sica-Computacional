#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include<iostream>
//#include<conio>
#include<iomanip>

using namespace std;

const int ROW=5;
const int COL=5;

class matrix
{
    int a[ROW][COL];
    int row;
    int col;
public:
    matrix () : row(0), col(0)
    {}
    void read(int r, int c);
    void display();
    matrix multiply (matrix m1, matrix m2);
};

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
            cout<<setw(4)<<a[i][j];
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