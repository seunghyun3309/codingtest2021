#include <iostream>
#include<algorithm>
#include <vector>
#include<cstring>
#include<cstdlib>

using namespace std;

struct Pos {
	int xpos;
	int ypos;
};

int N, L, R;
int map[60][60];
bool visited[60][60] = { false, };
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int num = 0; int people = 0; int answer = 0;

vector<Pos>v;

void dfs(int i, int j)
{
	visited[i][j] = true;

	for (int d = 0; d < 4; d++)
	{
		int nx = i + dx[d];
		int ny = j + dy[d];
		if (nx >= 0 && nx < N && ny >= 0 && ny < N)
		{
			if (!visited[nx][ny] && abs(map[i][j] - map[nx][ny]) <= R && abs(map[i][j] - map[nx][ny]) >= L)
			{
				v.push_back({ nx, ny });
				num++;
				people += map[nx][ny];
				dfs(nx, ny);
			}
		}
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
	bool flag = true;

	while (flag)
	{
		memset(visited, false, sizeof(visited));

		flag = false;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (visited[i][j])	continue;

				v.clear();
				v.push_back({ i,j });
				num = 1;
				people = map[i][j];
				dfs(i, j);

				if (num >= 2)
				{
					flag = true;

					int result = people / num;;
					for (int i = 0; i < v.size(); i++)
					{
						int x = v[i].xpos;
						int y = v[i].ypos;
						map[x][y] = result;
					}
				}
			}
		}
		if (flag) {
			answer += 1; //인구 이동 횟수
		}

		else {
			break;
		}
	}

	cout << answer;
	return 0;
}
