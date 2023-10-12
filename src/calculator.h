#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <unordered_map>
#include <stack> 
#include "number.h"
#include "plugin_manager.h"


class Calculator
{
public:
	Calculator(Calculator const&) = delete;
	Calculator& operator = (Calculator const&) = delete;
	Calculator(Calculator&&) = delete;
	Calculator& operator = (Calculator&&) = delete;

	static Calculator& getInstance();

	std::string makeString(std::string const& entry_arg);
	void makeEntryString(std::string const& str);

	void printResult();

	~Calculator() = default;

private:
	Calculator();

	void initPriorityTable();
	void preprocess();
	void polishNotation();
	void calculate();

	PluginManager plugin_manager;

	std::vector<std::string> entry_string;
	std::unordered_map<std::string, int> priority_table;
	std::vector<std::string> output_string;
};