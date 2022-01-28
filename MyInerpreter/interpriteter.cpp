#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


struct var_name
{
	std::string name;
	char type; 
	unsigned short index; 
	bool initialized; 
};

std::vector <std::string> s_v; //string_value
std::vector <long> l_v; //long_value
std::vector <double> d_v; //double_value
std::vector <bool> b_v; //bool_value
std::vector <var_name> v_n; //variable_name
std::vector <std::string> code;
std::vector <std::string> tokens;
std::vector <std::string> cycle;
std::string token;
std::string code_item;
std::string save;

int indexx = 0;

void creative(std::vector <std::string>& tokens);
void operation(std::vector <std::string>& tokens);
void unboxing(std::vector <std::string>& tokens);
void initialize(std::vector <std::string>& tokens);
void printation(std::vector <std::string>& tokens);
void condition(std::vector <std::string>& tokens);
void who_are_u(std::string& code_item);
void memory();





int main()
{
	std::string path = "txt.txt";
	std::ifstream fin;
	fin.open(path);
	if (fin.is_open()) {
		while (!fin.eof()) {
			std::string line;
			getline(fin, line);
			std::string tmp;
			for (int i = 0; i <= line.length(); i++) {

				if (line[i] != '\0') {
					tmp += line[i];
				}
				else {
					code.push_back(tmp);
					tmp = "";
				}
			}
		}
	}
	else {
		std::cout << "ERROR: file not found " << std::endl;
	}
	for (int i = 0; i < code.size(); i++)
	{
		std::string out = "";
		bool tmp = 0;
		for (int j = 0; j < code[i].size(); j++)
		{
			if (code[i][j] != ' ' && code[i][j] != '	') tmp = 1;
			if (tmp) out += code[i][j];
		}
		code[i] = out;
	}
	for (int i = 0; i < code.size(); i++) std::cout << code[i] << std::endl; //***

	std::cout << "************" << std::endl;

	for (; indexx < code.size(); indexx++)
	{
		who_are_u(code[indexx]);
	}


}
void creative(std::vector <std::string>& tokens)
{

	for (int i = 0, turn = 0; i < tokens.size(); i++, turn++)
	{
		var_name var;
		var.type = tokens[0][0];
		i++;
		if (turn > 0)
			var.name = tokens[i - 1];
		else
			var.name = tokens[i];
		i++;

		if (tokens[i] == "=") {
			i++;
		}
		else if (tokens[i] == "&" || tokens[i] == ":") {
			var.initialized = 0;
			v_n.push_back(var);
			continue;
		}
		var.initialized = 1;
		if (tokens[0] == "qol") {
			long tmp = std::stol(tokens[i]);
			var.index = l_v.size();
			l_v.push_back(tmp);
		}
		else if (tokens[0] == "str") {
			std::string tmp = tokens[i];
			var.index = s_v.size();
			s_v.push_back(tmp);
		}
		else if (tokens[0] == "ket") {
			double tmp = std::stod(tokens[i]);
			var.index = d_v.size();
			d_v.push_back(tmp);
		}
		else if (tokens[0] == "log") {
			bool tmp;
			if (tokens[i] == "true") tmp = 1;
			else if (tokens[i] == "false") tmp = 0;
			var.index = b_v.size();
			b_v.push_back(tmp);
		}
		i++;
		v_n.push_back(var);
	}
}
void operation(std::vector <std::string>& tokens)
{
	for (int tmp = 0; tmp < tokens.size(); tmp++)
	{
		if (tokens[tmp] == "mul" || tokens[tmp] == "div")
		{
			char brand = tokens[tmp][0];
			double arr[3];
			arr[0] = std::stod(tokens[tmp - 1]);
			arr[1] = std::stod(tokens[tmp + 1]);
			tokens.erase(tokens.begin() + (tmp - 1));
			tokens.erase(tokens.begin() + (tmp));
			if (brand == 'm') arr[2] = arr[0] * arr[1];
			else arr[2] = arr[0] / arr[1];
			tmp--;
			tokens[tmp] = std::to_string(arr[2]);
		}
	}
	for (int tmp = 0; tmp < tokens.size(); tmp++)
	{
		if (tokens[tmp] == "plus" || tokens[tmp] == "minus")
		{
			char brand = tokens[tmp][0];
			double arr[3];
			arr[0] = std::stod(tokens[tmp - 1]);
			arr[1] = std::stod(tokens[tmp + 1]);
			tokens.erase(tokens.begin() + (tmp - 1));
			tokens.erase(tokens.begin() + (tmp));
			if (brand == 'p') arr[2] = arr[0] + arr[1];
			else arr[2] = arr[0] - arr[1];
			tmp--;
			tokens[tmp] = std::to_string(arr[2]);
		}
	}
}

void unboxing(std::vector <std::string>& tokens)
{
	for(int j = 1; j < tokens.size(); j++)
	{
		for (int i = 0; i < v_n.size(); i++)
		{
			if (tokens[j] == v_n[i].name)
			{
				if (v_n[i].type == 'q')
				{
					tokens[j] = std::to_string(l_v[v_n[i].index]);
				}
				else if (v_n[i].type == 'l')
				{
					tokens[j] = b_v[v_n[i].index];
				}
				else if (v_n[i].type == 'k')
				{
					tokens[j] = std::to_string(d_v[v_n[i].index]);
				}
				else if (v_n[i].type == 's')
				{
					tokens[j] = s_v[v_n[i].index];
				}
			}
		}
	}
}

void initialize(std::vector <std::string>& tokens)
{
	int j ;
	for (int i = 0; i < v_n.size(); i++) if (v_n[i].name == tokens[0]) j = i;
	if (v_n[j].initialized == 0)
	{
		if (v_n[j].type == 'q')
		{
			v_n[j].index = l_v.size();
			long tmp = std::stol(tokens[2]);
			l_v.push_back(tmp);
		}
		else if (v_n[j].type == 'l')
		{
			v_n[j].index = b_v.size();
			bool tmp;
			if (tokens[2] == "true") tmp = 1;
			else if (tokens[2] == "false") tmp = 0;
			b_v.push_back(tmp);
		}
		else if (v_n[j].type == 'k')
		{
			v_n[j].index = d_v.size();
			double tmp = std::stod(tokens[2]);
			d_v.push_back(tmp);
		}
		else if (v_n[j].type == 's')
		{
			v_n[j].index = s_v.size();
			std::string tmp = tokens[2];
			s_v.push_back(tmp);
		}
		v_n[j].initialized = 1;
	}
	else
	{
		if (v_n[j].type == 'q')
		{
			l_v[v_n[j].index] = std::stol(tokens[2]);
		}
		else if (v_n[j].type == 'l')
		{
			if (tokens[2] == "true") b_v[v_n[j].index] = 1;
			else if (tokens[2] == "false") b_v[v_n[j].index] = 0;
		}
		else if (v_n[j].type == 'k')
		{
			d_v[v_n[j].index] = std::stod(tokens[2]);
		}
		else if (v_n[j].type == 's')
		{
			s_v[v_n[j].index] = tokens[2];
		}

	}
}

void memory()
{
	for (int i = 0; i < v_n.size(); i++)
	{
		std::cout << "Name_" << v_n[i].name << " Type_" << v_n[i].type << " Initalized_" << v_n[i].initialized;
		if (v_n[i].initialized == 1)
		{
			std::cout << " Value_"; 
			if (v_n[i].type == 'q') std::cout << l_v[v_n[i].index] << std::endl;
			else if (v_n[i].type == 'l') std::cout << b_v[v_n[i].index] << std::endl;
			else if (v_n[i].type == 'k') std::cout << d_v[v_n[i].index] << std::endl;
			else if (v_n[i].type == 's') std::cout << s_v[v_n[i].index] << std::endl;
		}
		else std::cout << std::endl;
	}
}



void printation(std::vector <std::string>& tokens)
{
	int i = 0;
	if (tokens[i] == "fout") i++; 
	if (tokens[i] == ":u") unboxing(tokens);
	else if (tokens[i] == ":m") operation(tokens);
	else if (tokens[i] == ":u:m" || tokens[i] == ":m:u") { unboxing(tokens); operation(tokens); }
	else
	{
		i++;
		for (; i < tokens.size() - 1; i++) std::cout << tokens[i] << " ";
	}
	i+=2;
	for (; i < tokens.size() - 1; i++)std::cout << tokens[i] << " ";
	std::cout << std::endl;
}

void condition(std::vector <std::string>& tokens)
{
	for (int tmp = 0; tmp < tokens.size(); tmp++)
	{
		if (tokens[tmp] == "same" || tokens[tmp] == "diff")
		{
			char brand = tokens[tmp][0];
			std::string arr[3];
			arr[0] = tokens[tmp - 1];
			arr[1] = tokens[tmp + 1];
			tokens.erase(tokens.begin() + (tmp - 1));
			tokens.erase(tokens.begin() + (tmp));
			if (brand == 's')
			{
				if (arr[0] == arr[1]) arr[2] = "1"; else arr[2] = "0";
			}
			else
			{
				if (arr[0] != arr[1]) arr[2] = "1"; else arr[2] = "0";
			}
			tmp--;
			tokens[tmp] = arr[2];
		}
	}
	for (int tmp = 0; tmp < tokens.size(); tmp++)
	{
		if (tokens[tmp] == "CSS" || tokens[tmp] == "mech" || tokens[tmp] == "poq" || tokens[tmp] == "poqh" || tokens[tmp] == "has" || tokens[tmp] == "nos")
		{
			std::string brand = tokens[tmp];
			double arr[3];
			arr[0] = std::stod(tokens[tmp - 1]);
			arr[1] = std::stod(tokens[tmp + 1]);
			tokens.erase(tokens.begin() + (tmp - 1));
			tokens.erase(tokens.begin() + (tmp));
			if (brand == "CSS") arr[2] = arr[0] > arr[1];
			else if (brand == "mech") arr[2] = arr[0] >= arr[1];
			else if (brand == "poq") arr[2] = arr[0] < arr[1];
			else if (brand == "poqh") arr[2] = arr[0] <= arr[1];
			else if (brand == "has") arr[2] = arr[0] == arr[1];
			else if (brand == "nos") arr[2] = arr[0] != arr[1];
			tmp--;
			tokens[tmp] = std::to_string(arr[2]);
		}
	}
	for (int tmp = 0; tmp < tokens.size(); tmp++)
	{
		if (tokens[tmp] == "and" || tokens[tmp] == "or")
		{
			char brand = tokens[tmp][0];
			double arr[3];
			arr[0] = std::stod(tokens[tmp - 1]);
			arr[1] = std::stod(tokens[tmp + 1]);
			tokens.erase(tokens.begin() + (tmp - 1));
			tokens.erase(tokens.begin() + (tmp));
			if (brand == 'a') arr[2] = arr[0] && arr[1];
			else arr[2] = arr[0] || arr[1];
			tmp--;
			tokens[tmp] = std::to_string(arr[2]);
		}
	}

}
void who_are_u(std::string& code_item)
{
	for (int i = 0; i <= code_item.length(); i++)
	{
		if (code_item[i] != ' ' && code_item[i] != '\0') token += code_item[i];
		else { tokens.push_back(token);	token = ""; }
	}
	if (tokens[0] == "qol" || tokens[0] == "ket" || tokens[0] == "log" || tokens[0] == "str")
	{
		unboxing(tokens);
		operation(tokens);
		creative(tokens);
	}
	else if (tokens[0] == "fout")
	{
		printation(tokens);
	}
	else if (tokens[0] == "fourni")
	{
		int begin = indexx, finish = indexx+1, count = 0;
		bool tmp = 1;
		for (; tmp ; finish++)
		{
			if (code[finish] == "commencer") count++;
			else if (code[finish] == "cesser") count--;
			if (count == 0) tmp = 0;
		}
		finish--;
		indexx++;
		unboxing(tokens);
		operation(tokens);
		condition(tokens);
		if ( std::stoi(tokens[2]) == 1)
		{
			for (; indexx < finish; indexx++)
			{
				tokens.clear();
				code_item = "";
				who_are_u(code[indexx]);
			}
		}
		indexx = finish;

	}
	else if (tokens[0] == "fra")
	{
		int begin = indexx, finish = indexx + 1, count = 0;
		bool tmp = 1;
		for (; tmp; finish++)
		{
			if (code[finish] == "commencer") count++;
			else if (code[finish] == "cesser") count--;
			if (count == 0) tmp = 0;
		}
		finish--;
		for (; begin <= finish; begin++) cycle.push_back(code[begin]);
		begin = indexx;
		tmp = 0;
		unboxing(tokens);
		operation(tokens);
		condition(tokens);
		if (std::stoi(tokens[2]) == 1) tmp = 1;
		while (tmp)
		{
			for (int j = indexx; j < finish; j++)
			{
				tokens.clear();
				code_item = "";
				who_are_u(code[j]);
			}

			tokens.clear();
			code_item = "";
			for (int i = begin, j = 0; i < finish; i++, j++)
			{
				code[i] = cycle[j];
			}
			code_item = code[indexx];
			for (int i = 0; i <= code_item.length(); i++)
			{
				if (code_item[i] != ' ' && code_item[i] != '\0') token += code_item[i];
				else { tokens.push_back(token);	token = ""; }
			}
			unboxing(tokens);
			operation(tokens);
			condition(tokens);
			if (std::stoi(tokens[2]) == 1) tmp = 1;
			else tmp = 0;
		}
		indexx = finish;
	}
	else if (tokens[0] == "memory<>")
	{
		memory();
	}
	else
	{
		bool tmp = 0;
		for (int i = 0; i < v_n.size(); i++) if (tokens[0] == v_n[i].name) tmp = 1;
		if (tmp == 1)
		{
			unboxing(tokens);
			operation(tokens);
			initialize(tokens);
		}
	}

	tokens.clear();
	code_item = "";
}

