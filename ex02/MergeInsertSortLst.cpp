#include <sstream>
#include "PmergeMe.hpp"

itl	prevItlList(itl it, int n)
{
	std::advance(it, n * -1);
	return (it);
}

itl	nextItlList(itl it, int n)
{
	std::advance(it, n);
	return (it);
}

itlp	prevItlpList(itlp it, int n)
{
	std::advance(it, n * -1);
	return (it);
}

itlp	nextItplList(itlp it, int n)
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

void	recursiveInsertSort(std::list<std::pair<int, int> > &list, size_t n)
{
	if (n <= 1)
		return ;
	recursiveInsertSort(list, n - 1);
	std::pair<int, int> last = *nextItplList(list.begin(), n - 1);
	list.erase(nextItplList(list.begin(), n - 1));
	//int	i = n - 2;
	int	i = n - 2;
	while (i >= 0 && (*nextItplList(list.begin(), i)).second > last.second)
	{
		//list[i + 1] = list[i];
		i--;
	}
	list.insert(nextItplList(list.begin(), i + 1), last);
	//list[i + 1] = last;
}

typedef std::list<int>::iterator itl;
void    binaryInsertionlist(std::list<int> &list, itl const &begin, itl const &end, int num)
{
    size_t  len = distance(begin, end);
    if (len == 0)
    {
        /*if (deq.begin() == begin)
            deq.push_front(num);
        else if (deq.end() == end)
            deq.push_back(num);
		*/
		list.insert(begin, num);
        return ;
    }
    size_t	find = len / 2;
    itl	itf = nextItlList(begin, find);
    /*if (*itf == num ||(*itf < num && num < *(itf + 1)))  
    {
        deq.insert(itf + 1, num);
        return ;
    }*/
    if (num < *itf)
        binaryInsertionlist(list, begin, itf, num);
    else
        binaryInsertionlist(list, nextItlList(itf, 1), end, num);
}

void	generateJacobsthalSequenceLst(std::list<int> &lst, int size)
{
	int	jIndex = 2;
	int	jNum = generateJacobsthal(jIndex);
	lst.push_back(jNum);
	jIndex++;
	while (jNum < size)
	{
		int	jLast = jNum;
		jNum = generateJacobsthal(jIndex);
		lst.push_back(jNum);
		jIndex++;
		int	add = jNum - 1;
		while (add > jLast)
		{
			lst.push_back(add);
			add--;
		}
	}
}

void	mergeInsertFordJohnsonLst(std::list<int> &list)
{
	size_t	len = list.size();
	bool	straggler = false;
	int		straggler_n;
	if (len % 2 != 0)
		straggler = true;
	if (straggler)
	{
		//std::cout << "Número impar" << std::endl;
		straggler_n = list.back();
		list.pop_back();
		//std::cout << "Número impar quitado" << std::endl;
	}
	//crear lista con parejas
	std::list<std::pair<int,int > >	pairs;
	int	i = 0;
	for (itl itb = list.begin(), ite = list.end(); itb != ite; itb = nextItlList(itb, 2), i++)
	{
		pairs.push_back(std::pair<int, int>(*itb, *nextItlList(itb, 1)));
		if ((*nextItplList(pairs.begin(), i)).first > (*nextItplList(pairs.begin(), i)).second)
		{
			std::swap((*nextItplList(pairs.begin(), i)).first, (*nextItplList(pairs.begin(), i)).second);
			/*int	swap = (*nextItplList(pairs.begin(), i)).first;
			(*nextItplList(pairs.begin(), i)).first  = (*nextItplList(pairs.begin(), i)).second;
			(*nextItplList(pairs.begin(), i)).second = swap;*/
		}
		//i++; //esto meterlo en el for
	}
	//ordenar lista de parejas
	/*
	std::cout << "Parejas sin ordenar" << std::endl;
	for (itlp itb = pairs.begin(), ite = pairs.end(); itb != ite; itb++)
		std::cout << "[" << itb->first << ", " << itb->second << "]" << std::endl;*/
	recursiveInsertSort(pairs, pairs.size());
	/*
	std::cout << "Parejas ordenadas" << std::endl;
	for (itlp itb = pairs.begin(), ite = pairs.end(); itb != ite; itb++)
		std::cout << "[" << itb->first << ", " << itb->second << "]" << std::endl;
	*/
	//crear lista o cadena de 'a' (elemento mayor, cadena principal) y de 'b' (elemento menor)
	std::list<int> a;
	std::list<int> b;
	for (itlp itb = pairs.begin(), ite = pairs.end(); itb != ite; itb++)
	{
		a.push_back(itb->second);
		b.push_back(itb->first);
	}
	/*std::cout << "Lista de 'a' (elementos mayores)" << std::endl;
	for (itl itb = a.begin(), ite = a.end(); itb != ite; itb++)
		std::cout << *itb << std::endl;
	std::cout << "Lista de 'b' (elementos menores)" << std::endl;
	for (itl itb = b.begin(), ite = b.end(); itb != ite; itb++)
		std::cout << *itb << " " << std::endl;*/

	//meto primer elemento de b (el menor de todos) al principio de a - ya sé que debe ser siempre el primero
	a.push_front(*b.begin());
	b.pop_front();

	//lista de numeros de jacobsthal - meter esto en una funcion aparte
	std::list<int> jacobsthalSeq;
	size_t	bSize =  b.size();
	generateJacobsthalSequenceLst(jacobsthalSeq, bSize);
	/*std::cout << "Secuencia de Jacobsthal" << std::endl;
	for (itl ib = jacobsthalSeq.begin(), ie = jacobsthalSeq.end(); ib != ie; ib++)
		std::cout << *ib << std::endl;*/
	std::list<int>	indexes;
	for (itl	itb = jacobsthalSeq.begin(), ite = jacobsthalSeq.end(); itb != ite; itb++)
	{
		(*itb)--;
		if (*itb < bSize)
			indexes.push_back(*itb);
	}
	/*std::cout << "Orden de índices a insertar" << std::endl;
	for (itl ib = indexes.begin(), ie = indexes.end(); ib != ie; ib++)
		std::cout << *ib << std::endl;
	std::cout << "Longitud de b: " << b.size() << " Longitud de índices: " << indexes.size() << std::endl;
	*/
	//insercion binaria
	int	pairIndex = 0;
	for (itl ib = indexes.begin(), ie = indexes.end(); ib != ie; ib++)
	{
		//itl		lim = std::find(a.begin(), a.end(), (*nextItplList(pairs.begin(), pairIndex)).second);
		//binaryInsertionlist(a, a.begin(), lim, *nextItlList(b.begin(), *ib));
		binaryInsertionlist(a, a.begin(), a.end(), *nextItlList(b.begin(), *ib));
	}
	if (straggler)
		binaryInsertionlist(a, a.begin(), a.end(), straggler_n);
	
	//copio lista 'a' ordenada a lista original
	for (itl itb = a.begin(), ite = a.end(), itc = list.begin(); itb != ite; itb++, itc++)
		*itc = *itb;
}

void	sortNumbersList(char **args)
{
	std::cout << "-----------------LIST IMPLEMENTATION-----------------" << std::endl;
	
	long long int	timeBef;
	long long int	timeAfter;
	double distTime;

	//PARSE
	timeBef = getCurrTimeMicrosec();
	std::list<int> nums;
	parseNumberslist(nums, args);
	if (nums.empty())
		return ;
	timeAfter = getCurrTimeMicrosec();
	distTime = (double)(timeAfter - timeBef) / 1000;
	/*std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;*/
	std::cout << "Time to perform parsing: " << distTime << std::endl;

	//SORT
	std::cout << "Before: ";
	printList(nums.begin(), nums.end());
	timeBef = getCurrTimeMicrosec();
	mergeInsertFordJohnsonLst(nums);
	timeAfter = getCurrTimeMicrosec();
	distTime = (double)(timeAfter - timeBef) / 1000;
	/*std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;*/
	std::cout << "Time to perform sorting: " << distTime << std::endl;
	std::cout << "After: ";
	printList(nums.begin(), nums.end());
}

