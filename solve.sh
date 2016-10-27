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
extern const float dt;
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
const float dt = $dt;
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
make all 1>/dev/null
${BIN_DIR}/solve $output_file & 1>/dev/null
pid1=$(echo $!)
echo "Solve process started: pid=$pid1"
sleep 1

# Построение графика решения
./plot.py $output_file & 2>/dev/null 1>/dev/null
pid2=$(echo $!)
echo "Plot process started: pid=$pid2"

# Завершение программы
read -n 1 -p "Press q to stop..." mainmenuinput
if [ "$mainmenuinput" = "q" ]; then
	kill -9 $pid1
	kill -9 $pid2
	echo
fi
