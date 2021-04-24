#include<iostream>
#include<cmath>
#include <vector>
using namespace std;
int N;
int arr[20]; // 식의 숫자가 들어갈 배열
int op[10];
vector<int>selected;
int result = 98765432;
int visited[21] = { 0, };
int min_answer = 98765432;
int max_answer = -98765432;
int team_start, team_link;

void Calc(int x, int y, int op)
{
	// cout << "x: " << x << " y: " << y << " op: " << op << endl;
	result = -1;
	if (op == 0)
	{
		result = x + y;
	}
	else if (op == 1)
	{
		result = x - y;
	}
	else if (op == 2)
	{
		result = x * y;
	}
	else if (op == 3)
	{
		result = x / y;
	}
}

void dfs(vector<int> selected) // num은 
{
	if (selected.size() == N-1) //합이 N-1인 연산자 개수
	{
		result = arr[0];
		for (int k = 0; k < selected.size(); k++)
		{
			Calc(result, arr[k + 1], selected[k]);
		}
		if (result < min_answer)
		{
			min_answer = result;
		}
		if (result > max_answer)
		{
			max_answer = result;
		}
		// cout << result << endl;

		return;
	}
	else
	{

		for (int i = 0; i < 4; i++) // 연산자 개수만큼 돌아
		{
			if (op[i] > 0)
			{
				op[i] -= 1;
				selected.push_back(i);
				dfs(selected);
				selected.pop_back();
				op[i] += 1;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> op[i];
	}

	dfs(selected);
	cout << max_answer << "\n" << min_answer;
	return 0;
}