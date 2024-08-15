#include "basicFunc.h"



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
  cout << "Programe executer en " << duration.count()/1000 << " milisecondes"<< endl;
  return 0;
}
