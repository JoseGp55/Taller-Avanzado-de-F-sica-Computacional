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
    for(int i=0; i<temp.row; i++)
 	for(int j=0; j<temp.col; j++)
 	{
            temp.a[i][j]=0;
            {            
                for (int k=0; k<temp.col; k++)
                    temp.a[i][j] += m1.a[i][k]*m2.a[k][j];
                        }
 	}
    return temp;
}
int matrix_basic_class()
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
