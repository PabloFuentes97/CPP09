#pragma once
#include <string>
#include <deque>
#include <list>
#include <iostream>
#include <sstream>
#include <sys/time.h>

class	invalidArg : public std::exception
{
	public:
		virtual const char	*what() const throw ();
};

//utils
int 			charcmpDict(char c, std::string dict);
int 			strcmpDict(std::string str, std::string dict);
int 			strToInt(std::string str);
long long int   getCurrTimeMicrosec(void);
int				generateJacobsthal(size_t n);

//DEQUE IMPLEMENTATION
typedef std::deque<int>::iterator itq;
typedef std::deque<std::pair<int,int > >::iterator itqp;

//parse
void	parseNumbersDeque(std::deque<int> &numDeque, char **args);
void	printDeque(itq start, itq end);
void	cpyDeque(itq	srcStart, itq srcEnd, itq destStart, itq destEnd);

//sorting algorithms
void	insertSortDeque(itq startIt, itq endIt);
void	mergeSortDeque(itq startIt, itq endIt);

//LIST IMPLEMENTATION
typedef std::list<int>::iterator itl;
typedef std::list<std::pair<int, int> >::iterator itlp;

//parse
void	parseNumbersList(std::list<int> &numList, char **args);
void	printList(itl start, itl end);
void	cpyList(itl	srcStart, itl srcEnd, itl destStart, itl destEnd);

//sorting algorithms
void	insertSortList(itl startIt, itl endIt);
void	mergeSortList(itl startIt, itl endIt);

//main function
void	sortNumbersDeque(char **args);
void	sortNumbersList(char **args);