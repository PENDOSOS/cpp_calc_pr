#include <iostream>
#include "calculator.h"

 
int main()
{
	auto& calculator = Calculator::getInstance();  

	std::string expression;
	std::cout << "Enter the expression you want to calculate: ";
	std::getline(std::cin, expression);

	calculator.makeEntryString(calculator.makeString(expression));

	try
	{
		calculator.printResult();
	}
	catch (const std::exception&)
	{
		std::cout << "Error";
	}
	return 0;
}