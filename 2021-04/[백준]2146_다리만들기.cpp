#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int map[40][40];
int result[40][40] = { 0, };
int dist[40][40] = { 0, };
int par[410];
int n, m;
int ans = -1;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0, -1,0,1 };
int nx, ny;
int fx, fy;
int guyeok = 1;
int tmp = 0;
queue<pair<int, int>> q;
bool visited[20][20] = { false, };

struct Kru {
	int x;
	int y;
	int cost;
};

// 단지 번호 붙이기
void bfs(int x, int y)
{
	q.push({ x, y });

	while (!q.empty())
	{
		fx = q.front().first;
		fy = q.front().second;

		visited[fx][fy] = true;
		result[fx][fy] = guyeok;

		for (int k = 0; k < 4; k++)
		{
			nx = fx + dx[k];
			ny = fy + dy[k];
			if (nx > 0 && nx <= n && ny > 0 && ny <= m)
			{
				if (!visited[nx][ny] && map[nx][ny] == 1)
				{
					q.push({ nx, ny });
				}
			}
		}
		q.pop();
	}
	return;
}

void getNum()
{
	int cnt = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (!visited[i][j] && map[i][j] == 1)
			{
				bfs(i, j);
				guyeok += 1;
			}
		}
	}
	guyeok -= 1;
	return;
}

// 단지 거리 계산하기
void getDist()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (result[i][j] > 0) // 좌표가 있을 때
			{
				for (int k = 0; k < 4; k++)
				{
					int step = 0;
					nx = i;
					ny = j;
					while (1)
					{
						nx = nx + dx[k];
						ny = ny + dy[k];
						if (result[i][j] != result[nx][ny] && result[nx][ny] != 0) // 0
						{
							if (dist[result[i][j]][result[nx][ny]] == 0 || step < dist[result[i][j]][result[nx][ny]]) // dist가 0이거나 최소거리라면
							{
								if (step >= 2)
								{
									dist[result[i][j]][result[nx][ny]] = step;
								}
							}
						}
						if (nx <= 0 || nx > n || ny <= 0 || ny > m || result[nx][ny] != 0) //범위를 벗어나거나 0이 안나올때 까지
						{
							break;
						}
						step += 1;
					}
				}
			}
		}
	}
}

bool comp(Kru a1, Kru a2)
{
	return a1.cost < a2.cost;
}

int findNode(int x)
{
	if (par[x] == x)
		return x;
	else
	{
		return par[x] = findNode(par[x]); //재귀적으로 부모 노드를 찾는 함수
	}
}

void link(int x, int y)
{
	par[findNode(y)] = findNode(x);
}

bool isConnect()
{
	bool flag = true;

	int temp = findNode(1);
	for (int i = 2; i <= guyeok; i++)
	{
		if (temp !=findNode(i))
		{
			flag = false;
		}
	}
	return flag;
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);

	cin >> n >> m;
	// cin >> n;
	// m = n;
	vector<Kru>kru;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> map[i][j];
		}
	}

	getNum();

	/*cout << "단지번호붙이기 결과" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cout<<result[i][j]<<" ";
		}
		cout << endl;
	}*/

	getDist();

	//cout << "단지간 길이 구하기 결과" << endl; //단지번호는 1부터 시작
	//for (int i = 1; i <= guyeok; i++)
	//{
	//	for (int j = 1; j <= guyeok; j++)
	//	{
	//		cout << dist[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	for (int i = 1; i <= guyeok; i++)
	{
		for (int j = i + 1; j <= guyeok; j++)
		{
			if (dist[i][j] >= 2) //길이가 2보다 큰 다리만 건설
			{
				Kru k;
				k.x = i;
				k.y = j;
				k.cost = dist[i][j];
				kru.push_back(k);
			}
		}
	}

	sort(kru.begin(), kru.end(), comp);

	for (int i = 1; i <= guyeok; i++)
	{
		par[i] = i;
	}

	int idx = 0;
	int cnt = 0;

	tmp = 0;

	while (idx < kru.size())
	{
		if (findNode(kru[idx].x) != findNode(kru[idx].y))
		{
			link(kru[idx].x, kru[idx].y);
			tmp += kru[idx].cost;
			cnt++;
		}
		idx++;

		if (cnt == guyeok - 1)
		{
			break;
		}
	}

	/*cout << "parent Result" << endl;
	for (int i = 1; i <= guyeok; i++)
	{
		cout << par[i] << " ";
	}*/
	if (isConnect())
	{
		ans = tmp;
	}

	cout << ans;
	return 0;
}