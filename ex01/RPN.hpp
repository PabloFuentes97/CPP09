#pragma once

#define RPN_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <stack>

int strcmpDict(std::string str, std::string dict);
int strToInt(std::string str);
int RPN(std::string args);