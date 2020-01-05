#ifndef SLAU_HPP
#define SLAU_HPP

#include "vector.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

template<class T>
std::string as_slau(Vector<Vector<T>> v)
{
    std::ostringstream out;

    for(size_t i=0; i<v.size(); ++i)
    {
        out<<v[i][0]<<"*x1";
        for(size_t j=1; j<v[0].size()-1; ++j)
            out<<" + "<<v[i][j]<<"*x"<<j+1;
        out<<" = "<<v[i][v[i].size()-1]<<"\n";
    }

    return out.str();
}

template<class T>
std::string as_matrix(Vector<Vector<T>> v)
{
    std::ostringstream out;

    for(size_t i=0; i<v.size(); ++i)
    {
        if(i == 0)
            out << "/";
        else if (i == v.size() - 1)
            out << "\\";
        else
            out << "|";

        for(size_t j=0; j<v[0].size(); ++j)
            out<<std::setw(3)<<v[i][j];

        if(i == 0)
            out << "  \\";
        else if (i == v.size() - 1)
            out << "  /";
        else
            out << "  |";

        out<<"\n";
    }

    return out.str();
}

template<class T>
std::string as_extended_matrix(Vector<Vector<T>> v)
{
    std::ostringstream out;

    for(size_t i=0; i<v.size(); ++i)
    {
        if(i == 0)
            out << "/";
        else if (i == v.size() - 1)
            out << "\\";
        else
            out << "|";

        for(size_t j=0; j<v[0].size()-1; ++j)
            out<<std::setw(3)<<v[i][j];
        out<<" |"<<std::setw(3)<<v[i][v[0].size()-1];

        if(i == 0)
            out << "  \\";
        else if (i == v.size() - 1)
            out << "  /";
        else
            out << "  |";

        out<<"\n";
    }

    return out.str();
}

template<class T>
void slau_next_step(Vector<Vector<T>> &v, const size_t &step)
{
    std::sort(v.begin()+step, v.end(), [=](auto x, auto y){return std::abs(x[step]) > std::abs(y[step]);});

    std::cout<<"After sort:\n";
    std::cout<<as_extended_matrix(v)<<"\n";

    size_t row = step+1;
    for(; row < v.size(); ++row)
        if(v[row][step] != 0)
        {
            std::cout<<"PROCESS:\n";
            std::cout<<as_extended_matrix(v)<<"\n";

            if(v[step][step] < 0)
            {
                v[step] *= -1;
                std::cout<<as_extended_matrix(v)<<"\n";
            }

            T least_of = lcm(v[step][step], std::abs(v[row][step]));
            T zero_mul = least_of / v[step][step];
            T row_mul = least_of / v[row][step];

            std::cout<<step<<" must be mul by "<<zero_mul<<"\n";
            std::cout<<row<<" must be mul by "<<row_mul<<"\n\n";

            v[step] *= zero_mul;
            v[row] *= row_mul;
            std::cout<<as_extended_matrix(v)<<"\n";
            v[row] -= v[step];
            std::cout<<as_extended_matrix(v)<<"\n";
            v[step] /= zero_mul;
            std::cout<<as_extended_matrix(v)<<"\n";

            T div = T(1);
            for(size_t i=1; i<v[row].size(); ++i)
                if(v[row][i] != 0)
                {
                    div = std::abs(v[row][i]);
                    break;
                }
			
			for(size_t i=2; i<v[row].size(); ++i)
                if(v[row][i] != 0)
                    div = gcd(div, std::abs(v[row][i]));

            std::cout<<row<<" can be divided by "<<div<<"\n\n";
            v[row] /= div;
            std::cout<<as_extended_matrix(v);
            std::cout<<"DONE!\n";
        }
    std::cout<<"RETURN----------------------------\n";
}

template<class T>
size_t triangle_matrix_rank(const Vector<Vector<T>> &v)
{
    size_t result = 0;

    for(size_t i=0; i<v.size(); ++i)
    {
        T abs(0);
        for(size_t j=0; j<v[i].size(); ++j)
            abs += std::abs(v[i][j]);

        if(abs != T(0))
            ++result;
    }

    return result;
}

template<class T>
const Vector<Vector<T>> transform(const Vector<Vector<T>> &v)
{
    Vector<Vector<T>> result;

    for(size_t i=0; i<v[0].size(); ++i)
    {
        Vector<T> row;
        for(size_t j=0; j<v.size(); ++j)
            row.append(v[j][i]);
        result.append(row);
    }

    return result;
}

#endif
