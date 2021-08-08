#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include "math.h"

using namespace std;

int score(char c1, char c2);
int **fillTalbe(vector<char> list1, vector<char> list2);
void printTalbe(int **table, vector<char> list1, vector<char> list2);
void backTracking(int **table, vector<char> list1, vector<char> list2);

int main()
{

	vector<char> list1{'G', 'T', 'G', 'C', 'A', 'A', 'T', 'C', 'G', 'C', 'T', 'G', 'G', 'C', 'G', 'G', 'C', 'G', 'T', 'A', 'G'};
	vector<char> list2{'A', 'G', 'C', 'A', 'T', 'A', 'A', 'T', 'A', 'C', 'C', 'C', 'C', 'T', 'A', 'T', 'A', 'C', 'T', 'G', 'T'};

	// vector<char> list1{'G', 'T', 'G', 'C', 'A'};
	// vector<char> list2{'A', 'G', 'C', 'A', 'T', 'A'};

	int **result = fillTalbe(list1, list2);
	printTalbe(result, list1, list2);
	backTracking(result, list1, list2);
}

int **fillTalbe(vector<char> list1, vector<char> list2)
{
	int m = list1.size();
	int n = list2.size();

	vector<int> temp;

	int **table;
	table = new int *[m + 1];

	for (int i = 0; i < m + 1; i++)
	{
		table[i] = new int[n + 1];
	}
	table[0][0] = 0;

	for (int i = 1; i < n + 1; i++)
	{
		table[i][0] = -20 * i;
	}

	for (int j = 1; j < m + 1; j++)
	{
		table[0][j] = -20 * j;
	}

	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			temp.push_back(table[j - 1][i - 1] + score(list1[i - 1], list2[j - 1]));
			temp.push_back(table[j - 1][i] - 20);
			temp.push_back(table[j][i - 1] - 20);

			int max = *max_element(begin(temp), end(temp));

			table[j][i] = max;
			temp.clear();
		}
	}

	return table;
}

int score(char c1, char c2)
{
	// P(a,a) = +1
	if (c1 == c2)
	{
		return 100;
	}
	// P(a,b) = -0.15
	// case for AT and CG
	else if ((c1 == 'A' && c2 == 'T') || (c1 == 'T' && c2 == 'A') || (c1 == 'C' && c2 == 'G') || (c1 == 'G' && c2 == 'C'))
	{
		return -15;
	}
	// P(a,b) = -0.1
	// case for not AT and CG
	else
	{
		return -10;
	}
}

void printTalbe(int **table, vector<char> list1, vector<char> list2)
{
	cout << "         ";
	for (int i = 0; i < list1.size(); i++)
	{
		cout << setw(6) << list1[i];
	}
	cout << endl;

	vector<char> temp;
	temp.push_back(' ');
	temp.insert(temp.end(), list2.begin(), list2.end());

	for (int i = 0; i < list2.size() + 1; i++)
	{
		cout << setw(5) << temp[i];
		for (int j = 0; j < list1.size() + 1; j++)
		{
			cout << setw(5) << setprecision(2) << (double)table[i][j] / 100 << " ";
		}
		cout << endl;
	}
}

void backTracking(int **table, vector<char> list1, vector<char> list2)
{

	int x = list1.size();
	int y = list2.size();
	int k = x - 1;
	int l = y - 1;

	vector<char> path_top;
	vector<char> path_bot;
	vector<int> scorePath;
	scorePath.push_back(table[x][y]);

	while (true)
	{
		if (x == 0 && y == 0)
		{
			break;
		}

		if (list1[l] == list2[k])
		{
			if (table[x][y] - 100 == table[x - 1][y - 1])
			{
				path_top.push_back(list1[l]);
				path_bot.push_back(list2[k]);

				//print out new value
				scorePath.push_back(table[x - 1][y - 1]);

				//update x and y
				x = x - 1;
				y = y - 1;

				k = x - 1;
				l = y - 1;
			}
		}

		else if (table[x][y] == table[x - 1][y] - 20)
		{
			path_top.push_back('-');
			//path_top.push_back(list1[l]);

			path_bot.push_back(list2[k]);

			//print out the next value
			scorePath.push_back(table[x - 1][y]);

			//update x to the new place
			x = x - 1;

			k = x - 1;
		}

		else if (table[x][y] == table[x][y - 1] - 20)
		{

			path_top.push_back(list1[l]);

			path_bot.push_back('-');
			//path_bot.push_back(list2[k]);
			scorePath.push_back(table[x][y - 1]);

			//update y to the new place
			y = y - 1;

			l = y - 1;
		}

		else if (table[x][y] + 10 == table[x - 1][y - 1] || table[x][y] + 15 == table[x - 1][y - 1])
		{
			path_top.push_back(list1[l]);
			path_bot.push_back(list2[k]);
			scorePath.push_back(table[x - 1][y - 1]);

			//update x and y
			x = x - 1;
			y = y - 1;

			k = x - 1;
			l = y - 1;
		}
	}

	reverse(path_top.begin(), path_top.end());
	reverse(path_bot.begin(), path_bot.end());


	cout << endl;
	cout << endl;
	cout << "Alignment: " << endl;
	for (char c : path_top)
	{
		cout << c << " ";
	}
	cout << endl;
	for (char c : path_bot)
	{
		cout << c << " ";
	}
	cout << endl;
	cout << endl;
	
	cout << "Score path: ";
	for(int score: scorePath){
		cout << setprecision(2) << (double)score/100 << " -> ";
	}
	cout << endl;
}