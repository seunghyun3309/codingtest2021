#include<iostream>
#include<cmath>
#include <vector>
using namespace std;
int N;
int arr[21][21];
int team_start, team_link;
vector<int>selected;
int result = 98765432;

int Calc(vector<int> selected, vector<int>unselected)
{
	team_start = 0, team_link = 0;
	for (int i = 0; i < selected.size(); i++)
	{
		for (int j = 0; j < selected.size(); j++)
		{
			if (selected[i] != selected[j])
			{
				team_start += arr[selected[i]][selected[j]];
			}
		}
	}
	for (int i = 0; i < unselected.size(); i++)
	{
		for (int j = 0; j < unselected.size(); j++)
		{
			if (unselected[i] != unselected[j])
			{
				team_link += arr[unselected[i]][unselected[j]];
			}
		}
	}
	return abs(team_start - team_link);
}

void dfs(int start, vector<int> selected) // num은 
{
	if (selected.size() == N / 2)
	{
		int idx = 0;
		vector<int>unselected;

		for (int i = 1; i <= N; i++)
		{
			bool check = false;
			for (int k = 0; k < selected.size(); k++)
			{
				if (selected[k] == i)
					check = true;
			}
			if (!check)
				unselected.push_back(i);
		}
		
		if (result > Calc(selected, unselected))
		{
			result = Calc(selected, unselected);
		}
		// cout << Calc(selected, unselected)<<endl;

		/*for (int i = 0; i < unselected.size(); i++)
		{
			cout << unselected[i] << " ";
		}
		cout << endl;*/
		return;
	}
	else if (start > N) // start가 N보다 클수는 없어!
	{
		return;
	}
	else
	{
		for (int i = start + 1; i <= N; i++)
		{
			selected.push_back(i);
			dfs(i, selected);
			selected.pop_back();
		}
	}
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 1; i <= N; i++)
	{
		selected.push_back(i);
		dfs(i, selected);
		selected.pop_back();
	}

	cout << result;
	return 0;
}