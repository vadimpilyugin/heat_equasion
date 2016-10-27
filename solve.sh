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
#pragma once
#include <cmath>
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
printf "Solve process started:\tpid=$pid1\n"
sleep 1

# Построение графика решения
./expplot.py $output_file & 2>/dev/null 1>/dev/null
pid2=$(echo $!)
printf "Plot process started:\tpid=$pid2\n"

# Завершение программы
read -n 1 -p "Press q to stop..." mainmenuinput
if [ "$mainmenuinput" = "q" ]; then
	kill -9 $pid1
	kill -9 $pid2
	echo
	printf "Process killed:\t$pid1\n"
	printf "Process killed:\t$pid2\n"
fi
