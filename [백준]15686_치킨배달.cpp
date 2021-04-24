#include <iostream>
#include <deque>
#include <queue>
#include<vector>
#include<algorithm>
#include<cmath>
#include <cstring>
using namespace std;

int M, N;
int map[60][60];
int d[60][60] = { 0, };
int visited[60][60] = { false, };
int tmp;
int result, answer = 98765432;
vector<pair<int, int>>selectChicken;

void dis_sum(vector<pair<int, int>>selected)
{
	result = 0;
	memset(d, 0, sizeof(d));
	for (int k = 0; k < selected.size(); k++) // N*N* k개 만큼 수행
	{
		int i = selected[k].first;
		int j = selected[k].second;
		// cout << i << j << endl;
		for (int s = 0; s < N; s++)
		{
			for (int t = 0; t < N; t++)
			{
				if (map[s][t] == 1) // 치킨집이면 각 집마다의 최소 거리를 입력하자
				{
					tmp = abs(s - i) + abs(t - j);

					if (d[s][t] == 0)
					{
						d[s][t] = tmp;
					}
					else if (d[s][t] > tmp) // tmp가 더 작으면
					{
						d[s][t] = tmp; // tmp값으로 업데이트
					}
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result += d[i][j];
		}
	}

	//cout << result<< endl;

	if (result < answer)
	{
		answer = result;
	}
	return;
}

void choice(vector<pair<int, int>> selected, int num)
{
	if (selected.size() == M)
	{
		//for (int i = 0; i < selected.size(); i++)
		//{
		//	cout << selected[i].first << "," << selected[i].second << " ";
		//}
		dis_sum(selected);

		return;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if ((((i * N) + j) >= num) && !visited[i][j] && map[i][j] == 2)
				{
					visited[i][j] = true;
					selected.push_back({ i,j });
					choice(selected, i * N + j);
					selected.pop_back();
					visited[i][j] = false;
				}
			}
		}
	}
}



int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}

	choice(selectChicken, 0);

	cout << answer;

	return 0;
}