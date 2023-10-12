#include "Calculator.h"
#include "plugin_manager.h"

Calculator::Calculator()
{
	initPriorityTable();
}

Calculator& Calculator::getInstance()
{
	static Calculator test;
	return test;
}

std::string Calculator::makeString(std::string const& entry_arg)
{
	std::string temp;
	for (int i = 0; i < entry_arg.size(); i++)
	{
		if (entry_arg[i] != ' ')
			temp.push_back(entry_arg[i]);
	}
	return temp;
}

void Calculator::makeEntryString(std::string const& str)
{
	int i = 0;
	while (i < str.size())
	{
		if (priority_table.contains(std::string(1, str[i])))
			this->entry_string.push_back(std::string(1, str[i]));
		else
		{
			std::string temp;
			int j = i;
			while (!priority_table.contains(std::string(1, str[j])) && j < str.size())
			{
				temp.push_back(str[j]);
				j++;
			}
			this->entry_string.push_back(temp);
			i = j - 1;
		}
		i++;
	}
}

 
void Calculator::preprocess() 
{
	for (std::vector<std::string>::iterator it = entry_string.begin(); it != entry_string.end(); ++it)
	{
		if (plugin_manager.contains(*it))
		{
			auto it_plus_1 = it + 2;
			double value = stod(*it_plus_1);
			double res = plugin_manager.function(*it, value);
			*it = std::to_string(res);
			entry_string.erase(it + 1, it + 4);
		}
		else if (!priority_table.contains(*it))
		{
			try
			{
				stod(*it);
			}
			catch (...)
			{
				throw std::exception();
			}
		}
	}
}

void Calculator::polishNotation()
{
	std::stack<std::string> stack;
	for (std::vector<std::string>::const_iterator it = entry_string.cbegin(); it != entry_string.cend(); ++it)
	{
		if (priority_table.contains(*it))
		{
			if (*it == "(")
				stack.push(*it);
			else if (*it == ")")
			{
				while (stack.top() != "(")
				{
					output_string.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
			}
			else if (stack.size() == 0 || priority_table[*it] >= priority_table[stack.top()])
				stack.push(*it);
			else
			{
				output_string.push_back(stack.top());
				stack.pop();
				stack.push(*it);
			}
		}
		else
		{
			output_string.push_back(*it);
		}
	}
	while (!stack.empty())
	{
		output_string.push_back(stack.top());
		stack.pop();
	}
}

void Calculator::initPriorityTable()
{
	priority_table.insert(std::pair<std::string, int>("(", 0));
	priority_table.insert(std::pair<std::string, int>(")", 1));
	priority_table.insert(std::pair<std::string, int>("+", 2));
	priority_table.insert(std::pair<std::string, int>("-", 2));
	priority_table.insert(std::pair<std::string, int>("*", 3));
	priority_table.insert(std::pair<std::string, int>("/", 3));
	priority_table.insert(std::pair<std::string, int>("^", 4));
}

void Calculator::calculate()
{
	int i = 0;
	while (output_string.size() != 1)
	{
		if (priority_table.contains(output_string[i]))
		{
			Number a(stod(output_string[i - 2]));
			Number b(stod(output_string[i - 1]));
			std::string new_elem;
			switch (priority_table[output_string[i]])
			{
			case 2:
				if (output_string[i] == "+")
					new_elem = std::to_string((a + b).value);
				else
					new_elem = std::to_string((a - b).value);
				break;
			case 3:
				if (output_string[i] == "*")
					new_elem = std::to_string((a * b).value);
				else
					new_elem = std::to_string((a / b).value);
				break;
			case 4:
			{
				new_elem = std::to_string(plugin_manager.function("deg", a.value, b.value));
			}
			default:
				break;
			}
			output_string.erase(output_string.begin() + (i - 2), output_string.begin() + i);
			output_string[i - 2] = new_elem;
			i = 0;
		}
		else
			i++;
	}
}

void Calculator::printResult()
{
	preprocess();
	polishNotation();
	calculate();
	std::cout << output_string[0];
}