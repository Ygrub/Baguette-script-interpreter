#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <cctype>
#include <stack>
#include <chrono>

using namespace std;
using namespace chrono;

vector<string> split(string line, const char* token = " ")
{
	vector<string> finnal = {};
	string word;

	for (char c : line)
	
	{
		if (c != *token)
		{
			word += c;
		}
		else
		{
			finnal.push_back(word);
			word = "";
		}
	}
	finnal.push_back(word);
	return finnal;
	

}


bool isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool is_valid_str(const string str)
{
	int num = 0; 
	for (char c : str)
	{
		if (c == *"'")
		{
			num++;
		}
	}
	return num == 2;
}

bool is_a_int(const string str)
{
	try
	{
		int l = stoi(str);
		return true;
	}
	catch (const exception& e)
	{
		return false;
	}
}

int calculate(int a, int b, char op)
{
	switch (op)
	{
		case '+': return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
	}
	return 0;
}

int evaluate(string expression)
{
	stack<int> values;
	stack<char> ops;
	for (int i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];
		if (isdigit(c))
		{
			int num = 0;
			while (isdigit(c))
			{
				num = num*10 + (c - '0');
				c = expression[++i];
			}
			i--;
			values.push(num);
		}
		else if (c == '(')
		{
			ops.push(c);
		}
		else if (c == ')')
		{
			while (ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();
				int val1 = values.top();
				values.pop();
				char op = ops.top();
				ops.pop();
				values.push(calculate(val1, val2, op));
			}
			ops.pop();
		}
		else if (isOperator(c))
		{
			while (!ops.empty() && ops.top() != '(' && (c == '*' || c == '/') && (ops.top() == '*' || ops.top() == '/'))
			{
				int val2 = values.top();
				values.pop();
				int val1 = values.top();
				values.pop();
				char op = ops.top();
				ops.pop();
				values.push(calculate(val1, val2, op));
			}
			ops.push(c);
		}
	}
	while (!ops.empty())
	{
		int val2 = values.top();
		values.pop();
		int val1 = values.top();
		values.pop();
		char op = ops.top();
		ops.pop();
		values.push(calculate(val1, val2, op));
	}

	return values.top();
}

int get_lt(vector<string> program_lines, string label)
{
	int lt = 0;
	for (auto line : program_lines)
	{
		vector<string> code = split(line, " ");

		if (code[0] == label + ":")
		{
			return lt;
		}
		lt++;
	}
	return 0;
}


string minus_the_end(const string str)
{
	string new_str = "";
	for (int i = 0; i<str.length(); i++)
	{
		new_str+=str[i];
	}
	return new_str;
}

string process_string(const vector<string>& parts)
{
	stringstream ss;
	for (size_t i = 1; i< parts.size(); i++)
	{
		ss << parts[i] << ' ';
	}
	string result;
	getline(ss, result, '\0');
	return result.substr(1, result.length() -2);
}

string remove(const string str, const char* unwanted = "'")
{
	string newstr;
	for (int i = 0; i<str.size(); i++)
	{
		if (str[i] != *unwanted)
		{
			newstr+=str[i];
		}
	}
	return newstr;
}


