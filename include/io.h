#pragma once

#include <string>

#include "matrix.h"

Matrix<float> load_matrix(std::string path);
void write_matrix(Matrix<float> res, std::string path);
