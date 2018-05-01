#include <iostream>
#include "vect.h"
#include "mat.h"

int main(){
    std::cout<<"vector test"<<std::endl;
    std::cout<<"ctor, size(), rand()"<<std::endl;
    Vect<double> v1, v2(3), v3(v2);
    std::cout<<v1<<std::endl<<v1.size()<<std::endl;
    std::cout<<v2<<std::endl<<v2.size()<<std::endl;
    std::cout<<v3<<std::endl<<v3.size()<<std::endl;
    v1.rand(); v2.rand(); v3.rand();
    std::cout<<v1<<std::endl;;
    std::cout<<v2<<std::endl;;
    std::cout<<v3<<std::endl;;

    std::cout<<"element operations"<<std::endl;
    std::cout<<v2[1]<<std::endl;
    v2[1]=1.5;
    v3[2]=v2[1];
    std::cout<<v2<<std::endl;
    std::cout<<v3<<std::endl;
    double a=v3[2]+v2[1];
    std::cout<<a<<std::endl;


    std::cout<<"vector operations"<<std::endl;
    v1=v2+v3;
    v1.print();

    v2=2.0*v1;
    v2.print();
    v2.fprint("test_out.txt");

    v3=v1*2;
    v3.print();

    a=v1.dot(v1);
    std::cout<<a<<std::endl;

    std::cout<<"matrix test"<<std::endl;
    Mat<double> M1, M2(2,3);
    M1.rand(); M2.rand();
    std::cout<<M1<<std::endl;
    std::cout<<M2<<std::endl;
    M2.print();
    M2.fprint("test_out.txt");
    Mat<double> M3(M2);
    std::cout<<M3<<std::endl;
    M3.rand();
    std::cout<<M3<<std::endl;
    std::cout<<M3[0]<<std::endl<<M3[0][0]<<std::endl;
    M3[0]=M3[1];
    M3[0][0]=1.5;
    std::cout<<M3<<std::endl;
    std::cout<<M3+M3<<std::endl;
    std::cout<<M3*2<<std::endl;
    std::cout<<2.0*M3<<std::endl;
    std::cout<<M3.col(2)<<std::endl;

    std::cout<<"matrix product"<<std::endl;
    Mat<double> Ma(3,2), Mb(2,3);
    Ma[0][0]=1;Ma[0][1]=2;Ma[1][0]=3;Ma[1][1]=4;Ma[2][0]=5;Ma[2][1]=6;
    Mb[0][0]=1;Mb[0][1]=2;Mb[0][2]=3;Mb[1][0]=4;Mb[1][1]=5;Mb[1][2]=6;
    std::cout<<Ma<<std::endl;
    std::cout<<Mb<<std::endl;
    std::cout<<"matrix product perf"<<std::endl;
    std::cout<<Ma.dot(Mb)<<std::endl;
    Mb=Ma.transp();
    std::cout<<Mb<<std::endl;
    Ma[0]=v2;
    std::cout<<Ma<<std::endl;

    return 0;
}
