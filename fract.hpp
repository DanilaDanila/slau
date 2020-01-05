#ifndef FRACT_HPP
#define FRACT_HPP

#include <cmath>
#include <iostream>


class Fract
{
private:
	
// greatest common divisor
// P.S. сами пишите своего евклида
// P.P.S. "х&@$ х&@$ и в продакшн!"
template<class T>
const T gcd(const T &t0, const T &t1)
{
    for(T i=t0; i>T(0); --i)
        if ((t0 % i == T(0)) && (t1 % i == T(0)))
            return i;
    return T(1);
}

// least common multiple
template<class T>
const T lcm(const T &t0, const T &t1)
{
    return (t0 * t1) / gcd(t0, t1);
}

    long   p;  
    size_t q;
public:
    Fract() { p=0; q=1; }

    Fract(long p, size_t q): p(p), q(q) {}

    Fract(const long &l) { p=l; q=1; }

    Fract(const Fract &) = default;

    void reduce()
    {   
        if(p == 0)
        {
            q = 1;
            return;
        }
        size_t t = gcd((size_t)std::abs(p), q); 

        short sign = (p>=0)?1:-1;
        p = sign*(std::abs(p)/t);
        q /= t;
    }   

    ~Fract() {}

    const Fract &operator+=(Fract f)
    {   
        p *= f.q;
        f.p *= q;
        q *= f.q;

        p += f.p;

        reduce();

        return *this;
    }
	
	const Fract &operator-=(Fract f)
    {   
        p *= f.q;
        f.p *= q;
        q *= f.q;

        p -= f.p;

        reduce();

        return *this;
    }

    const Fract &operator*=(const Fract &f)
    {
        p *= f.p;
        q *= f.q;

        reduce();

        return *this;
    }

    const Fract &operator/=(const Fract f)
    {
        Fract new_f(q, std::abs(f.p));
        new_f.p *= (f.p>0)?1:-1;

        *this *= new_f;

        reduce();

        return *this;
    }

    friend std::ostream &operator<<(std::ostream&, const Fract&);
    friend const Fract operator+(const Fract&, const Fract&);
    friend const Fract operator-(const Fract&, const Fract&);
    friend const Fract operator*(const Fract&, const Fract&);
    friend const Fract operator/(const Fract&, const Fract&);
};

std::ostream &operator<<(std::ostream &out, const Fract &f)
{
    if(f.q == 1)
        out<<f.p;
    else
        out<<f.p<<"/"<<f.q;

    return out;
}

const Fract operator+(const Fract &f0, const Fract &f1)
{
    Fract result = f0;
    result += f1;
    return result;
}

const Fract operator-(const Fract &f0, const Fract &f1)
{
    Fract result = f0;
    result -= f1;
    return result;
}

const Fract operator*(const Fract &f0, const Fract &f1)
{
    Fract result = f0;
    result *= f1;
    return result;
}

const Fract operator/(const Fract &f0, const Fract &f1)
{
    Fract result = f0;
    result /= f1;
    return result;
}
#endif
