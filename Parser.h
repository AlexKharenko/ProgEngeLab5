#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>  
#include <fstream>

using namespace std;

class Parser
{
	vector<string> oper={"*", "/", "+", "-"};
	queue<string> expresion;
	vector<string> tree;
	vector<pair<string, double>> values;
	stack<string> opStack;
	double result;
	int find(string other);
	bool is_num(string other);
	bool higher_precedence(string other);
	void shunting_yard_algo();
public:
	void read();
	void calculator();
};

