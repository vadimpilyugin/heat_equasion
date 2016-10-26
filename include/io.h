#pragma once

#include <string>
#include <vector>
#include <fstream>

vector<float> load_data(std::string path);
void put_line(vector<float> res, std::ofstream &out);
