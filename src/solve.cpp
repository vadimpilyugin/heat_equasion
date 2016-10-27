#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;

#include "io.h"
#include "params.h"

int stoi(const char *s)
{
	stringstream tmp(s);
	int a;
	tmp >> a;
	return a;
}

void triag_matrix_alg(vector<float> last, vector<float> &next, float dt, float dx, int n, float C)
{
	int x_steps = last.size();
	float a = C/2, g = C/2;
	float b = 1+C;
	float d = 0;
	
	// Прямой ход
	vector<float> p(x_steps - 1), q(x_steps - 1); // прогоночные коэффициенты
	if(border_type == 1)
	{
		p[0]=0;
		q[0]=left_border(time_bottom + (n-1)*dt);
	}
	else if(border_type == 2)
	{
		p[0]=1;
		q[0]=-left_border(time_bottom + (n-1)*dt);
	}
	for(int i = 1; i < x_steps-1; i++)
	{
		d = -last[i] - dt*source_func(x_left + dx*i, time_bottom + (n-1)*dt);
		p[i] = g/(b-a*p[i-1]);
		q[i] = (a*q[i-1]-d)/(b-a*p[i-1]);
	}
	
	// Обратный ход
	if(border_type == 1)
	{
		next[x_steps-1] = right_border(time_bottom + (n-1)*dt);
	}
	else if(border_type == 2)
	{
		next[x_steps-1] = (q[x_steps-2] + right_border(time_bottom + (n-1)*dt)*dx)/(1-p[x_steps-2]);
	}
	for(int i = x_steps-2; i >= 0; i--)
		next[i] = p[i]*next[i+1] + q[i];
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Wrong arguments! Usage:\n");
		fprintf(stderr, "\tbuild/bin/solve <output_file>\n");
		throw 1;
	}
	
	// Загрузка данных
	ofstream output(argv[1], ios_base::trunc);
	vector<float> input(x_steps);
	float dx = (x_right - x_left)/(x_steps - 1);
	for(int i = 0; i < x_steps; i++)
		input[i] = start_conditions(x_left + (i-1)*dx);
	// Решение
	float C = 2*D*dt/(dx*dx);
	vector<float> last(x_steps), next(x_steps);
	last = input;
	if(method == 1)
	{
		if(C>1)
		{
			fprintf(stderr, "dt = %f, dx = %f, C = %f\n", dt, dx, C);
			fprintf(stderr, "Решение неустойчиво! Уменьшите шаг по времени или увеличьте по пространству!\n");
			//dt = (dx*dx)/(4*D);
			//C = 2*D*dt/(dx*dx);
			//fprintf(stderr, "Выставлено рекомендуемое значение dt = %f, C = %f\n", dt, C);
			//exit(1);
		}
		for(int n = 2; true; n++) // пока скрипт не пошлет SIGKILL
		{
			for(int i = 1; i < x_steps-1; i++)
				next[i] = C/2*(last[i-1]-2*last[i]+last[i+1]) + dt*source_func(x_left + (n-1)*dx, time_bottom + (n-1)*dt) + last[i];
			if(border_type == 1)
			{
				next[0] = left_border(time_bottom + (n-1)*dt);
				next[x_steps-1] = right_border(time_bottom + (n-1)*dt);
			}
			else if(border_type == 2)
			{
				next[0] = next[1]-dx*left_border(time_bottom + (n-1)*dt);
				next[x_steps-1] = next[x_steps-2]+dx*right_border(time_bottom + (n-1)*dt);
			}
			put_line(next, output);
			last=next;
			//printf("line = %d\n", n);
			unsigned int microseconds = 10000;
			usleep(microseconds);
		}
	}
	else if(method == 2)
	{
		for(int n = 2; true; n++)
		{
			triag_matrix_alg(last, next, dt, dx, n, C);
			put_line(next, output);
			last=next;
			unsigned int microseconds = 10000;
			usleep(microseconds);
		}
	}
}
