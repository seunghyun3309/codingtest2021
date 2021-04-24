#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int arr[20][20];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0, -1 };
int answer = -1;
int tmp, cnt = 0;
bool visited[20][20] = { false, };
bool isVirus[20][20] = { false, };
int nx, ny, qx, qy;

struct Pos {
	int xpos;
	int ypos;
};

vector<Pos>virus;
queue<Pos>q;

void bfs()
{
	memset(isVirus, false, sizeof(isVirus));
	for (int i = 0; i < virus.size(); i++)
	{
		memset(visited, false, sizeof(visited));
		q.push({ virus[i].xpos,virus[i].ypos });
		visited[virus[i].xpos][virus[i].ypos] = true;
		isVirus[virus[i].xpos][virus[i].ypos] = true;
		while (!q.empty())
		{
			qx = q.front().xpos;
			qy = q.front().ypos;

			for (int k = 0; k < 4; k++)
			{
				nx = qx + dx[k];
				ny = qy + dy[k];

				if (nx >= 0 && nx < N && ny >= 0 && ny < M)
				{
					if (!visited[nx][ny] &&!isVirus[nx][ny]&& arr[nx][ny] == 0)
					{
						visited[nx][ny] = true;
						isVirus[nx][ny] = true;
						q.push({ nx, ny });
					}
				}
			}
			q.pop(); //이거 꼭 해야해
		}
	}



	tmp = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (!isVirus[i][j] && arr[i][j] == 0)
			{
				tmp++;
			}
		}
	}
	if (tmp > answer)
	{
		answer = tmp;
	}
}

void dfs(int cnt)
{
	if (cnt > 3)
	{
		return;
	}
	else if (cnt == 3)
	{
		bfs();
		return;
	}
	else {
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (arr[i][j] == 0)
				{
					arr[i][j] = 1;
					dfs(cnt + 1);
					arr[i][j] = 0;
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
		for (int j = 0; j < M; j++)
		{
			cin >> arr[i][j];
			if (arr[i][j] == 2)
			{
				virus.push_back({ i, j });
			}
		}
	}

	dfs(0);

	cout << answer;
}