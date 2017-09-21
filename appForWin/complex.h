#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <iostream>

class Complex
{

private:

    // 实部和虚部
    double RealPart;
    double ImaginaryPart;

public:

    // 默认构造函数
    Complex()
    {
        this->RealPart = 0.0;
        this->ImaginaryPart = 0.0;
    }

    // 构造函数
    Complex(double rep, double imp)
    {
        this->RealPart = rep;
        this->ImaginaryPart = imp;
    }

    // 直接置数
    void Update(double ReP, double ImP)
    {
        this->RealPart = ReP;
        this->ImaginaryPart = ImP;
    }

    // 取实部
    double Re(void)
    {
        return this->RealPart;
    }

    //取虚部
    double Im(void)
    {
        return this->ImaginaryPart;
    }

    //取模的平方
    double AbsSqr(void)
    {
        return (this->RealPart * this->RealPart + this->ImaginaryPart * this->ImaginaryPart);
    }

    //取模
    double Abs(void)
    {
        return sqrt(this->RealPart * this->RealPart + this->ImaginaryPart * this->ImaginaryPart);
    }

    // 复数加法
    Complex operator+( Complex c )
    {
        return Complex(this->RealPart + c.Re(), this->ImaginaryPart + c.Im() );
    }

    // 复数减法
    Complex operator-( Complex c )
    {
        return Complex(this->RealPart - c.Re(), this->ImaginaryPart - c.Im() );
    }

    // 复数乘法
    Complex operator*( Complex c )
    {
        double rep = this->RealPart * c.Re() - this->ImaginaryPart * c.Im();
        double imp = this->RealPart * c.Im() + c.Re() * this->ImaginaryPart;
        return Complex(rep, imp);
    }

    // 重载赋值运算符
    void operator=( Complex rv )
    {
        this->RealPart = rv.Re();
        this->ImaginaryPart = rv.Im();
    }

    // 重载输出运算符
    void operator<<( Complex rv )
    {
        std::cout<<rv.Re()<<"   "<<rv.Im()<<std::endl;
    }
};

#endif // COMPLEX_H
