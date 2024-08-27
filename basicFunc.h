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

bool evaluate_simple_condition(string lhs, string op, string rhs, map<string, int>& Ivariables, map<string, string>& Svariables)
{
    int lhs_value;
    int rhs_value;

    // Evaluate LHS
	if (is_a_int(lhs))
    {
        lhs_value = stoi(lhs);
    }
	if (is_a_int(rhs))
    {
        lhs_value = stoi(lhs);
    }


    // Evaluate the condition
    if (op == "=") return lhs_value == rhs_value;
    if (op == "<") return lhs_value < rhs_value;
    if (op == ">") return lhs_value > rhs_value;
    if (op == "<=") return lhs_value <= rhs_value;
    if (op == ">=") return lhs_value >= rhs_value;
	if (op == "!=") return lhs_value != rhs_value;

    throw runtime_error("Unknown operator: " + op);
}

bool evaluate_condition(string condition, map<string, int>& Ivariables, map<string, string>& Svariables) {
    stringstream ss(condition);
    string token;
    vector<string> conditions;
    vector<string> operators;

    // Parse condition into individual expressions and operators
    while (ss >> token) {
        if (token == "et" || token == "ou" || token == "xou") {
            operators.push_back(token);
        } else {
            conditions.push_back(token);
        }
    }

    // Evaluate the first condition
    string lhs, op, rhs;

	
    stringstream cond_ss(conditions[0]);
	lhs = conditions[0];
    op = conditions[1];
	rhs = conditions[2];

	if (Ivariables.count(lhs))
	{
		lhs = to_string(Ivariables[lhs]);
	}
	else if (Svariables.count(lhs))
	{
		lhs = Svariables[lhs];
	}
	if (Ivariables.count(rhs))
	{
		rhs = to_string(Ivariables[rhs]);
	}
	else if (Svariables.count(lhs))
	{
		lhs = Svariables[lhs];
	}

    bool result = evaluate_simple_condition(lhs, op, rhs, Ivariables, Svariables);
    // Evaluate subsequent conditions
	//cout << condition << endl;
	/*
	if (conditions.size()>3)
	{
		
		for (int i = 0; i < conditions.size(); i+=4) 
		{
		
        	stringstream cond_ss(conditions[i]);
			lhs = conditions[i];
		    op = conditions[i+1];
			rhs = conditions[i+2];
			if (Ivariables.count(lhs))
			{
				lhs = to_string(Ivariables[lhs]);
			}
			else if (Svariables.count(lhs))
			{
				lhs = Svariables[lhs];
			}
			if (Ivariables.count(rhs))
			{
				rhs = to_string(Ivariables[rhs]);
			}
			else if (Svariables.count(lhs))
			{
				lhs = Svariables[lhs];
			}
			bool result = evaluate_simple_condition(lhs, op, rhs, Ivariables, Svariables);
			

			lhs = conditions[i+3];
	    	op = conditions[i+4];
			rhs = conditions[i+5];
			
			if (Ivariables.count(lhs))
			{
				lhs = to_string(Ivariables[lhs]);
			}
			else if (Svariables.count(lhs))
			{

				lhs = Svariables[lhs];
			}
			if (Ivariables.count(rhs))
			{
				rhs = to_string(Ivariables[rhs]);
			}
			else if (Svariables.count(lhs))
			{
				lhs = Svariables[lhs];
			}
    	    bool current_result = evaluate_simple_condition(lhs, op, rhs, Ivariables, Svariables);

        	if (operators[i] == "et") 
			{
            	result = result && current_result;
        	} 
			else if (operators[i] == "ou") 
			{
            	result = result || current_result;
    	    } 
			else if (operators[i] == "xou") 
			{
            	result = (result != current_result);  // XOR: true if one is true and the other is false
        	}
    	}
	}*/
    return result;
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


