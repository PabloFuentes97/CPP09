#include "PmergeMe.hpp"

//-------------------------UTILS-------------------------

const char	*invalidArg::what() const throw ()
{
	return ("Invalid arg!");
}

int charcmpDict(char c, std::string dict)
{
    int dictSize = dict.size();
    int same = 0;

    for (int i = 0; i < dictSize; i++)
    {
         if (c == dict[i])
            same++;
    }
    if (same < 1)
        return (0);
    return (1);
}

int strcmpDict(std::string str, std::string dict)
{
    int strSize = str.size();
    int dictSize = dict.size();
    int same;

    for (int i = 0; i < strSize; i++)
    {
        same = 0;
        for (int j = 0; j < dictSize; j++)
        {
            if (str[i] == dict[j])
                same++;
        }
        if (same < 1)
            return (0);
    }
    return (1);
}

int strToInt(std::string str)
{
    const char *charptr;

    charptr = str.c_str();
    return (atoi(charptr));
}

long long int   getCurrTimeMicrosec(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_usec);
}

int	generateJacobsthal(size_t n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (generateJacobsthal(n - 1) + 2 * (generateJacobsthal(n - 2)));
}

//-------------------------DEQUE-------------------------
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

void	printDeque(itq start, itq end)
{
	while (start != end)
	{
		std::cout << *start << " ";
		start++;
	} 
	std::cout << std::endl;
}

void	cpyDeque(itq	srcStart, itq srcEnd, itq destStart, itq destEnd)
{
	while (srcStart != srcEnd && destStart != destEnd)
	{
		*destStart = *srcStart;
		srcStart++;
		destStart++;
	}
}
typedef std::deque<std::pair<int, int> >::iterator itpairs;
void	recursiveInsertSort(std::deque<std::pair<int, int> > &deque, size_t n)
{
	if (n <= 1)
		return ;
	recursiveInsertSort(deque, n - 1);
	std::pair<int, int> last = deque[n - 1];
	deque.erase(deque.begin() + (n - 1));
	//int	i = n - 2;
	int	i = n - 2;
	while (i >= 0 && deque[i].second > last.second)
	{
		//deque[i + 1] = deque[i];
		i--;
	}
	deque.insert(deque.begin() + i + 1, last);
	//deque[i + 1] = last;
}

typedef std::deque<int>::iterator itdeque;
void    binaryInsertionDeque(std::deque<int> &deq, itdeque const &begin, itdeque const &end, int num)
{
    size_t  len = distance(begin, end);
    if (len == 0)
    {
        /*if (deq.begin() == begin)
            deq.push_front(num);
        else if (deq.end() == end)
            deq.push_back(num);
		*/
		deq.insert(begin, num);
        return ;
    }
    size_t	find = len / 2;
    itdeque	itf = begin + find;
    /*if (*itf == num ||(*itf < num && num < *(itf + 1)))  
    {
        deq.insert(itf + 1, num);
        return ;
    }*/
    if (num < *itf)
        binaryInsertionDeque(deq, begin, itf, num);
    else
        binaryInsertionDeque(deq, itf + 1, end, num);
}

void	generateJacobsthalSequenceDeque(std::deque<int> &deq, int size)
{
	int	jIndex = 2;
	int	jNum = generateJacobsthal(jIndex);
	deq.push_back(jNum);
	jIndex++;
	while (jNum < size)
	{
		int	jLast = jNum;
		jNum = generateJacobsthal(jIndex);
		deq.push_back(jNum);
		jIndex++;
		int	add = jNum - 1;
		while (add > jLast)
		{
			deq.push_back(add);
			add--;
		}
	}
}
void	mergeInsertFordJohnson(std::deque<int> &deque)
{
	size_t	len = deque.size();
	bool	straggler = false;
	int		straggler_n;
	if (len % 2 != 0)
		straggler = true;
	if (straggler)
	{
		//std::cout << "Número impar" << std::endl;
		straggler_n = *(deque.end() - 1);
		deque.pop_back();
		//std::cout << "Número impar quitado" << std::endl;
	}
	//crear lista con parejas
	std::deque<std::pair<int,int > >	pairs;
	int	i = 0;
	for (itdeque itb = deque.begin(), ite = deque.end(); itb != ite; itb += 2)
	{
		pairs.push_back(std::pair<int, int>(*itb, *(itb + 1)));
		if (pairs[i].first > pairs[i].second)
		{
			std::swap(pairs[i].first, pairs[i].second);
			/*int	swap = pairs[i].first;
			pairs[i].first = pairs[i].second;
			pairs[i].second = swap;*/
		}
		i++;
	}

	//ordenar lista de parejas
	/*std::cout << "Parejas sin ordenar" << std::endl;
	for (itpairs itb = pairs.begin(), ite = pairs.end(); itb != ite; itb++)
		std::cout << "[" << itb->first << ", " << itb->second << "]" << std::endl;
	*/
	recursiveInsertSort(pairs, pairs.size());
	/*std::cout << "Parejas ordenadas" << std::endl;
	for (itpairs itb = pairs.begin(), ite = pairs.end(); itb != ite; itb++)
		std::cout << "[" << itb->first << ", " << itb->second << "]" << std::endl;
	*/

	//crear lista o cadena de 'a' (elemento mayor, cadena principal) y de 'b' (elemento menor)
	std::deque<int> a;
	std::deque<int> b;
	for (itpairs itb = pairs.begin(), ite = pairs.end(); itb != ite; itb++)
	{
		a.push_back(itb->second);
		b.push_back(itb->first);
	}
	/*
	std::cout << "Lista de 'a' (elementos mayores)" << std::endl;
	for (itdeque itb = a.begin(), ite = a.end(); itb != ite; itb++)
		std::cout << *itb << std::endl;
	std::cout << "Lista de 'b' (elementos menores)" << std::endl;
	for (itdeque itb = b.begin(), ite = b.end(); itb != ite; itb++)
		std::cout << *itb << " " << std::endl;
	*/
	//meto primer elemento de b (el menor de todos) al principio de a - ya sé que debe ser siempre el primero
	a.push_front(b[0]);
	b.pop_front();

	//lista de numeros de jacobsthal
	std::deque<int> jacobsthalSeq;
	size_t	bSize =  b.size();
	generateJacobsthalSequenceDeque(jacobsthalSeq, bSize);
	/*std::cout << "Secuencia de Jacobsthal" << std::endl;
	for (itdeque ib = jacobsthalSeq.begin(), ie = jacobsthalSeq.end(); ib != ie; ib++)
		std::cout << *ib << std::endl;
	*/
	std::deque<int>	indexes;
	for (itdeque	itb = jacobsthalSeq.begin(), ite = jacobsthalSeq.end(); itb != ite; itb++)
	{
		(*itb)--;
		if (*itb < bSize)
			indexes.push_back(*itb);
	}
	/*std::cout << "Orden de índices a insertar" << std::endl;
	for (itdeque ib = indexes.begin(), ie = indexes.end(); ib != ie; ib++)
		std::cout << *ib << std::endl;
	std::cout << "Longitud de b: " << b.size() << " Longitud de índices: " << indexes.size() << std::endl;
	*/
	//insercion binaria
	int	pairIndex = 0;
	for (itdeque ib = indexes.begin(), ie = indexes.end(); ib != ie; ib++, pairIndex++)
	{
		//itq		lim = std::find(a.begin(), a.end(), pairs[pairIndex].second);
		binaryInsertionDeque(a, a.begin(), a.end(), b[*ib]);
		//binaryInsertionDeque(a, a.begin(), lim + 1, b[*ib]);
	}
		
	if (straggler)
		binaryInsertionDeque(a, a.begin(), a.end(), straggler_n);	
	//copio deck 'a' ordenado a deck original
	for (itdeque itb = a.begin(), ite = a.end(), itc = deque.begin(); itb != ite; itb++, itc++)
		*itc = *itb;
}

void	sortNumbersDeque(char **args)
{
	std::cout << "-----------------DEQUE IMPLEMENTATION-----------------" << std::endl;
	
	long long int	timeBef;
	long long int	timeAfter;

	//PARSE
	timeBef = getCurrTimeMicrosec();
	std::deque<int> nums;
	parseNumbersDeque(nums, args);
	if (nums.empty())
		return ;
	timeAfter = getCurrTimeMicrosec();
	/*std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;*/
	std::cout << "Time to perform parsing: " << (double)(timeAfter - timeBef) / 1000 << std::endl;

	//SORT
	std::cout << "Before: ";
	printDeque(nums.begin(), nums.end());
	timeBef = getCurrTimeMicrosec();
	mergeInsertFordJohnson(nums);
	timeAfter = getCurrTimeMicrosec();
	/*std::cout << "Tiempo 1: " << timeBef << " Tiempo 2: " << timeAfter << " Diferencia: "
		<< timeAfter - timeBef << std::endl;*/
	std::cout << "Time to perform sorting: " << (double)(timeAfter - timeBef) / 1000 << std::endl;
	std::cout << "After: ";
	printDeque(nums.begin(), nums.end());
}

//-------------------------LIST-------------------------

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
