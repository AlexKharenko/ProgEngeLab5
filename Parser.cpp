#include "Parser.h"


int Parser::find(string other)
{
	for (int i = 0; i < values.size(); i++)
	{
		if (values[i].first == other) {
			return i;
		}
	}
	return -1;
}

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
	else if (other == oper[1] && opStack.top()!= oper[0] && opStack.top() != oper[1]) {
		return true;
	}
	else if (other == oper[0] && opStack.top() != oper[0] && opStack.top() != oper[1]) {
		return true;
	}
	else {
		return false;
	}
}


void Parser::read()
{
	fstream in("input.txt");
	int expr=0;
	int i = 0;
	if (!in.is_open()) {
		cout << "Error" << endl;
	}
	else {
		while (!in.eof()) {
			char buff;
			in.get(buff);
			if (buff == '\n') {
				expr++;
			}
		}
		in.close();
		in.open("input.txt");
		i = 0;
		while (i != expr) {
			string buff, eq, val;
			in >> buff >> eq >> val;
			values.resize(expr);

			values[i].first = buff;
			values[i].second = stod(val);
			i++;
		}
		while (!in.eof()) {
			string temp;
			in >> temp;
			expresion.push(temp);
		}
		in.close();
	}
	
}

void Parser::shunting_yard_algo()
{
	
	int index = 0;
	while (!expresion.empty()) {
		if (is_num(expresion.front()))
		{
			tree.push_back(expresion.front());
			expresion.pop();
			index++;
		}
		else {
			if (higher_precedence(expresion.front())) {
				opStack.push(expresion.front());
				expresion.pop();
			}
			else {
				tree.push_back(opStack.top());
				opStack.pop();
				opStack.push(expresion.front());
				expresion.pop();
			}
		}
	}
	while (!opStack.empty()) {
		tree.push_back(opStack.top());
		opStack.pop();
	}
}

void Parser::calculator()
{
	shunting_yard_algo();
	vector<string> eval;
	bool first = true;
	int index = 0;
	while (!tree.empty()) {
		string right;
		while (is_num(tree[index])) {
			index++;
		}
		if (first)
		{
			eval.push_back(tree[index - 2]);
			right = tree[index - 1];
			tree.erase(tree.begin() + index - 2, tree.begin() + index);
			first = false;
			index -= 2;
		}
		else {
			right = tree[index - 1];
			tree.erase(tree.begin() + index - 1);
			index -= 1;
		}
		if (tree[index] == "+") {
			double rt, lt;
			if (find(eval[0]) != -1) {
				lt = values[find(eval[0])].second;
			}
			else {
				lt = stod(eval[0]);
			}
			if (find(right) != -1) {
				rt = values[find(right)].second;
			}
			else {
				rt = stod(right);
			}
			
			eval[0] = to_string(lt + rt);
			tree.erase(tree.begin() + index);
		}
		else if (tree[index] == "-") {
			double rt, lt;
			if (find(eval[0]) != -1) {
				lt = values[find(eval[0])].second;
			}
			else {
				lt = stod(eval[0]);
			}
			if (find(right) != -1) {
				rt = values[find(right)].second;
			}
			else {
				rt = stod(right);
			}
			eval[0] = to_string(lt - rt);
			tree.erase(tree.begin() + index);
		}
		else if (tree[index] == "*") {
			double rt, lt;
			if (find(eval[0]) != -1) {
				lt = values[find(eval[0])].second;
			}
			else {
				lt = stod(eval[0]);
			}
			if (find(right) != -1) {
				rt = values[find(right)].second;
			}
			else {
				rt = stod(right);
			}
			eval[0] = to_string(lt * rt);
			tree.erase(tree.begin() + index);
		}
		else if (tree[index] == "/") {
			double rt, lt;
			if (find(eval[0]) != -1) {
				lt = values[find(eval[0])].second;
			}
			else {
				lt = stod(eval[0]);
			}
			if (find(right) != -1) {
				rt = values[find(right)].second;
			}
			else {
				rt = stod(right);
			}
			eval[0] = to_string(lt / rt);
			tree.erase(tree.begin() + index);
		}
		index = 0;
	}
	result = stod(eval[0]);
	cout << "Result: " <<result<< endl;
}
