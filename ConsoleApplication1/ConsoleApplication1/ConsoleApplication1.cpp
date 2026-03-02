using namespace std;
#include<string>
#include <iostream>
#include<cctype>

using namespace std;

string remove_Space(string str) 
{
	string result = "";
	for (char c:str)
	{
		if (c != ' ') { result += c; }
	}
	return result;
}

string sign_detection(string str) {
	switch (str[0]) {
	case '+':
	case '-':return str;
	default:
		str ='+'+ str;
		return str;
	}
}

string var_detection(string str, int n)
{
	bool vars_detect[101] = { false };
	int varIDX = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == 'x') {
			string num = "";
			int j = i + 1;
			while (isdigit(str[j]) && j < str.length())
			{
				num += str[j];
				j++;
			}
			if (num != "")
			{
				varIDX = stoi(num);
				if (varIDX >0 && varIDX <= n)
				{
					vars_detect[varIDX] = true;
				}
				else
				{
					cout << "Index of variable is out of index" << endl;
					return "";
				}
			}
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		if(!vars_detect[i])
		{
			cout << "Missing Variable x" << i << endl;
			return "";
		}
	}
	return str;
}



string flip_sign(string str) {

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '+') { str[i] = '-'; }
		else if (str[i] == '-') { str[i] = '+'; }
	}
	return str;
}

string input_validate(string str) {
	for (char c : str) 
	{
		if (!isdigit(c) && c != 'x' && c != '+' && c != '-' && c != '=')
		{
			 str=" ";
		}
	}
	return str;
}

/**string right_side_handel(string r) {
	for (int i = 0; i < r.length(); i++) {
		if (r[i] == '+'|| r[i] == '-') 
		{
			//while()
		}
	}
}*/


void matrix(double matrix[100][101], int n)
{
	string eqn;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter Equation " << i + 1 << " : " << endl;
		getline(cin, eqn);
		eqn = input_validate(eqn);
		eqn = remove_Space(eqn);
		eqn = sign_detection(eqn);
		eqn = var_detection(eqn, n);
		
		if (eqn == "")
		{
			i--;
			continue;
		}

		int equalidx = eqn.find('=');
		string left = eqn.substr(0, equalidx);
		string right = eqn.substr(equalidx + 1);

		//setting rows and columns to zer0
		for (int j = 0; j <= n; j++)matrix[i][j] = 0;

		string nums = "";
		int sign = 1;

		for (int j = 0; j < left.length(); j++)
		{
			if (left[j] == '+') { sign = 1; }
			else if (left[j] == '-') { sign = -1; }
			else if (isdigit(left[j])) { nums += left[j]; }
			else if (left[j] == 'x')
			{
				//capture value after x in a placeholder
				string varnum = "";
				//capture index of the number after x
				int k = j + 1;
				//while to catch numbers of more than one didgit after x
				while (k < left.length() && isdigit(left[k]))
				{
					varnum += left[k];
					k++;
				}

				int idx = stoi(varnum) - 1;
				if (nums =="") { matrix[i][idx] += sign; }
				else { matrix[i][idx] += sign * stoi(nums); }
				nums = "";
				j = k - 1;
			}
		}

		matrix[i][n] = stoi(right);
	}

}

void gaussian(double mtx[100][101], int n) {
	for (int i = 0; i < n; i++) {
		double pivot = mtx[i][i];
		for (int j = 0; j <= n; j++) {
			mtx[i][j] /= pivot;
		}
		for (int j = 0; j < n; j++) {
			if (j != i) {
				double factor = mtx[j][i];
				for (int s = 0; s <= n; s++) {
					mtx[j][s] -= factor * mtx[i][s];
				}

			}

		}
	}
}


void print_whole_matrix(double matrix[100][101], int n)
{
	cout << "\n----- Matrix (Augmented) -----\n";

	for (int i = 0; i < n; i++) // rows
	{
		for (int j = 0; j <= n; j++) // columns
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "-------------------------------\n";
}


void print_answer(double matrex[100][101], int n) {
	cout << "<-------solution----------->"<<endl;
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << "=" << matrex[i][n] << endl;
	}
}


int main()
{
	int n;
	cout << "Enter number of equations 'max 100'" << endl;
	cin >> n;
	cin.ignore();
	if (n <= 0 || n > 100)
	{
		cout << "Invalid number" << endl;
		return 0;
	}
	double matrex[100][101];
	matrix(matrex, n);
	print_whole_matrix(matrex, n);
	gaussian(matrex, n);
	print_answer(matrex, n);
	
}