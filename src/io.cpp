#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
using namespace std;

vector<float> load_data(string path)
{
	ifstream f(path);
	if(!f.is_open())
	{
		fprintf(stderr, "Could not open file: %s\n", path.c_str());
		throw -1;
	}
	int m = -1;
	f >> m;
	vector<float> res(m);
	for(int i = 0; i < m; i++)
		f >> res[i];
	return res;
}

void put_line(vector<float> res, ofstream &f)
{
	if(!f.is_open())
	{
		fprintf(stderr, "Could not open output file\n");
		throw -1;
	}
	int m = res.size();
	for(int i = 0; i < m; i++)
		f << res[i] << " ";
	f << "\n";
}
