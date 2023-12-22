#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Bad number of arguments!" << std::endl;
		return (1);
	}
	try
	{
		std::map<int, double> dataFile = parseDataFile("data.csv");
		ParseInput(dataFile, argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
