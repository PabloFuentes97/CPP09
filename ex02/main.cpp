#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (0);
	try
	{
		sortNumbersDeque(&argv[1]);
		sortNumbersList(&argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}