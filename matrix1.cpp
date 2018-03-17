#include<iostream>
#include<vector>
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>
#include<boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace std;

typedef std::vector<vector<double> > mdatatype;
class matrix
{
public:
    
    short rows, columns;
    char *matrix_name;
    mdatatype Matrix;
    double determinant();
    matrix();
    matrix(int m,int n);
    matrix adjoint();
    matrix cofactor();
    matrix transpose();
    matrix inverse();
    
    //matrix &operator=(matrix ob) ;
    
    matrix operator+(matrix ob) ;
    
    matrix operator-(matrix ob) ;
    
    matrix operator*(matrix ob);
    
};

//***********************************************************************

//constructors
matrix::matrix()//default constructor
{
    rows=0;
    columns=0;
   //Matrix=0;
    matrix_name=0;
}

matrix::matrix(int m, int n)
{
    if(n==0||m==0)
    {
        cout<< endl <<"Error !!! Matrix cannot have zero number of rows or columns"<<endl;;
        //exit(1);
    }
    rows=m;
    columns=n;
    matrix_name=0;
    
    Matrix.resize(rows);
    for (short i=0;i<rows;++i)
    {
        Matrix[i].resize(columns);
    }
}

//**********************************************************************

double matrix :: determinant()
{
    if(rows!=columns)
    {
        cout << "not possible for unequal number of rows and columns" << endl;
        //exit(1);
    }
    if (rows==1)
        return Matrix[0][0];
    else if (rows ==2)
        return Matrix[0][0]*Matrix[1][1] - Matrix[1][0]*Matrix[0][1];
    else
    {
    	vector<matrix>temp;
    	temp.resize(rows);
       // matrix **temp = new matrix*[rows];
        for(int i = 0; i < rows; i++)
        	temp[i] = matrix(rows-1,columns-1);
            //temp[i] = new matrix(rows - 1,columns - 1);
        
        for(int k = 0; k < rows; k++)
        {
            
            for(int i = 1; i < rows; i++)
            {
                int j1 = 0;
                for(int j = 0; j < rows; j++)
                {
                    if(k == j)
                        continue;
                    temp[k].Matrix[i-1][j1++] = Matrix[i][j];
                }
            }
        }
        
        double det = 0;
        for(int k = 0; k < rows; k++)
        {
            if( (k %2) == 0)
            {
                det = det + (Matrix[0][k] * temp[k].determinant());

            }
            else
            {
                det = det - (Matrix[0][k] * temp[k].determinant());
                
            }
        }
        return det;
    }
    
}
//**********************************************************************
matrix matrix :: cofactor()
{
    matrix cofactor(rows, columns);
    if(rows != columns)
    {
        cout << "not possible since number of rows != number of columns" << endl;
        //exit(1);
    }
    
    if(rows < 2)
        return *this;
    
    else if(rows == 2)
    {
        cofactor.Matrix[0][0] = Matrix[1][1];
        cofactor.Matrix[0][1] = -Matrix[1][0];
        cofactor.Matrix[1][0] = -Matrix[0][1];
        cofactor.Matrix[1][1] = Matrix[0][0];
        return cofactor;
    }
    else if(rows > 2)
    {
        int DIM = rows;
        //matrix ***temp = new matrix**[DIM];
        vector<vector<matrix> > temp;       
        temp.resize(rows);
        for(int i = 0; i < DIM; i++)
        	temp[i].resize(columns);
        
           // temp[i] = new matrix*[DIM];
        for(int i = 0; i < DIM; i++)
            for(int j = 0; j < DIM; j++)
                temp[i][j] = matrix (DIM - 1,DIM - 1);
        
        for(int k1 = 0; k1 < DIM; k1++)
        {
            for(int k2 = 0; k2 < DIM; k2++)
            {
                int i1 = 0;
                for(int i = 0; i < DIM; i++)
                {
                    int j1 = 0;
                    for(int j = 0; j < DIM; j++)
                    {
                        if(k1 == i || k2 == j)
                            continue;
                        temp[k1][k2].Matrix[i1][j1++] = this->Matrix[i][j];
                    }
                    if(k1 != i)
                        i1++;
                }
            }
        }
        
        bool flagPositive = true;
        for(int k1 = 0; k1 < DIM; k1++)
        {
            flagPositive = ( (k1 % 2) == 0);
            
            for(int k2 = 0; k2 < DIM; k2++)
            {
                if(flagPositive == true)
                {
                    cofactor.Matrix[k1][k2] = temp[k1][k2].determinant();
                    flagPositive = false;
                }
                else
                {
                    cofactor.Matrix[k1][k2] = -temp[k1][k2].determinant();
                    flagPositive = true;
                }
            }
            
        }
        
        temp.clear();
    }
    return cofactor;
}
//**********************************************************************
matrix matrix :: adjoint()
{
    matrix cofactor( rows, columns);
    matrix adj(rows, columns);
    if(rows != columns)
    {
        cout << "not possible since number of rows != number of columns" << endl;
        //exit(1);
    }
    
    cofactor.Matrix = this->cofactor().Matrix;
    
    // adjoint is transpose of a cofactor of a matrix
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            adj.Matrix[j][i] = cofactor.Matrix[i][j];
        }
    }
    return adj;
}
//**********************************************************************

matrix matrix ::transpose()
{
    matrix trans( columns, rows);
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            trans.Matrix[j][i] = Matrix[i][j];
        }
    }
    return trans;
}
//**********************************************************************
matrix matrix :: inverse()
{
    matrix cofactor(rows, columns);
    matrix inv(rows, columns);
    if(rows != columns)
        return inv;
    
    // to find out determinant
    double det = determinant();
    
    cofactor.Matrix = this->cofactor().Matrix;
    
    // inv = transpose of cofactor / determinant
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            inv.Matrix[j][i] = cofactor.Matrix[i][j] / det;
        }
    }
    return inv;
}

//**********************************************************************

//OPERATOR OVERLOAD

/*matrix &matrix::operator=(matrix ob)
{
    if(Matrix!=0)
    {
        for (short j=0; j<columns; ++j)
        {
            if(Matrix[j]!=0)
                delete []Matrix[j];
        }
        if(Matrix!=0)delete []Matrix;
        Matrix=0;
    }
    
    rows=ob.rows;
    columns=ob.columns;
    
    Matrix=new float * [columns];
    
    for (short i =0;i <columns;++i)
    {
        Matrix[i]=0;
    }
    
    for (short i=0;i<columns;++i)
    {
        Matrix[i]=new float[rows];
    }
    
    for (short j=0; j<columns; ++j)
    {
        for (short i=0;i<rows;i++)
        {
            Matrix[j][i]=ob.Matrix[j][i];
        }
    }
    
    return *this;
}*/

/*bool matrix::operator==(const matrix &ob) const
 {
 if(rows!=ob.rows||columns!=ob.columns) return 0;
 
 for (short i = 0; i <columns ; ++i)
 {
 for (short j = 0; j <rows ; ++j)
 {
 if(Matrix[i][j]!=ob.Matrix[i][j])
 return 0;
 }
 }
 
 return 1;
 }*/


matrix matrix::operator+(matrix ob) 
{
    if(ob.columns!=columns||ob.rows!=rows)
    {
        cout<< endl <<"Error on attempt to add matrixes of different dimensions" << endl;
        //exit(1);
        //return (matrix) this;
    }
    
    matrix temp(rows,columns);
    
    
    for (short i =0; i <rows; ++i)
    {
        for (short j = 0; j <columns; ++j)
        {
            temp.Matrix[i][j]=(Matrix[i][j])+(ob.Matrix[i][j]);
        }
    }
    
    return temp;
}

matrix matrix::operator-(matrix ob)
{
    if(ob.columns!=columns||ob.rows!=rows)
    {
        cout<< endl <<"Error on attempt to subtract matrixes of different dimensions" << endl;
        //exit(1);
    }
    
    matrix temp(rows,columns);
    
    for (short i =0; i <rows; ++i)
    {
        for (short j = 0; j <columns; ++j)
        {
            temp.Matrix[i][j]=(Matrix[i][j])-(ob.Matrix[i][j]);
        }
    }
    
    return temp;
}

matrix matrix::operator*(matrix ob)
{
    if(columns!=ob.rows)
    {
        cout<< endl <<"Error on attempt to multiply matrixes due to dimension error" << endl ;
        //exit(1);
        //return (matrix) this;
    }
    
    matrix temp(rows, ob.columns);
    
    /*matrix temp1;
     matrix *present;
     present=(matrix *)this;
     temp1 = *present;*/
    
    
    for(short i=0;i< rows;i++)
    {
        for(short j=0;j< ob.columns;j++)
        {
            temp.Matrix[i][j] = 0;
            for(short k=0;k< columns;k++)
            {
                temp.Matrix[i][j] += Matrix[i][k] * ob.Matrix[k][j];
            }
        }
    }
    return temp;
    
}

using namespace boost::python;
BOOST_PYTHON_MODULE(matrix1)
{
    class_<vector<double> >("mdatatype1")
        .def(vector_indexing_suite<vector<double> > ());
    class_<std::vector<vector<double> > >("mdatatype")
        .def(vector_indexing_suite<std::vector<vector<double> > >());
		
    class_<matrix>("matrix")
        .def("inverse",&matrix::inverse)
        .def("adjoint",&matrix::adjoint)
        .def("cofactor",&matrix::cofactor)
        .def("transpose",&matrix::transpose)
        .def("determinant",&matrix::determinant)
        .def(init<>())
        .def(init<int ,int >())
        .def_readwrite("rows",&matrix::rows)
        .def_readwrite("columns",&matrix::columns)
        .def_readwrite("matrix_name",&matrix::matrix_name)
        .def_readwrite("Matrix",&matrix::Matrix)
        .def(self+self)
        .def(self-self)
        .def(self*self)
  ;      
    
}

/*class matrix-
 short rows, columns;
 char *matrix_name;
 float **Matrix;
 float determinant();
 matrix();
 matrix(int m,int n);
 matrix adjoint();
 matrix cofactor();
 matrix transpose();
 matrix inverse();
 
 matrix &operator=(matrix &ob) ;
 
 matrix operator+(matrix &ob) const;
 
 matrix operator-(matrix &ob) const;
 
 matrix operator*(matrix ob);
*/


















