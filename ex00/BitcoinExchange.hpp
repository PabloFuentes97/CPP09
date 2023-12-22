#pragma once
#define BITCOINEXCHANGE_HPP
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>

//EXCEPTION CLASSES
class	valueRangeException : public std::exception
{
	public:
		virtual const char* what() const throw () {
			return ("Error: Value out of range!"); }
};

class	FileError : public std::exception
{
	public:
		virtual const char* what() const throw () {
			return ("Error: Couldn't open file to read"); }
};

class	keyException : public std::exception
{
	public:
		virtual const char* what() const throw () {
			return ("Error: Bad key format!"); }
};

class	valueFormatException : public std::exception
{
	public:
		virtual const char* what() const throw () {
			return ("Error: Bad value format!"); }
};

//TEMPLATES
template<typename T, typename e>
void	eraseElem(T &data, e elem)
{
	typename T::iterator	end = data.end();
	
	for (typename T::iterator	begin = data.begin(); begin != end; begin++)
	{
		if (*begin == elem)
			data.erase(begin);
	}
}

//UTILS
int		strToInt(std::string str);
double	strToDouble(std::string str);

//BITCOIN EXCHANGE
typedef std::map<int, double>::iterator it;
int						matchStr(std::string const &str, std::string const &match);
int						setKey(std::string token);
double					setValue(std::string token);
std::pair<int, double>	setKeyValue(std::stringstream &str, char del);
std::map<int, double>	parseDataFile(std::string file);
int						calculateBitcoinValue(std::map<int, double> &mapData, int key, double value);
void					ParseInput(std::map<int, double> &mapData, std::string file);
