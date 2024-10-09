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
#include <format> 
#include <cmath>
#include <ctime>
#include<algorithm>

using namespace std;
using namespace chrono;


vector<string> split(string line, const char token = *" ")
{
	vector<string> finnal = {};
	string word;

	for (char c : line)
	
	{
		if (c != token)
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
	string str(1, c);
	vector<string> operators = {"/", "(", ")", "+", "-", "[", "]", "{", "}", "=", "!", " ", "*", "<", ">"};
	for (int i = 0; i<operators.size(); ++i)
	{
		if (operators[i] == str) return true;
	}
	return false;
}

bool is_good_bgs_string(vector<string> str)
{
	int num_of_g = 0;
	for (auto n : str)
	{
		for (auto c : n)
		{
			if (c == *"'") num_of_g ++;
		}
	}
	return !(num_of_g%2);

}

bool has_an_operator(const string str)
{
	for (int i = 0; i<str.size(); ++i)
	{
		if (isOperator(str[i])) return true;
	}
	return false;
}


int get_lt(const vector<string> program_lines, const string label)
{
	int lt = 0;
	for (auto line : program_lines)
	{
		vector<string> code = split(line, *" ");

		if (code[0] == label + ":") return lt;
		
		lt++;
	}
	return 0;
}


string minus_the_end(const string str)
{
	string new_str = "";
	for (int i = 0; i<str.length(); i++) new_str+=str[i];
	
	return new_str;
}

string remove(const string str, const char* unwanted = "'")
{
	string newstr;
	for (int i = 0; i<str.size(); i++)
	{
		if (str[i] != *unwanted) newstr+=str[i];
		
	}
	return newstr;
}

string add_string(map<string, string> Svariables, string expretion)
{
	vector<string> expretion_minus_the_op = split(expretion, *"+");
	for (int i = 0; i<expretion_minus_the_op.size(); i++)
	{
		if (Svariables.count(expretion_minus_the_op[i])>0) expretion_minus_the_op[i] = Svariables[expretion_minus_the_op[i]];
		else if (expretion_minus_the_op[i].find("'")%2) throw runtime_error("String pas valide.");
	}
	string new_expretion = "";
	for (auto i : expretion_minus_the_op) 
	{
		new_expretion+=i;
	}
	new_expretion = remove(new_expretion, "'");
	return new_expretion;
}

string get_variables_value_in_string(map<string, int> Ivariables, map<string, string> Svariables, string possible_var_name, int line)
{
	if (Ivariables.count(possible_var_name) != 0) return to_string(Ivariables[possible_var_name]);
	else if (Svariables.count(possible_var_name) != 0) return Svariables[possible_var_name];
	else if (is_a_int(possible_var_name)) return possible_var_name;
	else if (isOperator(possible_var_name[0])) throw runtime_error("Erreur à la ligne " + to_string(line) + " \nLa variable '" + possible_var_name + "' n'est pas déclaré.");
	return "";
}

string get_expretion(vector<string> str, map<string, int> Ivariables, map<string, string> Svariables, int line)
{
	string expretion = "";
	for (int i = 1; i<str.size(); ++i)
	{
		string possible_var_name = "";
		for (auto c : str[i])
		{
			if (c == *" ") continue;
			if (is_a_int(to_string(c))) expretion += c;
			else if (isOperator(c) && possible_var_name.length()==0) expretion += c;
			else if(Ivariables.count(possible_var_name) == 0 && Svariables.count(possible_var_name) == 0) possible_var_name += c;
			else if (i == str.size()-1)
			{
				expretion += get_variables_value_in_string(Ivariables, Svariables, possible_var_name, line) + c;
				possible_var_name = "";
			}		
		}
	}
	return expretion;
}

string get_literal_string(vector<string> str, map<string, int> Ivariables, map<string, string> Svariables, int line)
{
	string literal_string = "";
	for (int i = 1; i<str.size(); i++)
	{
		str[i] = remove(str[i]);
		if (str[i][0] == *"$")
		{
			string var_name = remove(str[i], "$");
			str[i] = get_variables_value_in_string(Ivariables, Svariables, var_name, line);
		}
		literal_string += str[i] + " ";
	}
	return literal_string;
}

string add_strings(string unproced_string, map<string, string> Svariables)
{
	unproced_string = remove(unproced_string, "'");
	string proced_string = remove(unproced_string, "+");
	if (proced_string.find("$") < 9287434)
	{
		for (int i = 0; i<proced_string.length(); ++i)
		{
			if (proced_string[i] == *"$")
			{
				string possible_var_name = "";
				for (int j = i+1; j<proced_string.length(); ++j)
				{
					if (isOperator(proced_string[j]) || j == proced_string.length())
					{
						for (int o = i; o<j; ++o) proced_string[o] = *"";
						for (int o = 0; o<Svariables[possible_var_name].length(); ++o) 
						{
							proced_string[i+o] = Svariables[possible_var_name][o];
							proced_string[i+o] += *" ";
						}
						possible_var_name = "";
					}
				possible_var_name += proced_string[j];			
				}
			}
		}
	}
	return proced_string;
}

string make_redable_expretion(string expretion)
{
	string proced_string = "";
	for (auto c : expretion)
	{
		if (isOperator(c))  proced_string += ' ' + c + ' ';
		else proced_string+=c;
	}
	return proced_string;
}

 
// Function to perform arithmetic operations.


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

double eval(const string& expression) {
    stack<double> values;  // Stack to store numbers
    stack<char> ops;       // Stack to store operators

    for (int i = 0; i < expression.length(); i++) {
        // Skip whitespaces
        if (isspace(expression[i])) continue;

        // Current token is a number, push it to the value stack
        if (isdigit(expression[i])) {
            double val = 0;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    double factor = 0.1;
                    i++;
                    while (i < expression.length() && isdigit(expression[i])) {
                        val = val + (expression[i] - '0') * factor;
                        factor /= 10;
                        i++;
                    }
                    break;
                }
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;  // adjust for the increment in the loop
        }

        // Current token is an operator
        else if (expression[i] == '+' || expression[i] == '-' ||
                 expression[i] == '*' || expression[i] == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    // Entire expression has been parsed, apply remaining operators
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

string convert_var_expretion_to_expretion(string unproced_string, map<string, int> Ivariables, map<string, string> Svariables, int line)
{
	
	vector<string> procecing_string = split(unproced_string, ' ');
	string processed_string = "";
	
	for (auto var_name : procecing_string)
	{
		
		if (var_name == "") continue;
		if (isOperator(var_name[0])) 
		{
			processed_string+= var_name + ' ';
			continue;
		}
		if (Ivariables.count(var_name)) var_name = to_string(Ivariables[var_name]);
		else if (Svariables.count(var_name)) var_name = Svariables[var_name];
		else if (!is_a_int(var_name)) throw runtime_error("Erreur valeur ligne: " + to_string(line) + " La variable '" + var_name + "' n'est pas déclaré");
		processed_string+=var_name+' ';
	}
	return processed_string;
}

bool evaluateComparison(vector<string> expretion, map<string, int> Ivariables, map<string, string> Svariables, int line) {
    string expression = "";
	for (int i = 1; i < expretion.size(); i++) expression+= expretion[i] + ' ';

	
	expression = convert_var_expretion_to_expretion(expression,  Ivariables, Svariables, line);
	
    // Lire le premier opérande, l'opérateur, et le second opérande
	string leftOperand = split(expression, ' ')[0];
	string operatorSymbol = split(expression, ' ')[1];
	string rightOperand = split(expression, ' ')[2];
    // Vérifier quel opérateur est utilisé et effectuer la comparaison appropriée
    if (operatorSymbol == "==") {
        return leftOperand == rightOperand;
    } else if (operatorSymbol == "!=") {
        return leftOperand != rightOperand;
    } else if (operatorSymbol == "<") {
        return leftOperand < rightOperand;
    } else if (operatorSymbol == ">") {
        return leftOperand > rightOperand;
    } else if (operatorSymbol == "<=") {
        return leftOperand <= rightOperand;
    } else if (operatorSymbol == ">=") {
        return leftOperand >= rightOperand;
    } else {
        throw invalid_argument(operatorSymbol + "n'est pas un opérateur reconnu.");
    }
}



void afficher(vector<string> str, map<string, int> Ivariables, map<string, string> Svariables, int line)
{
	if (!is_good_bgs_string(str)) 
	{
		throw runtime_error("Erreur argument ligne: " + to_string(line) + " argument invalide pour la fonction 'afficher'.\n L'argument peut-être des formes suivantent :\n Pour une chêne de caractaire simple : afficher 'Ceci est une chêne de caractaire simple'\n Pour afficher une variable : afficher nom_de_la_variable\n Pour une chêne de caractaire contenant une variable : afficher 'Ceci est une chêne de cractaire avec une $variable' ");
	}
	
	string literal_string = "";
	string unproced_string = "";
	for (int i = 1; i<str.size(); ++i)  
	{
		if (i != str.size()-1) unproced_string+= str[i]+ " ";
		else unproced_string+=str[i];
	}
	if (Ivariables.count(unproced_string)) literal_string = to_string(Ivariables[unproced_string]);
	else if (Svariables.count(unproced_string)) literal_string = Svariables[unproced_string];
	else if (unproced_string.find("'") > 9385798475) //Si il n'y à pas de " ' "
	{
		
		string processed_string = convert_var_expretion_to_expretion(unproced_string, Ivariables, Svariables, line);

		try 
		{
			literal_string = to_string(eval(processed_string));
		
		}
		catch (const invalid_argument& ia) 
		{
			
			for (auto var_name : split(processed_string, *"+"))
			{
				if (isOperator(var_name[0]) && var_name != "+") throw runtime_error("Erreur à la ligne : " + to_string(line) + "\nL'opérateur '" + var_name + "' n'est pas valide pour une operation de string.");
				else if (var_name == "+") literal_string+="";
				else literal_string+=var_name;
			}
		}
	}
	else literal_string = remove(unproced_string, "'");
	//cout << unproced_string.find("'") << " " << has_an_operator(unproced_string) << endl;

	cout << literal_string << endl;
}

string get_var_name(vector<string> raw_token_expretion, int line)
{
	string unprocesed_var_name = raw_token_expretion[1];

	if (has_an_operator(unprocesed_var_name)) throw runtime_error("Erreur ligne " + to_string(line) + "\n caracter non autoriser dans le nom de la variable.");

	string procesed_var_name = "";
	for (int i = 0; i<unprocesed_var_name.length(); i++)
	{
		if (unprocesed_var_name[i] == *"=") break;
		else procesed_var_name+=unprocesed_var_name[i];
	}
	return procesed_var_name;

}

int assigner_int(vector<string> raw_token_expretion, map<string, int> Ivariables, int line)
{
	
	string raw_string_expretion = "";
	for (int i = 2; i<raw_token_expretion.size(); ++i)  
	{
		for (int j =0; j<raw_token_expretion[i].length(); ++j) raw_string_expretion+=raw_token_expretion[i][j];
		raw_string_expretion+=" ";
	}

	int result = eval(raw_string_expretion);


	return result;
}

string assigner_str(vector<string> raw_token_expretion, map<string, string> Svariables, int line)
{
	
	string raw_string_expretion = "";
	for (int i = 2; i<raw_token_expretion.size(); ++i)  
	{
		for (int j =0; j<raw_token_expretion[i].length(); ++j) 
		{
			if (raw_token_expretion[i][j] == '=' && i == 2) continue;
			else raw_string_expretion+=raw_token_expretion[i][j];
		}
		raw_string_expretion+=" ";
	}
	
	if (!is_good_bgs_string(split(raw_string_expretion, ' '))) throw runtime_error("Non. Je vais regréter de ne pas avoir donnée plus d'info plus tard");



	string result = remove(raw_string_expretion, "'");


	return result;
}
vector<string> make_token(const string line, map<string, int>& Ivariables, map<string, string>& Svariables) {
    vector<vector<string>> tokens = {{}};
    const char * line_breaker = ";";
    string current_tokens = "";
    int line_number = 0;

    for (auto c : line) {
        if (c == ' ' && !current_tokens.empty()) 
		{
            tokens[line_number].push_back(current_tokens);
            current_tokens = "";
        } 
		else current_tokens += c;
        
    }

    // Push the last token if it's not empty
    if (!current_tokens.empty()) tokens[line_number].push_back(current_tokens);
    

    // Remove unwanted characters and empty strings from tokens
    for (int i = 0; i < tokens.size(); i++) {
        for (int j = 0; j < tokens[i].size(); ) {
            tokens[i][j] = remove(tokens[i][j], " ");
            if (tokens[i][j].empty()) tokens[i].erase(tokens[i].begin() + j);
        
			else j++;
            
        }
    }
	//int i = 0;
    /*for (const auto& line_tokens : tokens) {
		cout << i << " ";
		i++;
        for (const auto& token : line_tokens) {
            cout << "[" << token << "] ";
			
        }
        cout << endl;
    }*/
	return tokens[0];
}