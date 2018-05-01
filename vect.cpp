#include <stdexcept>
#include <iostream>
#include <fstream>
#include "vect.h"
#include <random>

//creates vector with a given size (defaut 0)
template <typename T>
Vect<T>::Vect(int size) : size_(size){
    if(size<0) throw std::invalid_argument("array size must be greater than zero");
    this->array = new T[this->size_];
}

//copy constructor
template <typename T>
Vect<T>::Vect(const Vect<T> &v0) : size_(v0.size_){
    this->array = new T[this->size_];
    for (int i = 0; i < this->size_; ++i){
      this->array[i] = v0.array[i];  //copy each element
    }
}

//frees the array
template <typename T>
Vect<T>::~Vect(){
	delete[] this->array;
}

//returns an element by value
template <typename T>
T Vect<T>::operator[](int i) const{
    if(i>=size_ || i<0) throw std::out_of_range("array index is out of range");
    return this->array[i];
}

//returns an element by reference
template <typename T>
T & Vect<T>::operator[](int i){
    if(i>=size_ || i<0) throw std::out_of_range("array index is out of range");
    return this->array[i];
}

//assignment operator
template <typename T>
Vect<T> & Vect<T>::operator=(const Vect<T> &v){
    if(this==&v) return *this;

    //reallocate array
    delete[] this->array;
    this->size_=v.size_;
    this->array = new T[this->size_];

    for (int i = 0; i < size_; ++i){
      this->array[i] = v.array[i];  // copy each element
    }

    return *this;
}

//elementwise addition
template <typename T>
const Vect<T> Vect<T>::operator+(const Vect<T> &v) const{
    if(this->size_!=v.size_) throw std::invalid_argument("vector sizes do not match");
    Vect<T> res(this->size_);
    for (int i = 0; i < size_; ++i){
        res.array[i]=this->array[i]+v.array[i];
    }

    return res;
}

//elementwise substraction
template <typename T>
const Vect<T> Vect<T>::operator-(const Vect<T> &v) const{
    if(this->size_!=v.size_) throw std::invalid_argument("vector sizes do not match");
    Vect<T> res(this->size_);
    for (int i = 0; i < size_; ++i){
        res.array[i]=this->array[i]-v.array[i];
    }

    return res;
}

//elementwise multiplication
template <typename T>
const Vect<T> Vect<T>::operator*(const Vect<T> &v) const{
    if(this->size_!=v.size_) throw std::invalid_argument("vector sizes do not match");
    Vect<T> res(this->size_);
    for (int i = 0; i < size_; ++i){
        res.array[i]=this->array[i]*v.array[i];
    }

    return res;
}

//elementwise division
template <typename T>
const Vect<T> Vect<T>::operator/(const Vect<T> &v) const{
    if(this->size_!=v.size_) throw std::invalid_argument("vector sizes do not match");
    Vect<T> res(this->size_);
    for (int i = 0; i < size_; ++i){
        if(v.array[i]==0) throw std::out_of_range("division by zero");
        res.array[i]=this->array[i]/v.array[i];
    }

    return res;
}

//multiplication by scalar (right side)
template <typename T>
const Vect<T> Vect<T>::operator*(const T &t) const{
    Vect<T> res(this->size_);
    for (int i = 0; i < this->size_; ++i){
        res.array[i]=this->array[i]*t;
    }

    return res;
}

//dot product
template <typename T>
const T Vect<T>::dot(const Vect<T> &v) const{
    if(this->size_!=v.size_) throw std::invalid_argument("vector sizes do not match");
    T res=0;
    for (int i = 0; i < size_; ++i){
        res+=this->array[i]*v.array[i];
    }

    return res;
}

//returns the number of elements
template <typename T>
const int Vect<T>::size() const{
	return this->size_;
}

//writes the elements to the stdout
template <typename T>
void Vect<T>::print() const{
    std::cout<<*this<<std::endl;
}

//writes the elements to a file
template <typename T>
void Vect<T>::fprint(char* fname) const{
    std::ofstream fout;
    fout.open(fname);
    if(fout.is_open()){
        fout<<*this<<std::endl;
        fout.close();
    }
    else std::cout<<"Writing to file failed."<<std::endl;
}

//fills the vector with random values
template <typename T>
void Vect<T>::rand(double range){
    std::uniform_real_distribution<double> unif(-range,range);
    std::random_device rand_dev;
    std::default_random_engine re(rand_dev());
    for (int i = 0; i < this->size_; ++i){
      this->array[i] = unif(re);
    }
}

//multiplication by scalar (left side)
template <typename T>
Vect<T> operator* (const T &t, const Vect<T> &v){
    Vect<T> res(v.size_);
    for (int i = 0; i < v.size_; ++i){
        res.array[i]=v.array[i]*t;
    }

    return res;
}

//out << Vect
template <typename T>
std::ostream & operator<< (std::ostream &out, const Vect<T> &v){
    out<<"[";
    if(v.size_>0){
        out<<v.array[0];
        for (int i = 1; i < v.size_; ++i){
          out<<", "<<v.array[i];
        }
    }
    else out<<"null";
    out<<"]";
    return out;
}

//explicitly stating possible template substitutions (if not, implementation must be in the header)
template class Vect<int>;
template  Vect<int> operator* <int>(const int &, const Vect<int> &);
template std::ostream & operator<< <int>(std::ostream &, const Vect<int> &);

template class Vect<float>;
template  Vect<float> operator* <float>(const float &, const Vect<float> &);
template std::ostream & operator<< <float>(std::ostream &, const Vect<float> &);

template class Vect<double>;
template  Vect<double> operator* <double>(const double &, const Vect<double> &);
template std::ostream & operator<< <double>(std::ostream &, const Vect<double> &);

