
#include<string>
#include <iostream>
#include<cctype>
using namespace std;
bool vars_detect[101] = { false };

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

string var_detection(string str, int n, string print_vars=" ")
{
	
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

void nums_vars(int n) {
	int counter=0;
	for (int i = 1; i <= n; i++)
	{
		if (vars_detect[i])
		{
			counter++;
			
		}
	}
	cout << counter << endl;
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

void print_answer(double matrex[100][101], int n) {
	cout << "<-------solution----------->" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << "=" << matrex[i][n] << endl;
	}
}

void print_whole_matrix(double matrix[100][101], int n)
{
	cout << "\n----- Matrix (Augmented) -----\n";

	for (int i = 0; i < n; i++) // rows
	{
		for (int j = 0; j < n; j++) // columns
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "-------------------------------\n";
}

void equation_i_operation(double matrex[100][101], int n, int o)
{
	for (int j = 0; j <= n; j++) // columns
	{
		if (j < n) {
			if (matrex[o - 1][j] > 0) {
				cout<<"+" << matrex[o - 1][j] << "x" << j + 1;
			}
			else {
				cout  << matrex[o - 1][j] << "x" << j + 1;
			}	
		}
		else {
			cout << "=" << matrex[o - 1][n] << endl;
		}	
	}
	cout << endl;
}


void column_operation(double matrex[100][101], int n, int o)
{
	for (int i = 0; i < n; i++) // rows
	{
			cout << matrex[i][o-1] << endl;	
	}
}

void add_operation(double matrex[100][101], int n, int eq1 ,int eq2) {
	for (int i = 0; i <= n; i++)
	{
		if (i < n) {
			if(matrex[eq1 - 1][i] + matrex[eq2 - 1][i]>0){ cout << "+" << matrex[eq1 - 1][i] + matrex[eq2 - 1][i] << "x" << i + 1; }
			else{ cout << matrex[eq1 - 1][i] + matrex[eq2 - 1][i] << "x" << i + 1; }
			
		}
		else { cout<<"=" << matrex[eq1-1][n] + matrex[eq2-1][n] << endl; }
		
	}
	
}


void subtract_operation(double matrex[100][101], int n, int eq1, int eq2) {
	for (int i = 0; i <= n; i++)
	{
		if (i < n) {
			if (matrex[eq1 - 1][i] - matrex[eq2 - 1][i] > 0) { cout << "+" << matrex[eq1 - 1][i] - matrex[eq2 - 1][i] << "x" << i + 1; }
			else { cout << matrex[eq1 - 1][i] - matrex[eq2 - 1][i] << "x" << i + 1; }

		}
		else { cout << "=" << matrex[eq1 - 1][n] - matrex[eq2 - 1][n] << endl; }

	}

}
void Dx_operation(double mat[100][101], int n, int col)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == col - 1)
				cout << mat[i][n] << "\t";
			else
				cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
}


double determinant(double mat[100][101], int n)
{
	double temp[100][100];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = mat[i][j];

	double det = 1;

	for (int i = 0; i < n; i++)
	{
		if (temp[i][i] == 0)
		{
			for (int k = i + 1; k < n; k++)
			{
				if (temp[k][i] != 0)
				{
					for (int j = 0; j < n; j++)
						swap(temp[i][j], temp[k][j]);

					det *= -1;
					break;
				}
			}
		}

		det *= temp[i][i];

		for (int k = i + 1; k < n; k++)
		{
			double factor = temp[k][i] / temp[i][i];

			for (int j = i; j < n; j++)
				temp[k][j] -= factor * temp[i][j];
		}
	}

	return det;
}

void D_value_operation(double mat[100][101], int n)
{
	double d = determinant(mat, n);
	cout << d << endl;
}

void substitute_operation(double matrex[100][101], int n, int var, int eq1, int eq2)
{
	double a = matrex[eq1 - 1][var - 1];
	double b = matrex[eq2 - 1][var - 1];

	if (b == 0)
	{
		cout << "Cannot substitute because coefficient is zero" << endl;
		return;
	}

	double factor = a / b;

	double result[101];

	for (int i = 0; i <= n; i++)
	{
		result[i] = matrex[eq1 - 1][i] - factor * matrex[eq2 - 1][i];
	}

	for (int i = 0; i <= n; i++)
	{
		if (i < n)
		{
			if (result[i] > 0)
				cout << "+" << result[i] << "x" << i + 1;
			else
				cout << result[i] << "x" << i + 1;
		}
		else
		{
			cout << "=" << result[i];
		}
	}

	cout << endl;
}



int main()
{
	int n;
	string command;
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
	
	
	while (true)
	{
		cin >> command;
		if (command == "num_vars")
		{
			nums_vars(n);
		}
		else if (command == "equation")
		{
			int o = 0;
			cin >> o;
			equation_i_operation(matrex, n, o);
		}
		else if (command == "column")
		{
			string str = "";
			string num = "";
			cin >> str;
			for (int i = 1; i < str.length(); ++i) {
				if (isdigit(str[i])) {
					num += str[i];
				}
				else {
					break;
				}
			}
			int o = stoi(num);
			column_operation(matrex, n, o);
		}
		else if (command == "display")
		{
			print_whole_matrix(matrex, n);
		}
		else if (command == "Dx")
		{
			int col;
			cin >> col;
			Dx_operation(matrex, n, col);
		}
		else if (command == "D_value")
		{
			D_value_operation(matrex, n);
		}
		else if (command == "add")
		{
			int eq1, eq2;
			cin >> eq1;
			cin >> eq2;
			add_operation(matrex, n, eq1, eq2);

		}
		else if (command == "subtract")
		{
			int eq1, eq2;
			cin >> eq1;
			cin >> eq2;
			subtract_operation(matrex, n, eq1, eq2);

		}
		else if (command == "substitute")
		{
			string var;
			int eq1, eq2;

			cin >> var >> eq1 >> eq2;

			string num = "";
			for (int i = 1; i < var.length(); i++)
				num += var[i];

			int var_index = stoi(num);

			substitute_operation(matrex, n, var_index, eq1, eq2);
		}
		else if (command == "solve")
		{
			gaussian(matrex, n);
			print_answer(matrex, n);
		}
		
		else if (command == "end") {
			break;
		}
	}
	

}