#include "basicFunc.h"
#include <cmath>
#include <ctime>
#include<algorithm>

vector<string> del_white(vector<string> tokens) {
  vector<string> result = {};
  for (const string& token : tokens) {
    if (!token.empty()) {
      result.push_back(token);
      //cout << token << "#" << endl;
    }
  }
  return result;
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
  map<string, int> fonctions;
  string string_literal;
  int number;
  int pc = 0;
  string opcode;
  vector<string> tokens = {};
  auto start = high_resolution_clock::now();
  vector<int> old_pc = {};
  while (split(program[pc])[split(program[pc]).size()-1] != "stop")
  {
	
    opcode = program[pc];
    //cout << opcode << endl;
    tokens =  del_white(split(opcode));
    while (tokens.empty())
    {
      pc++;
      opcode = program[pc];
      tokens =  del_white(split(opcode));
    }
   
    //cout << tokens[0] << " " << tokens[tokens.size()-1].find(":") << endl;

    //cout << opcode << " " << pc << endl;
    //cout << tokens[tokens.size()-1] << endl;
    if (fonctions.count(tokens[tokens.size()-1])>0)
    {
      //cout << pc << " c" << endl;
      old_pc.push_back(pc);
      pc = fonctions[tokens[tokens.size()-1]];
      
    } 

    else if (opcode == "finfonc")
    {
      //cout << pc << " f0" << endl;
      pc = old_pc[old_pc.size()-1];
      //cout << pc << " f1" << endl;
      old_pc.pop_back();
    //cout << pc << " f2" << endl;
    }
  
    else if (tokens[0] == "fonction")
    {
      fonctions[split(tokens[1], ":")[0]] = pc+1;
      //cout << split(tokens[1], ":")[0] + " " << pc+1 << endl;
      while ((program[pc].find("finfonc") != 1))
      {
      
      pc++;
      if (pc > program.size())
      {
        throw runtime_error("Erreur ligne " + to_string(fonctions[split(tokens[1], ":")[0]]) + " la fonciton " + split(tokens[1], ":")[0] + " doit être fermé par 'finfonc'");
      }
      if (program[pc].find("finfonc") < 934287)
      {
        break;
      }
    }
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
	else if (tokens[3] == "haz!")
	{
		auto a1 = high_resolution_clock::now();
		int a = duration_cast<nanoseconds>(a1.time_since_epoch()).count();
		auto b1 = high_resolution_clock::now();
		int b = duration_cast<nanoseconds>(a1.time_since_epoch()).count();
		auto c1 = high_resolution_clock::now();
		int c = duration_cast<nanoseconds>(a1.time_since_epoch()).count();
		Ivariables[tokens[1]] = round(a*b/(c/10));
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


    else if (opcode.find("afficher") < 10000000)
    {
      string str_parts = "";
      string string_literal = "";
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
	vector<string> token_string = {};
	string current_string_token = "";
	for (int i =0; i<split(remove(str_parts, "'")).size(); i++)
	{
		current_string_token = split(remove(str_parts, "'"))[i];

		if (current_string_token[0] == *"$")
		{
			string possible_var_name = "";
			for (int n = 1; n<current_string_token.size(); n++)
			{
				possible_var_name+=current_string_token[n];
			}

			if (Ivariables.count(possible_var_name)>0)
			{
				string_literal += to_string(Ivariables[possible_var_name]) + " ";
			}
			else if (Svariables.count(possible_var_name)>0)
			{
				string_literal += Svariables[possible_var_name] + " ";
			}
			else 
			{
				throw runtime_error(possible_var_name + " n'est pas une variable connue.");
			}
		}
		else
		{
		  string_literal += current_string_token + " ";
		}
	}		
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

    else if (opcode.find("si") < 139485708947 && tokens.size() > 1 && opcode.find("finsi") > 1343254245)
    {
      // Extract the condition expression
      string condition = "";
      int starting_index = 0;
      for (int i = 0; i < tokens.size(); i++)
      {
        if (tokens[i] == "si")
        {
          starting_index = i + 1;
          break;
        }
      }
      for (int i = starting_index; i < tokens.size(); i++)
      {
        condition += tokens[i] + " ";
      }
      
      // Evaluate the condition expression
      bool result = evaluate_condition(condition, Ivariables, Svariables);

      // Execute the block if the condition is true
      if (!result)
      {
        while (program[pc].find("finsi") > 109483)
        {
          pc++;
        }
      }
    }


    pc++;
    //cout << pc << "/" << program.size()<< endl;
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\n";
  cout << "Programe executer en " << duration.count()/1000 << " milisecondes"<< endl;
  return 0;
}
