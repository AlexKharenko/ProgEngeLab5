#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

class Parser
{
	vector<string> oper={"*", "/", "+", "-"};
	queue<string> expresion;
	queue<string> tree;
	unordered_map<string, double> values;
	stack<string> opStack;
	bool is_num(string other);
	bool higher_precedence(string other);
public:
	void shuting_yard_algo();
};

struct TokenBase {
	virtual ~TokenBase() {}
};

template<class T> class Token : public TokenBase {
public:
	Token(T t) : val(t) {}
	T val;
};

typedef queue<TokenBase*> TokenQueue;
