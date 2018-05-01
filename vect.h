#ifndef VECT_H
#define VECT_H

#include <iostream>

template <typename T> class Vect;

template <typename T> Vect<T> operator* (const T &, const Vect<T> &);
template <typename T> std::ostream & operator<< (std::ostream &, const Vect<T> &);
template <typename T> std::istream & operator>> (std::istream &, Vect<T> &);

//Vector class declaration
template <typename T>
class Vect{
    private:
        int size_;  //number of elements
        T *array;   //pointer to array of values        
    public:
        Vect(int = 0);  //creates vector with a given size (defaut 0)
        Vect(const Vect<T> &);  //copy constructor
        ~Vect();    //frees the array

        T operator[](int) const;  //returns an element by value
        T & operator[](int);  //returns an element by reference
        Vect<T> & operator=(const Vect<T> &);   //assignment

        const Vect<T> operator+(const Vect<T> &) const;  //elementwise addition
        const Vect<T> operator-(const Vect<T> &) const;  //elementwise substraction
        const Vect<T> operator*(const Vect<T> &) const;  //elementwise multiplication
        const Vect<T> operator/(const Vect<T> &) const;  //elementwise division

        const Vect<T> operator*(const T &) const;  //multiplication by scalar (right side)
        const T dot(const Vect<T> &) const; //dot product

        const int size(void) const; //returns the number of elements
        void print(void) const; //writes the elements to the stdout
        void fprint(char*) const; //writes the elements to a file
        void fread(char*); //reads the elements from a file TODO
        void rand(double = 10); //fills the vector with random values

        friend Vect<T> (::operator* <>)(const T &, const Vect<T> &);    //multiplication by scalar (left side)

        friend std::ostream & operator<< <>(std::ostream &, const Vect<T> &); //out << Vect
        friend std::istream & operator>> <>(std::istream &, Vect<T> &);    //in >> Vect TODO
};

#endif
