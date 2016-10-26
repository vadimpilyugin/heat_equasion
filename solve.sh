#! /bin/bash

set -o errexit # остановка после первой ошибки

# Директории
DATA="data"
RESULT="data/result"
SRC="src"
INCLUDE="include"
BIN_DIR="build/bin"

# Параметры программы
source ./config.cfg

# Программируем программу выдачи граничных значений и параметров
cat <<Input >${INCLUDE}/params.h
extern const int border_type;
extern const float D;
extern const int method;
extern const float time_bottom;
extern const float time_top;
extern const int time_steps;
extern const float x_left;
extern const float x_right;
extern const int x_steps;
float left_border(float t);
float right_border(float t);
float start_conditions(float x);
float source_func(float x, float t);
Input
cat <<Input >${SRC}/params.cpp
#include <cmath>
#include "params.h"
const int border_type = $border_type;
const float D = $D;
const int method = $method;
const float time_bottom = $time_bottom;
const float time_top = $time_top;
const int time_steps = $time_steps;
const float x_left = $x_left;
const float x_right = $x_right;
const int x_steps = $x_steps;
float left_border(float t)
{
	return $left_border;
}
float right_border(float t)
{
	return $right_border;
}
float start_conditions(float x)
{
	return $start_conditions;
}
float source_func(float x, float t)
{
	return $source_func;
}
Input

# Компиляция и запуск программы
make all
${BIN_DIR}/solve $output_file

# Построение графика решения
./plot.py $output_file
