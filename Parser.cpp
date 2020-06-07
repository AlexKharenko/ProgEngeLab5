#include "Parser.h"
#include "Parser.h"

bool Parser::is_num(string other)
{
	for (int i = 0; i < oper.size(); i++)
	{
		if (oper[i] == other) {
			return false;
		}
	}
	return true;
}

bool Parser::higher_precedence(string other)
{
	if (opStack.empty())
	{
		return true;
	}
	else if (other != oper[0] && other != oper[1] && opStack.top()!= oper[0] && opStack.top() != oper[1]) {
		return true;
	}
	else {
		return false;
	}
}

void Parser::shuting_yard_algo()
{
	
	int index = 0;
	while (!expresion.empty()) {
		if (is_num(expresion.front()))
		{
			tree.push(expresion.front());
			expresion.pop();
			index++;
		}
		else {
			if (higher_precedence(expresion.front())) {
				opStack.push(expresion.front());
				expresion.pop();
			}
			else {
				tree.push(opStack.top());
				opStack.pop();
				opStack.push(expresion.front());
				expresion.pop();
			}
		}
	}
	while (!opStack.empty()) {
		tree.push(opStack.top());
		opStack.pop();
	}
}
