#pragma once

#include <string>
#include <vector>

std::vector<std::string> ReadFileLines(std::string &path);

std::vector<std::string> SplitString(std::string &line, std::string delimiter = ",");

void WriteFileLines(std::string &path, std::vector<std::string> &lines);