#include <sstream>
#include "PmergeMe.hpp"

itl	prevItList(itl it, int n)
{
	std::advance(it, n * -1);
	return (it);
}

itl	nextItList(itl it, int n)
{
	std::advance(it, n);
	return (it);
}

void	parseNumberslist(std::list<int> &numList, char **args)
{
	std::string	token;
	int			i = 0;

	while (args[i])
	{
		std::stringstream	arg(args[i]);
		while (getline(arg, token, ' '))
		{
			if (!token.empty())
			{
				if (!charcmpDict(token[0], "0123456789+")
					|| !strcmpDict(&token[1], "0123456789"))
					throw invalidArg();
				numList.push_back(strToInt(token));	
			}
		}
		i++;
	}
}

void	printList(itl start, itl end)
{
	while (start != end)
	{
		std::cout << *start << " ";
		start++;
	} 
	std::cout << std::endl;
}

void	cpyList(itl	srcStart, itl srcEnd, itl destStart, itl destEnd)
{
	while (srcStart != srcEnd && destStart != destEnd)
	{
		*destStart = *srcStart;
		srcStart++;
		destStart++;
	}
}

void	insertSortList(itl startitl, itl enditl)
{
	for (itl auxitl = nextItList(startitl, 1); auxitl != enditl; auxitl++)
	{
		int	key = *auxitl;
		itl	moveitl = prevItList(auxitl, 1);
		while (moveitl != prevItList(startitl, 1) && *moveitl > key)
		{
			*(nextItList(moveitl, 1)) = *moveitl;
			moveitl--;
		}
		*(nextItList(moveitl, 1)) = key;
	}
}

static void	merge(itl startitl, itl miditl, itl enditl)
{
	std::list<int> left;
	std::list<int> right;

	for (itl leftitl = startitl; leftitl != miditl; leftitl++)
		left.push_back(*leftitl);
	for (itl rightitl = miditl; rightitl != enditl; rightitl++)
		right.push_back(*rightitl);

	itl	moveitl = startitl;
	itl	leftitl = left.begin();
	itl	leftEnditl = left.end();
	itl	rightitl = right.begin();
	itl	rightEnditl = right.end();
	while (leftitl != leftEnditl && rightitl != rightEnditl)
	{
		if (*leftitl <= *rightitl)
		{
			*moveitl = *leftitl;
			leftitl++;
		}
		else
		{
			*moveitl = *rightitl;
			rightitl++;
		}
		moveitl++;
	}
	cpyList(leftitl, leftEnditl, moveitl, enditl);
	cpyList(rightitl, rightEnditl, moveitl, enditl);
}

void	mergeSortList(itl startitl, itl enditl)
{
	size_t	size = std::distance(startitl, enditl);

	if (size <= 5)
	{
		insertSortList(startitl, enditl);
		return ;
	}
	itl	miditl = nextItList(startitl, size / 2 - 1);
	mergeSortList(startitl, miditl);
	mergeSortList(miditl, enditl);
	merge(startitl, miditl, enditl);
}

void	sortNumbersList(char **args)
{
	std::cout << "LIST IMPLEMENTATION " << std::endl;
	
	long long int	timeBef;
	long long int	timeAfter;
	double distTime;

	timeBef = getCurrTimeMicrosec();
	std::list<int> nums;
	parseNumberslist(nums, args);
	if (nums.empty())
		return ;
	timeAfter = getCurrTimeMicrosec();
	distTime = (double)(timeAfter - timeBef) / 1000;
	std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;
	std::cout << "Time to perform parsing: " << distTime << std::endl;

	std::cout << "Before: ";
	printList(nums.begin(), nums.end());
	std::cout << std::endl;
	timeBef = getCurrTimeMicrosec();
	mergeSortList(nums.begin(), nums.end());
	timeAfter = getCurrTimeMicrosec();
	distTime = (double)(timeAfter - timeBef) / 1000;
	std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;
	std::cout << "Time to perform sorting: " << distTime << std::endl;
	std::cout << "After: ";
	printList(nums.begin(), nums.end());
	std::cout << std::endl;
}
