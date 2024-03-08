#include "BitcoinExchange.hpp"

int	strToInt(std::string str)
{
	const char	*c_str;
	int			num;

	c_str = str.c_str();
	num = atoi(c_str);
	return (num);
}

double	strToDouble(std::string str)
{
	const char	*c_str;
	double		num;

	c_str = str.c_str();
	num = atof(c_str);
	return (num);
}

static bool checkKeyFormat(std::string const &key)
{
	if (key.empty())
		return (0);
	int	len = key.length();
	if (key[0] == '-' || key[len - 1] == '-')
		return (0);
	if (std::count(key.begin(), key.end(), '-') >= 3)
		return (0);
	std::vector<int> 	dates;
	std::stringstream 	str(key);
	std::string			data;
	int					i = 0;
	char del[] = {'-', '-', ' '};
	while (getline(str, data, del[i]))
	{
		if (i > 0 && data.size() != 2)
			return (0);
		dates.push_back(strToInt(data));
		i++;
	}
	if (dates.size() != 3)
		return (0);
	if (dates[0] < 2009)
		return (0);
	for (int i = 1; i < 3; i++)
	{
		if (dates[i] <= 0 || dates[i] > 31)
			return (0);
	}
	if (dates[1] == 2 && dates[2] > 29)
		return (0);
	return (true);
}

int	matchStr(std::string const &str, std::string const &match)
{
	int	find = 0;

	for (int i = 0; i < match.size(); i++)
	{
		for (int j = 0; j < str.size(); j++)
			if (match[i] == str[j])
				find++;
	}
	if (find == 0)
		return (0);
	return (1);
}

static int	checkValueFormat(std::string const &value)
{
	if (value.empty())
		return (0);	
	if (count(value.begin(), value.end(), '.') > 1)
		return (0);
	if (value[0] == '.')
		return (0);
	if (!matchStr(value, "0123456789."))
		return (0);
	return (1);
}

int	setKey(std::string token)
{
	if (!checkKeyFormat(token))
		throw keyException();
	eraseElem(token, '-');
	return (strToInt(token));
}

double	setValue(std::string token)
{
	if (!checkValueFormat(token))
		throw valueFormatException();
	return (strToDouble(token));
}

std::pair<int, double>setKeyValue(std::stringstream &str, char del)
{
	std::string	tokenKey;
	std::string	tokenValue;
	
	getline(str, tokenKey, del);
	int	key = setKey(tokenKey);
	getline(str, tokenValue, '\0');
	double	value = setValue(tokenValue);
	return (std::pair<int, double>(key, value));
}

std::map<int, double> parseDataFile(std::string file)
{
	std::ifstream data(file, std::ios::in);
	if (!data.is_open())
		throw FileError();
	
	std::string	line;
	std::map<int, double> mapData;
	while (!data.eof())
	{
		getline(data, line, '\n');
		if (!line.empty())
		{
			std::stringstream str(line);
			std::pair<int, double> keyValue = setKeyValue(str, ',');
			mapData.insert(keyValue);
		}
	}
	return (mapData);
}

int	calculateBitcoinValue(std::map<int, double> &mapData, int key, double value)
{
	it	db = mapData.begin();
	it	de = mapData.end();

	if (db->first < key)
	{
		while (db != de && db->first < key)
			db++;
		if (db->first > key)
			db--;
	}
	std::cout << "Date: " << db->first << " => " << value << " = "
		<< value * db->second << std::endl;
	return (value * db->second);
}

void	ParseInput(std::map<int, double> &mapData, std::string file)
{
	std::ifstream data(file, std::ios::in);
	if (!data.is_open())
		throw FileError();
	std::string line;
	while (!data.eof())
	{		
		try
		{
			getline(data, line, '\n');
			if (!line.empty())
			{
				std::stringstream	str(line);
				std::pair<int, double> keyValue = setKeyValue(str, '|');
				if (keyValue.second < 0 || keyValue.second > 1000)
					throw valueRangeException();
				calculateBitcoinValue(mapData, keyValue.first, keyValue.second);
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}