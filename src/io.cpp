#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

#include "matrix.h"

Matrix<float> load_matrix(string path)
{
	ifstream f(path);
	if(!f.is_open())
	{
		fprintf(stderr, "Could not open file: %s\n", path.c_str());
		throw -1;
	}
	int m = 0, n = 0;
	f >> m >> n;
	Matrix<float> res(m,n);
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			f >> res(i,j);
	return res;
}

void write_matrix(Matrix<float> res, string path)
{
	ofstream f(path);
	if(!f.is_open())
	{
		fprintf(stderr, "Could not open file: %s\n", path.c_str());
		throw -1;
	}
	int m = res.n_rows, n = res.n_cols;
	f << m << " " << n << "\n";
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
			f << res(i,j) << " ";
		f << "\n";
	}	
}
