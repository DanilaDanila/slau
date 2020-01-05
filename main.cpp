#include "fract.hpp"
#include "tools.hpp"
#include "vector.hpp"
#include "slau.hpp"

#include <iostream>
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

	Vector<Vector<int>>	v=slau1;
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
