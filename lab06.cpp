#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

void simplex(double** s_matrix, int flag, unsigned int matrix_length, unsigned int matrix_width, char variable)
{
	unsigned int basis_size = matrix_width - 1;
	double** ad_matrix = new double* [matrix_length];
	for (int i = 0; i < matrix_length; ++i)
		ad_matrix[i] = new double[matrix_width];
	int* basis = new int[basis_size];
	for (int i = 0; i < basis_size; ++i)
		basis[i] = i + 1;
	int* free = new int[matrix_length - 1];
	for (int i = 0; i < matrix_length - 1; ++i)
		free[i] = i + 1 + basis_size;
	double min = -1;
	std::cout << std::fixed;
	std::cout << " s0 ";
	for (int i = 0; i < basis_size; i++)
	{
		std::cout << variable << basis[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < matrix_length; ++i)
	{
		if (i < matrix_length - 1) std::cout << variable << free[i] << " ";
		else std::cout << "F ";
		for (int j = 0; j < matrix_width; ++j)
		{
			std::cout << std::setw(8) << std::setprecision(3) <<
				s_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	bool f = true;
	int perm_col, perm_str;
	bool exist = true;
	while (f && exist)
	{
		perm_str = -1;
		perm_col = -1;
		for (int i = 0; i < matrix_length - 1; ++i)
		{
			if (s_matrix[i][0] < 0)
			{
				perm_str = i;
				break;
			}
		}
		if (perm_str >= 0)
		{
			exist = false;
			for (int i = 1; i < matrix_width; ++i)
			{
				if (s_matrix[perm_str][i] < 0)
				{
					perm_col = i;
					exist = true;
					break;
				}
			}
			if (exist)
			{
				for (int i = 0; i < matrix_length - 1; ++i)
				{
					if (((s_matrix[i][0] / s_matrix[i][perm_col]) >= 0) &&
						((min < 0) || (s_matrix[i][0] / s_matrix[i][perm_col] < min)))
					{
						min = s_matrix[i][0] / s_matrix[i][perm_col];
						perm_str = i;
					}
				}
				for (int i = 0; i < matrix_length; i++)
				{
					for (int j = 0; j < matrix_width; j++)
					{
						if (i != perm_str && j != perm_col)
							ad_matrix[i][j] = s_matrix[i][j] -
							s_matrix[i][perm_col] * s_matrix[perm_str][j] /
							s_matrix[perm_str][perm_col];
						else if (i != perm_str)
							ad_matrix[i][j] = -1 * s_matrix[i][j] /
							s_matrix[perm_str][perm_col];
						else if (j != perm_col)
							ad_matrix[i][j] = s_matrix[i][j] /
							s_matrix[perm_str][perm_col];
						else
							ad_matrix[i][j] = 1 / s_matrix[i][j];
						if (abs(ad_matrix[i][j]) <= pow(10, -12))
							ad_matrix[i][j] = abs(ad_matrix[i][j]);
					}
				}
				for (int i = 0; i < matrix_length; ++i)
					for (int j = 0; j < matrix_width; ++j)
						s_matrix[i][j] = ad_matrix[i][j];
				std::swap(basis[perm_col - 1], free[perm_str]);
				std::cout << " s0 ";
				for (int i = 0; i < basis_size; i++)
				{
					std::cout << variable << basis[i] << " ";
				}
				std::cout << "\n";
				for (int i = 0; i < matrix_length; ++i)
				{
					if (i < matrix_length - 1) std::cout << variable <<
						free[i] << " ";
					else std::cout << "F ";
					for (int j = 0; j < matrix_width; ++j)
					{
						std::cout << std::setw(8) << std::setprecision(3)
							<< s_matrix[i][j] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else f = false;
	}
	if (exist) f = true;
	else std::cout << "There is no solution\n";
	bool unlim = false;
	while (f && !unlim)
	{
		perm_col = -1;
		min = -1;
		for (int i = 1; i < matrix_width; ++i)
		{
			if (s_matrix[matrix_length - 1][i] > 0)
			{
				perm_col = i;
				break;
			}
		}
		if (perm_col > 0)
		{
			unlim = true;
			for (int i = 0; i < matrix_length - 1; ++i)
				if (s_matrix[i][perm_col] > 0)
				{
					unlim = false;
					break;
				}
			if (!unlim)
			{
				for (int i = 0; i < matrix_length - 1; ++i)
				{
					if (((s_matrix[i][0] / s_matrix[i][perm_col]) >= 0) &&
						((min < 0) || (s_matrix[i][0] / s_matrix[i][perm_col] < min)))
					{
						min = s_matrix[i][0] / s_matrix[i][perm_col];
						perm_str = i;
					}
				}
				for (int i = 0; i < matrix_length; i++)
				{
					for (int j = 0; j < matrix_width; j++)
					{
						if (i != perm_str && j != perm_col)
							ad_matrix[i][j] = s_matrix[i][j] -
							s_matrix[i][perm_col] * s_matrix[perm_str][j] /
							s_matrix[perm_str][perm_col];
						else if (i != perm_str)
							ad_matrix[i][j] = -1 * s_matrix[i][j] /
							s_matrix[perm_str][perm_col];
						else if (j != perm_col)
							ad_matrix[i][j] = s_matrix[i][j] /
							s_matrix[perm_str][perm_col];
						else
							ad_matrix[i][j] = 1 / s_matrix[i][j];
						if (abs(ad_matrix[i][j]) <= pow(10, -12))
							ad_matrix[i][j] = abs(ad_matrix[i][j]);
					}
				}
				for (int i = 0; i < matrix_length; ++i)
					for (int j = 0; j < matrix_width; ++j)
						s_matrix[i][j] = ad_matrix[i][j];
				std::swap(basis[perm_col - 1], free[perm_str]);
				std::cout << " s0 ";
				for (int i = 0; i < basis_size; i++)
				{
					std::cout << variable << basis[i] << " ";
				}
				std::cout << "\n";
				for (int i = 0; i < matrix_length; ++i)
				{
					if (i < matrix_length - 1) std::cout << variable <<
						free[i] << " ";
					else std::cout << "F ";
					for (int j = 0; j < matrix_width; ++j)
					{
						std::cout << std::setw(8) << std::setprecision(3)
							<< s_matrix[i][j] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
		}
		else f = false;
	}
	std::cout << std::endl;
	if (unlim)
	{
		std::cout << "Function is unlimitted\n";
	}
	else
	{
		std::cout << "\nSolution:\n";
		std::cout << "F = " << s_matrix[matrix_length - 1][0] * flag *
			1.0 << "\n";
		double g = 1.0 / (s_matrix[matrix_length - 1][0] * flag * 1.0);
		std::cout << "g = " << g << "\n";
		std::vector<double> strategy;
		strategy.resize(basis_size);
		for (int i = 0; i < basis_size; ++i)
		{
			if (basis[i] <= basis_size)
			{
				std::cout << variable << basis[i] << " = 0\n";
				strategy[i] = 0;
			}
		}
		for (int i = 0; i < matrix_length - 1; ++i)
		{
			if (free[i] <= basis_size)
			{
				std::cout << variable << free[i] << " = " <<
					s_matrix[i][0] << "\n";
				strategy[free[i] - 1] = s_matrix[i][0] * g;
			}
		}
		std::cout << char(variable + 3 - 32) << ":\n(";
		for (auto i : strategy)
		{
			std::cout << i << ",";
		}
		std::cout << ")\n";
		for (int i = 0; i < matrix_length; ++i)
			delete[] ad_matrix[i];
		delete[] ad_matrix;
		delete[] basis;
		delete[] free;
	}
}
void GT_method()
{

	unsigned short int matrix_length = 5;
	unsigned short int matrix_width = 6;
	double** s_matrix = new double* [matrix_length];
	for (int i = 0; i < matrix_length; ++i)
		s_matrix[i] = new double[matrix_width];
	std::ifstream in("D:\\GitHub\\MO\\lab06\\lptask6.txt");
	for (int i = 0; i < matrix_length - 1; ++i)
		for (int j = 1; j < matrix_width; ++j)
			in >> s_matrix[i][j];
	for (int i = 0; i < matrix_length - 1; ++i) s_matrix[i][0] = 1;
	for (int i = 1; i < matrix_width; ++i) s_matrix[matrix_length - 1][i]
		= 1;
	s_matrix[matrix_length - 1][0] = 0;
	std::cout << s_matrix[0][1];
	in.close();
	std::swap(matrix_length, matrix_width);
	double** d_matrix = new double* [matrix_length];
	for (int i = 0; i < matrix_length; ++i)
		d_matrix[i] = new double[matrix_width];

	for (int i = 0; i < matrix_length - 1; ++i)
		for (int j = 1; j < matrix_width; ++j)
			d_matrix[i][j] = -1.0 * s_matrix[j - 1][i + 1];


	for (int i = 0; i < matrix_length - 1; ++i) d_matrix[i][0] = -1.0;
	for (int i = 1; i < matrix_width; ++i) d_matrix[matrix_length - 1][i]
		= -1.0;
	d_matrix[matrix_length - 1][0] = 0;
	std::cout << std::endl;
	std::cout << "--------------------Player-A------------------\n\n";
	simplex(d_matrix, 1, matrix_length, matrix_width, 'u');
	std::cout << "--------------------Player-B------------------\n\n";
	simplex(s_matrix, -1, matrix_width, matrix_length, 'v');
	std::cout << "-----------------------End--------------------\n\n";
	for (int i = 0; i < matrix_width; ++i)
		delete[] s_matrix[i];
	delete[] s_matrix;
	for (int i = 0; i < matrix_length; ++i)
		delete[] d_matrix[i];
	delete[] d_matrix;
}
int main()
{
	GT_method();
	return 0;
}