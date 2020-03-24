#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

int COM_NN_D(int n1, int* Num1)
{
	int n2;
	string Number2;
	size_t i = 0;

	cout << "enter number of simbols" << endl;
	cin >> n2;
	if (n2 <= 0)
	{
		cout << "Error1" << endl;
		return 3;
	}
	cin >> Number2;
	if (n1 > 1 && Number2[0] == 0)
	{
		cout << "Error" << endl;
		return  4;
	}
	if (Number2.length() < n2 || Number2.length() > n2)
	{
		cout << "Error" << endl;
		return 5;
	}
	for (i = 0; i < Number2.length(); i++)
	{
		if (Number2[i] < 48 || Number2[i] > 57)
		{
			cout << "Error" << endl;
			return 6;
		}
	}

	int* Num2 = new int[n2];
	for (i = 0; i < n2; i++)
	{
		Num2[i] = (int)(Number2[i] - '0');
		if (n2 > 1 && Num2[0] == 0)
		{
			cout << "Error" << endl;
			return  7;
		}
	}

	if (n1 > n2)
	{
		cout << "First numbor bolshe" << endl;
		return 2;
	}
	else if (n2 > n1)
	{
		cout << "Second is bolshe" << endl;
		return 0;
	}
	else
	{
		for (i = 0; i < n1; i++)
		{
			if (Num1[i] > Num2[i])
			{
				cout << "First numbor bolshe" << endl;
				return 2;
			}
			else if (Num1[i] > Num2[i])
			{
				cout << "Second is bolshe" << endl;
				return 0;
			}
		}
		return 1;
	}
}

bool NZER_N_B(int n1, int* Num1)
{
	if (n1 == 1 && Num1[0] == 0)
	{
		cout << "Chislo ravno nulyu" << endl;
		return FALSE;
	}
	else {
		cout << "Chislo ne nol" << endl;
		return TRUE;
	}
}

void ADD_1N_N(int* N1, int* Num1)
{
	int n2;
	size_t i;

	Num1[*N1 - 1] ++;
	for (i = (*N1 - 1); i > 0; i--)
	{
		if (Num1[i] >= 10)
		{
			Num1[i - 1] += (Num1[i] / 10);
			Num1[i] = (Num1[i] % 10);
		}
	}
	if (Num1[0] >= 10)
	{
		int* Num2 = new int[*N1 + 1];
		Num2[0] = (Num1[0] / 10);
		cout << Num2[0] << " ";
		Num1[0] = Num1[0] % 10;
		for (i = 0; i < *N1; i++)
		{
			Num2[i + 1] = Num1[i];
			cout << Num2[i + 1] << " ";


		}
		delete[] Num1;
		Num1 = new int[*N1 + 1];
		for (i = 0; i < (*N1 + 1); i++)
		{
			Num1[i] = Num2[i];
		}
		*N1 = *N1 + 1;
		cout << Num1[0];
	}

}

int main()
{
	int n1, Function;
	size_t i = 0;
	string Number1;

	cout << "enter number of simbols" << endl;
	cin >> n1;
	if (n1 <= 0)
	{
		cout << "Error1" << endl;
		return 1;
	}
	cin >> Number1;
	if (Number1.length() < n1 || Number1.length() > n1)
	{
		cout << "Error" << endl;
		return 3;
	}
	for (i = 0; i < Number1.length(); i++)
	{
		if (Number1[i] < 48 || Number1[i] > 57)
		{
			cout << "Error" << endl;
			return 4;
		}
	}

	int* Num1 = new int[n1];
	for (i = 0; i < n1; i++)
	{
		Num1[i] = (int)(Number1[i] - '0');
		if (n1 > 1 && Num1[0] == 0)
		{
			cout << "Error" << endl;
			return  2;
		}
	}

	cout << "enter function that you want" << endl;
	cin >> Function;
	switch (Function)
	{
	case 1: {COM_NN_D(n1, Num1); break; }
	case 2: {NZER_N_B(n1, Num1); break; }
	case 3: {ADD_1N_N(&n1, Num1); break; }

	}
	cout << Num1[0] << endl << Num1[1] << endl << n1;
}