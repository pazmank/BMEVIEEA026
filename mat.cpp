#include <stdexcept>
#include <fstream>
#include "vect.h"
#include "mat.h"
#include <random>

//creates matrix with a given size (defaut 0)
template <typename T>
Mat<T>::Mat(int rows, int cols) : rows_(rows), cols_(cols){
    if(rows<0 || cols<0) throw std::invalid_argument("size must be greater than 0,0");
    this->array = new Vect<T>*[this->rows_];
    for(int i=0; i<this->rows_; i++ ){
        this->array[i]=new Vect<T>(this->cols_);
    }
}

//copy constructor
template <typename T>
Mat<T>::Mat(const Mat<T> &M0) : rows_(M0.rows_), cols_(M0.cols_){
    this->array = new Vect<T>*[this->rows_];
    for(int i=0; i<this->rows_; i++ ){
        this->array[i]=new Vect<T>(this->cols_);
    }
    for (int i = 0; i < this->rows_; i++){
      *(this->array[i]) = *(M0.array[i]);   //copy each vector
    }
}

//frees the dynamically allocated arrays
template <typename T>
Mat<T>::~Mat(){
    for(int i=0; i<this->rows_; i++ ){
        delete this->array[i];
    }
	delete[] this->array;
}

//returns a row by value (so M[i][j] returns an element)
template <typename T>
Vect<T> Mat<T>::operator[](int i) const{
    if(i>=this->rows_ || i<0) throw std::out_of_range("array index is out of range");
    return *(this->array[i]);
}

//returns a row by reference (so M[i][j] returns an element)
template <typename T>
Vect<T> & Mat<T>::operator[](int i){
    if(i>=this->rows_ || i<0) throw std::out_of_range("array index is out of range");
    return *(this->array[i]);
}

//returns a column as a vector
template <typename T>
Vect<T> Mat<T>::col(int j) const{
    if(j>=this->cols_ || j<0) throw std::out_of_range("array index is out of range");
    Vect<T> ret(this->rows_);
    for (int i = 0; i < this->rows_; ++i){
        ret[i] = (*(this->array[i]))[j];
    }

    return ret;
}

//assignment operator
template <typename T>
Mat<T> & Mat<T>::operator=(const Mat<T> &M){
    if(this==&M) return *this;

    //frees the dynamically allocated arrays
    for(int i=0; i<this->rows_; i++ ){
        delete this->array[i];
    }
	delete[] this->array;

    //reallocate arrays
    this->rows_=M.rows_;
    this->cols_=M.cols_;
    this->array = new Vect<T>*[this->rows_];
    for(int i=0; i<this->rows_; i++ ){
        this->array[i]=new Vect<T>(this->cols_);
    }

    //copy each vector
    for (int i = 0; i < this->rows_; i++){
      *(this->array[i]) = *(M.array[i]);   
    }

    return *this;
}

//elementwise addition
template <typename T>
const Mat<T> Mat<T>::operator+(const Mat<T> &M) const{
    if(this->rows_!=M.rows_ && this->cols_!=M.cols_ ) throw std::invalid_argument("matrix dimensions do not match");
    Mat<T> res(this->rows_, this->rows_);
    for (int i = 0; i < this->rows_; ++i){
        *(res.array[i])=*(this->array[i])+*(M.array[i]);
    }

    return res;
}

//elementwise substraction
template <typename T>
const Mat<T> Mat<T>::operator-(const Mat<T> &M) const{
    if(this->rows_!=M.rows_ && this->cols_!=M.cols_ ) throw std::invalid_argument("matrix dimensions do not match");
    Mat<T> res(this->rows_, this->rows_);
    for (int i = 0; i < this->rows_; ++i){
        *(res.array[i])=*(this->array[i])-*(M.array[i]);
    }

    return res;
}

//elementwise multiplication
template <typename T>
const Mat<T> Mat<T>::operator*(const Mat<T> &M) const{
    if(this->rows_!=M.rows_ && this->cols_!=M.cols_ ) throw std::invalid_argument("matrix dimensions do not match");
    Mat<T> res(this->rows_, this->rows_);
    for (int i = 0; i < this->rows_; ++i){
        *(res.array[i])=*(this->array[i])* *(M.array[i]);
    }

    return res;
}

//elementwise division
template <typename T>
const Mat<T> Mat<T>::operator/(const Mat<T> &M) const{
    if(this->rows_!=M.rows_ && this->cols_!=M.cols_ ) throw std::invalid_argument("matrix dimensions do not match");
    Mat<T> res(this->rows_, this->rows_);
    for (int i = 0; i < this->rows_; ++i){
        *(res.array[i])=*(this->array[i]) / *(M.array[i]);
    }

    return res;
}

//multiplication by scalar (right side)
template <typename T>
const Mat<T> Mat<T>::operator*(const T &t) const{
    Mat<T> res(this->rows_, this->rows_);
    for (int i = 0; i < this->rows_; ++i){
        *(res.array[i])=*(this->array[i])* t;
    }

    return res;
}

//dot product
template <typename T>
const Mat<T> Mat<T>::dot(const Mat<T> &M) const{
    if(this->rows_!=M.cols_ || this->cols_!=M.rows_) throw std::invalid_argument("matrix sizes do not match");
    Mat<T> res(this->rows_, M.cols_);
    Vect<T> col;
    for(int j = 0; j < M.cols_; ++j){
        col=M.col(j);
        for(int i = 0; i < this->rows_; ++i){
            res[i][j] = col.dot(*(this->array[i]));
        }
    }

    return res;
}

//transpose
template <typename T>
const Mat<T>  Mat<T>::transp() const{
    Mat<T> res(this->cols_, this->rows_);
    for(int i = 0; i < this->cols_; ++i){
        res[i] = this->col(i);
    }
    return res;
}

//TODO determinant
template <typename T>
const T Mat<T>::det(void) const{
    if(this->rows_!=this->cols_) throw std::logic_error("not a square matrix");
    T det=0;

    return det;
}

//returns the number of rows
template <typename T>
const int Mat<T>::rows() const{
	return this->rows_;
}

//returns the number of columns
template <typename T>
const int Mat<T>::cols() const{
	return this->cols_;
}

//writes the elements to the stdout
template <typename T>
void Mat<T>::print() const{
    std::cout<<*this<<std::endl;
}

//writes the elements to a file
template <typename T>
void Mat<T>::fprint(char* fname) const{
    std::ofstream fout;
    fout.open(fname);
    if(fout.is_open()){
        fout<<*this<<std::endl;
        fout.close();
    }
    else std::cout<<"Writing to file failed."<<std::endl;
}

//fills the matrix with random values
template <typename T>
void Mat<T>::rand(double range){
    for (int i = 0; i < this->rows_; ++i){
      this->array[i]->rand(range);
    }
}

//multiplication by scalar (left side)
template <typename T>
Mat<T> operator* (const T &t, const Mat<T> &M){
    Mat<T> res(M.rows_, M.rows_);
    for (int i = 0; i < M.rows_; ++i){
        *(res.array[i])=*(M.array[i])* t;
    }

    return res;
}

//out << Mat
template <typename T>
std::ostream & operator<< (std::ostream &out, const Mat<T> &M){
    out<<"[";
    if(M.rows_>0){
        out<<*(M.array[0]);
        for (int i = 1; i < M.rows_; ++i){
            out<<", "<<*(M.array[i]);
        }
    }
    else out<<"null";
    out<<"]";
    return out;
}

//Explicitly stating possible template substitutions (if not, implementation must be in the header)
template class Mat<int>;
template  Mat<int> operator* <int>(const int &, const Mat<int> &);
template std::ostream & operator<< <int>(std::ostream &, const Mat<int> &);

template class Mat<float>;
template  Mat<float> operator* <float>(const float &, const Mat<float> &);
template std::ostream & operator<< <float>(std::ostream &, const Mat<float> &);

template class Mat<double>;
template  Mat<double> operator* <double>(const double &, const Mat<double> &);
template std::ostream & operator<< <double>(std::ostream &, const Mat<double> &);

 
