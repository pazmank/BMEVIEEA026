#ifndef MAT_H
#define MAT_H

#include <iostream>
#include "vect.h"

template <typename T> class Mat;

template <typename T> Mat<T> operator* (const T &, const Mat<T> &);
template <typename T> std::ostream & operator<< (std::ostream &, const Mat<T> &);
template <typename T> std::istream & operator>> (std::istream &, Mat<T> &);

//Matrix class declaration
template <typename T>
class Mat{
    private:
        int rows_, cols_;  //number of rows and columns
        Vect<T> **array;   //pointer to array of vectors (rows)        
    public:
        Mat(int = 0, int = 0);  //creates matrix with a given size (defaut 0, 0)
        Mat(const Mat<T> &);  //copy constructor
        ~Mat();    //frees the dynamically allocated arrays

        Vect<T> operator[](int) const;  //returns a row by value (so M[i][j] returns an element)
        Vect<T> & operator[](int);  //returns a row by reference (so M[i][j] returns an element)
        //the above allows M[i]=v assigment, where v.size()!=M.cols TODO: fix
        Vect<T> col(int) const;  //returns a column as a vector
        Mat<T> & operator=(const Mat<T> &);   //assignment

        const Mat<T> operator+(const Mat<T> &) const;  //elementwise addition
        const Mat<T> operator-(const Mat<T> &) const;  //elementwise substraction
        const Mat<T> operator*(const Mat<T> &) const;  //elementwise multiplication
        const Mat<T> operator/(const Mat<T> &) const;  //elementwise division

        const Mat<T> operator*(const T &) const;  //multiplication by scalar (right side)
        const Mat<T> dot(const Mat<T> &) const; //matrix mutipication
        const Mat<T>  transp(void) const;  //transpose
        const T det(void) const;  //determinant TODO

        const int rows(void) const; //returns the number of rows
        const int cols(void) const; //returns the number of columns
        void print(void) const; //writes the elements to the stdout
        void fprint(char*) const; //writes the elements to a file
        void fread(char*); //reads the elements from a file TODO
        void rand(double = 10); //fills the matrix with random values

        friend Mat<T> (::operator* <>)(const T &, const Mat<T> &);    //multiplication by scalar (left side)

        friend std::ostream & operator<< <>(std::ostream &, const Mat<T> &); //out << Mat
        friend std::istream & operator>> <>(std::istream &, Mat<T> &);    //in >> Mat TODO
};

#endif 
