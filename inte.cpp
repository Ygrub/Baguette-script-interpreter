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
using namespace std::chrono;
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // Attention à la division par zéro
    }
    return 0;
}

int evaluate(string expression) {
    stack<int> values;
    stack<char> ops;
    for (int i = 0; i < expression.length(); ++i) { // Declare and initialize i
        char c = expression[i];
        if (isdigit(c)) {
            int num = 0;
            while (isdigit(c)) {
                num = num * 10 + (c - '0');
                c = expression[++i];
            }
            i--;
            values.push(num);
        } else if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(calculate(val1, val2, op));

            }
            ops.pop();
        } else if (isOperator(c)) {
            while (!ops.empty() && ops.top() != '(' &&
                   (c == '*' || c == '/') && (ops.top() == '*' || ops.top() == '/')) {
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

    while (!ops.empty()) {
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


vector<string> split(string line, const char* token = " ")
{
  vector<string> finnal = {};
  string word;

  for (char c : line)
  {

    if (c != *token)
    {
      word = word+c;
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

int get_lt(vector<string> program_lines, string label)
{
  int lt = 0;
  for (auto line : program_lines)
  {
    //cout << line << endl;
    vector<string> code = split(line, " ");

    if (code[0] == label + ":")
    {
      return lt;
    }
    lt++;
  }
}

string minus_the_end(string str)
{
  string new_str = "";
  for (int i =0; i<str.length()-1; i++)
  {
    new_str+=str[i];
  }
  return new_str;
}

string process_string(const vector<string>& parts)
{
    stringstream ss;
    for (size_t i = 1; i < parts.size(); ++i)
    {
        ss << parts[i] << ' ';
    }

    string result;
    getline(ss, result, '\0'); // Read until end-of-string
    return result.substr(1, result.length() - 2);
}


string remove(const string str, const char* unwanted = "'")
{
  string newstr;
  for (int i= 0; i<str.size(); i++)
  {
    if (str[i] != *unwanted)
    {
      newstr+=str[i];
    }
  }
  return newstr;
}

bool is_valid_str(string str)
{
  int num=0;
  for (char c : str)
  {
    if (c == *"'")
    {
      num++;
    }
  }
  return num==2;
}

bool is_a_int(string str)
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

int main(int argc, char* argv[])
{


  ifstream program_file(argv[1]);

  if (!program_file.is_open())
  {
    throw runtime_error("Impossible d'ouvrire le fichier.");
  }


  string line;
  vector<string> program = {};

  while (getline(program_file, line))
  {
      program.push_back(line);
  }
  program_file.close();

  map<string, int> Ivariables;
  map<string, string> Svariables;
  string string_literal;
  int number;
  int pc = 0;
  string opcode;
  vector<string> tokens = {};
  auto start = high_resolution_clock::now();
  while (program[pc] != "stop")
  {

    opcode = program[pc];
    tokens =  split(opcode);
    if (opcode[opcode.size()-1] == *":")
    {
      while (program[pc] != "stop")
      {
        pc++;
      }
      pc++;
    }
    else if (tokens[0] == "int")
    {
      if (tokens[2] == "=")
      {
        if (Ivariables.count(tokens[3])>0)
        {
          Ivariables[tokens[1]] = Ivariables[tokens[3]];
        }
        else if (is_a_int(tokens[3]))
        {
          Ivariables[tokens[1]] = stoi(tokens[3]);
        }
        else
        {
          throw runtime_error(tokens[2] + " n'est pas valide pour une variable de type 'int'.");
        }
      }
    }

    else if (tokens[0] == "str")
    {
      if (tokens[2] == "=")
      {
        if (Svariables.count(tokens[3])>0)
        {
          Svariables[tokens[1]] = Svariables[tokens[3]];
        }
        else
        {
          if (is_valid_str(process_string(tokens)))
          {
          Svariables[tokens[1]] = process_string(tokens);
          }
          else
          {
            throw runtime_error(tokens[3] + " n'est pas valide pour une variable de type 'str'.");
          }
        }
      }
    }
    else if (Ivariables.count(tokens[0])>0)
    {
      //cout << tokens[2] << endl;
      if (tokens[1] == "=")
      {
        string expression = "";
        for (int i = 2; i<tokens.size(); i++)
        {
          if (Ivariables.count(tokens[i]))
          {
            expression += to_string(Ivariables[tokens[i]]);
          }
          else
          {
            expression += tokens[i];
          }

        }
        int result = evaluate(expression);
        Ivariables[tokens[0]] = result;
      }
    }

    else if (Svariables.count(tokens[0])>0)
    {
      if (tokens[1] == "u")
      {
        if (is_valid_str(tokens[2]))
        {
          Svariables[tokens[0]] = tokens[0];
        }
        else if (Svariables.count(tokens[2]))
        {
          Svariables[tokens[0]] = Svariables[tokens[2]];
        }
      }
    }


    else if (tokens[0] == "afficher")
    {
      string str_parts = "";
      for (int i = 1; i < tokens.size(); i++)
      {
        str_parts+=tokens[i] + " ";
      }
      if (Svariables.count(tokens[1])>0) // si la variable est str
      {
        string_literal = Svariables[tokens[1]];
      }
      else if (Ivariables.count(tokens[1])>0)// sinon si la variable est int
      {
        string_literal = to_string(Ivariables[tokens[1]]);
      }
      else
      {
        string_literal = remove(str_parts, "'");
      }
      cout << string_literal << endl;
    }

    else if (tokens[0] == "lire")
    {
      if (tokens[1] == "int")
      {
        int number;
        cin >> number;
        Ivariables[tokens[2]];
        Ivariables[tokens[2]] = number;
      }
      else if (tokens[1] == "str")
      {
        string word;
        cin >> word;
        Svariables[tokens[2]] = word;
      }
      else
      {
        throw runtime_error(tokens[1] +" n'est pas un type connu.");
      }
    }

    else if (tokens[0] == "si")
    {
      vector<string> current_comparaison = tokens;
      if (Ivariables.count(current_comparaison[1]))
      {
        if (current_comparaison[2] == "=")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (Ivariables[current_comparaison[1]] == Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (Ivariables[current_comparaison[1]] == stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == ">")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (Ivariables[current_comparaison[1]] > Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (Ivariables[current_comparaison[1]] > stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == "<")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (Ivariables[current_comparaison[1]] < Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (Ivariables[current_comparaison[1]] < stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == ">=")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (Ivariables[current_comparaison[1]] >= Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (Ivariables[current_comparaison[1]] >= stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == "<=")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (Ivariables[current_comparaison[1]] <= Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (Ivariables[current_comparaison[1]] <= stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
      }
      else
      {
        if (current_comparaison[2] == "=")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (stoi(current_comparaison[1]) == Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (stoi(current_comparaison[1]) == stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == ">")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (stoi(current_comparaison[1]) > Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (stoi(current_comparaison[1]) > stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == "<")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (stoi(current_comparaison[1]) < Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (stoi(current_comparaison[1]) < stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == ">=")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (stoi(current_comparaison[1]) >= Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (stoi(current_comparaison[1]) >= stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
        else if (current_comparaison[2] == "<=")
        {
          if (Ivariables.count(current_comparaison[3]))
          {
            if (stoi(current_comparaison[1]) <= Ivariables[current_comparaison[3]])
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
          else
          {
            if (stoi(current_comparaison[1]) <= stoi(current_comparaison[3]))
            {
              pc = get_lt(program, current_comparaison[4]);
            }
          }
        }
      }
    }

    pc++;
    //cout << pc << "/" << program.size()<< endl;
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\n";
  cout << "Programe executer en " << duration.count()/1000000 << " secondes"<< endl;
  return 0;
}
