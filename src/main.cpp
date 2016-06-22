#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "btree/btree.h"

using namespace std;

bool isFloat(string myString) 
{
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f;
	return iss.eof() && !iss.fail();
}

int main()
{
	btree<float>* tree = new btree<float>(NULL);
	
	string user_input;

	while (user_input != "close")
	{
		bool isValidInput = false;

		cout <<"awaiting your command..."<<endl;

		getline(cin, user_input);

		// TODO: change command parsing logic

		// adding
		if (isFloat(user_input))
		{
			tree->pushValue(stof(user_input));
			isValidInput = true;
		}

		// simple commands
		else if (user_input == "print")
		{
			tree->print();
			isValidInput = true;
		}
		else
		{
			// commands with args

			int index = 0;
			
			index = user_input.find(" ");

			if (index > 0)
			{
				string strArg = user_input.substr(index);
				const char * ch = strArg.c_str();
				int arg = atof(ch);
				string cmd = user_input.substr(0, index);

				if (cmd == "remove")
				{
					tree->removeValue(arg);
					isValidInput = true;
				}
			}

		}

		if (!isValidInput)
		{
			cout << "unknown command" << endl;
		}
		else
		{
			cout << "affirmative" << endl;
		}

	}

	delete tree;
}