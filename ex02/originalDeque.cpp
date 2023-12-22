#include <sstream>
#include "PmergeMe.hpp"

void	parseNumbersDeque(std::deque<int> &numDeque, char **args)
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
				numDeque.push_back(strToInt(token));	
			}
		}
		i++;
	}
}

void	printContainer(itq start, itq end)
{
	while (start != end)
	{
		std::cout << *start << std::endl;
		start++;
	}
}

void	cpyContainer(itq	srcStart, itq srcEnd, itq destStart, itq destEnd)
{
	while (srcStart != srcEnd && destStart != destEnd)
	{
		*destStart = *srcStart;
		srcStart++;
		destStart++;
	}
}

void	insertSortDeque(itq startitq, itq enditq)
{
	for (itq auxitq = startitq + 1; auxitq != enditq; auxitq++)
	{
		int	key = *auxitq;
		itq	moveitq = auxitq - 1;
		while (moveitq != (startitq - 1) && *moveitq > key)
		{
			*(moveitq + 1) = *moveitq;
			moveitq--;
		}
		*(moveitq + 1) = key;
	}
}

static void	merge(itq startitq, itq miditq, itq enditq)
{
	std::deque<int> left;
	std::deque<int> right;

	for (itq leftitq = startitq; leftitq != miditq; leftitq++)
		left.push_back(*leftitq);
	for (itq rightitq = miditq; rightitq != enditq; rightitq++)
		right.push_back(*rightitq);

	itq	moveitq = startitq;
	itq	leftitq = left.begin();
	itq	leftEnditq = left.end();
	itq	rightitq = right.begin();
	itq	rightEnditq = right.end();
	while (leftitq != leftEnditq && rightitq != rightEnditq)
	{
		if (*leftitq <= *rightitq)
		{
			*moveitq = *leftitq;
			leftitq++;
		}
		else
		{
			*moveitq = *rightitq;
			rightitq++;
		}
		moveitq++;
	}
	cpyContainer(leftitq, leftEnditq, moveitq, enditq);
	cpyContainer(rightitq, rightEnditq, moveitq, enditq);
}

void	mergeSortDeque(itq startitq, itq enditq)
{
	size_t	size = std::distance(startitq, enditq);

	if (size <= 5)
	{
		insertSortDeque(startitq, enditq);
		return ;
	}
	itq	miditq = startitq + (size / 2 - 1);
	mergeSortDeque(startitq, miditq);
	mergeSortDeque(miditq, enditq);
	merge(startitq, miditq, enditq);
}

void	sortNumbersDeque(char **args)
{
	std::cout << "DEQUE IMPLEMENTATION " << std::endl;
	
	long long int	timeBef;
	long long int	timeAfter;
	double distTime;

	timeBef = getCurrTimeMicrosec();
	std::deque<int> nums;
	parseNumbersDeque(nums, args);
	if (nums.empty())
		return ;
	timeAfter = getCurrTimeMicrosec();
	distTime = (double)(timeAfter - timeBef) / 1000;
	std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;
	std::cout << "Time to perform parsing: " << distTime << std::endl;

	std::cout << "Before: ";
	for (int i = 0; i < nums.size(); i++)
		std::cout << nums[i] << " ";
	std::cout << std::endl;

	timeBef = getCurrTimeMicrosec();
	mergeSortDeque(nums.begin(), nums.end());
	timeAfter = getCurrTimeMicrosec();
	distTime = (double)(timeAfter - timeBef) / 1000;
	std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;
	std::cout << "Time to perform sorting: " << distTime << std::endl;

	std::cout << "After: ";
	for (int i = 0; i < nums.size(); i++)
		std::cout << nums[i] << " ";
	std::cout << std::endl;
}

