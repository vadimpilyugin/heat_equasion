#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#include "matrix.h"
#include "io.h"

int stoi(const char *s)
{
	stringstream tmp(s);
	int a;
	tmp >> a;
	return a;
}

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		fprintf(stderr, "Wrong arguments! Usage:\n");
		fprintf(stderr, "\tbuild/bin/solve <input_file> <output_file> <[1-2]>\n");
		throw 1;
	}
	
	// Загрузка данных
	const int cond_type = stoi(argv[3]);
	Matrix<float> output;
	Matrix<float> input = load_matrix(argv[1]);
	
	
}
