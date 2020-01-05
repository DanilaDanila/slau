#include "fract.hpp"
#include "tools.hpp"
#include "vector.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

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

int main()
{
	/*
	 * y + 3z = -1
	 * 2x + 3y + 5z = 3
	 * 3x + 5y + 7z = 6
	 * (1, 2, -1)
	 *
	 * 2x + 3y + 4z + 5t = 30
	 * 3x + 3y + 4z + 5t = 34
	 * 4x + 4y + 4z + 5t = 41
	 * x + y + z + t = 10
	 * (4, 3, 2, 1)
	 *
	 * ----------------------
	 *
	 * 2x + y + z = 4
	 * 3x + z = 4
	 *
	 * 3x1 + x2 + x3 + 2x4 = -2
	 * 5x1 + 2x3 + 5x4 = -2
	 * 6x1 + x2 + 5x3 + 7x4 = -4
	 * 2x1 + x2 + 2x3 + 2x4 = -2
	 */
	
	
	Vector<Vector<int>> slau0={{0, 1, 3, -1},
						  	   {2, 3, 5, 3},
						  	   {3, 5, 7, 6}};

	Vector<Vector<int>> slau1={{2, 3, 4, 5, 30},
							   {3, 3, 4, 5, 34},
							   {4, 4, 4, 5, 41},
							   {1, 1, 1, 1, 10}};

	Vector<Vector<int>> slau2={{2, 1, 1, 4},
							   {3, 0, 1, 4}};

	Vector<Vector<int>> slau3={{3, 1, 1, 2, -2},
						   	   {5, 0, 2, 5, -2},
						   	   {6, 1, 5, 7, -4},
						   	   {2, 1, 2, 2, -2}};

	Vector<Vector<int>>	v=slau3;
	Vector<Vector<int>> v_cpy=v;
	
	std::cout<<"\n"<<as_slau(v);
	for(size_t i=0; i<v.size()-1; ++i)
		slau_next_step(v, i);

	size_t rank = triangle_matrix_rank(v);
	std::cout<<"Rank: "<<rank<<"\n";

	size_t vars_count = v[0].size()-1;
	size_t fixed_vars_count = vars_count - rank;
	size_t vec_dim = fixed_vars_count + 1;
	Vector<Vector<Fract>> vars(vars_count);
  	
	for(size_t i=0; i<vars_count; ++i)
		for(size_t j=0; j<fixed_vars_count+1; ++j)
			vars[i].append(0);

	for(size_t i=0; i<fixed_vars_count; ++i)
		vars[vars_count-1-i][fixed_vars_count-i] = 1;

	std::cout<<as_matrix(vars)<<"\n";

	Vector<Fract> e;
	e.append(1);
	for(size_t i=1; i<vec_dim; ++i)
		e.append(0);

	for(long row = vars_count-1-fixed_vars_count; row>=0; --row)
	{
		Vector<Fract> sum;
		for(size_t i=0; i<vec_dim; ++i)
			sum.append(0);

		for(size_t var_n = row+1; var_n<vars_count; ++var_n)
			sum += v[row][var_n] * vars[var_n];

		std::cout<<row<<"\n";
		std::cout<<e*v[row][vars_count]<<" - "<<sum<<"\n";
		std::cout<<(e*v[row][vars_count] - sum)<<" / "<<v[row][row]<<"\n";
		vars[row] = (e*v[row][vars_count] - sum) / Fract(v[row][row]);
		std::cout<<as_matrix(vars)<<"\n";
	}

	std::cout<<"Triangular matrix:\n";
	std::cout<<as_extended_matrix(v)<<"\n";

	std::cout<<"SLAU:\n";
	std::cout<<as_slau(v_cpy)<<"\n";

	std::cout<<"Triangular SLAU:\n";
	std::cout<<as_slau(v)<<"\n";

	std::cout<<"RESULT:\n";
	std::cout<<as_matrix(vars);


	return 0;
}
