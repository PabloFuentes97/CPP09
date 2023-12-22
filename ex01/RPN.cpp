#include <string>
#include <sstream>
#include <iostream>
#include <stack>

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

static int RPNOperations(std::stack<int> &calc, char op)
{
    int operand1 = calc.top();
    calc.pop();
    int operand2 = calc.top();
    calc.pop();
    int result;
    //std::cout << operand2 << " " << op << " " << operand1 << std::endl;
    switch(op)
    {
        case '+':
            result = operand2 + operand1;
            break ;
        case '-':
            result = operand2 - operand1;
            break ;
        case '*':
            result = operand2 * operand1;
            break ;
        case '/':
            if (operand1 == 0)
            {
                std::cout << "Error. Division by zero not allowed!" << std::endl; //cambiar por excepción
                return (0);
            }
            result = operand2 / operand1;
            break ;
    }
    calc.push(result);
    return (1);
}

int RPN(std::string args)
{
    std::stack<int> calculator;
    std::stringstream line(args);
    std::string token;
    
    while (getline(line, token, ' '))
    {
        if (token.size() > 1 || !strcmpDict(token, "0123456789+-*/"))
        {
            std::cout << "Error. Bad argument format!" << std::endl; //cambiar por excepción
            return (0);
        }
        if (strcmpDict(token, "0123456789"))
            calculator.push(strToInt(token));
        else
        {
            if (calculator.size() < 2)
            {
                std::cout << "Error. Not enough numbers to operate!" << std::endl; //cambiar por excepción
                return (0);
            }
            if (!RPNOperations(calculator, token[0]))
                return (0);
        }
    }
    if (calculator.size() > 1)
    {
        std::cout << "Error. Too many numbers to operate!" << std::endl; //cambiar por excepción
        return (0);
    }
    std::cout << calculator.top() << std::endl;
    return (1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);

    RPN(argv[1]);
    return (0);
}
