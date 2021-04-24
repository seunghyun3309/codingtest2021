#include <iostream>
#include<algorithm>
#include <queue>
#include <vector>
#include<cstring>

using namespace std;
int N, M;
int map[60][60];
int infect[60][60];
int canInfect = 0;
int answer = 98765432;

struct Pos {
	int xpos;
	int ypos;
};
vector<Pos> canVirus; // 활성화된 바이러스를 담는 벡터
vector<Pos> activate; // 활성화된 바이러스를 담는 벡터
bool selected[60] = { false, };
bool visited[60][60] = { false, };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };


void bfs()
{
	queue<Pos>q;

	for (int i = 0; i < activate.size(); i++) {
		q.push({ activate[i].xpos, activate[i].ypos });
		visited[activate[i].xpos][activate[i].ypos] = true;
		infect[activate[i].xpos][activate[i].ypos] = 0;
	}

	int infectNum = 0;
	int sec = 0;
	while (!q.empty()) {
		int size = q.size();

		while (size--)
		{
			int qx = q.front().xpos;
			int qy = q.front().ypos;
			q.pop();
			for (int d = 0; d < 4; d++)
			{
				int nx = qx + dx[d];
				int ny = qy + dy[d];

				if (nx >= N || nx < 0 || ny >= N || ny < 0)
				{
					continue;
				}
				if (!visited[nx][ny] && map[nx][ny]!=1&& infect[nx][ny]==-1)
				{
					visited[nx][ny] = true;
					infect[nx][ny] = infect[qx][qy] + 1;
					if (map[nx][ny] == 0)
					{
						infectNum += 1;
						sec = infect[nx][ny];
					}
					q.push({ nx, ny });
				}
			}
		}

		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//	{
		//		cout << infect[i][j] << " ";
		//	}
		//	cout << endl;
		//}
		//cout << endl;
		
	}
	if (canInfect == infectNum)
		answer = min(answer, sec);
}

void dfs(int idx, int cnt)
{
	if (cnt == M)
	{
		memset(visited, false, sizeof(visited));
		memset(infect, -1, sizeof(infect));
		bfs();
		return;
	}
	else
	{
		for (int k = idx; k < canVirus.size(); k++)
		{
			if (!selected[k])
			{
				selected[k] = true;
				activate.push_back({ canVirus[k].xpos, canVirus[k].ypos });
				dfs(k, cnt + 1);
				activate.pop_back();
				selected[k] = false;
			}
		}
		return;
	}
}


int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 2)
			{
				canVirus.push_back({ i,j });
			}
			else if (map[i][j] == 0)
			{
				canInfect++;
			}
		}
	}

	dfs(0, 0);

	if (answer == 98765432)
	{
		cout << -1;
	}
	else
	{
		cout << answer;

	}

	return 0;
}
