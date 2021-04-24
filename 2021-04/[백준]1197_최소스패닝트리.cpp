#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E;
int answer = 0;
int par[100010];

struct edge {
	int xpos;
	int ypos;
	int weigh;
};

edge e[100010];


bool comp(edge e1, edge e2)
{
	return e1.weigh < e2.weigh;
}



int findNode(int x)
{
	if (x == par[x])
	{
		return x;
	}
	else
	{
		return par[x] = findNode(par[x]);
	}
}

void linkNode(int x, int y)
{
	par[findNode(y)] = findNode(x);
}

bool isCycle()
{
	int tmp = findNode(1);
	for (int i = 2; i <= V; i++)
	{
		if (tmp != findNode(i))
			return false;
	}
	return true;

}
int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	cin >> V >> E;

	int a, b, c;
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b >> c;
		e[i].xpos = a;
		e[i].ypos = b;
		e[i].weigh = c;
	}
	for (int i = 1; i <= V; i++)
	{
		par[i] = i;
	}

	sort(e, e + E, comp);

	int idx = 0;
	int connected = 0;

	while (idx < E) //간선의 개수만큼 시행
	{
		if (findNode(e[idx].xpos) != findNode(e[idx].ypos))
		{
			connected++;
			answer += e[idx].weigh;
			linkNode(e[idx].xpos, e[idx].ypos);
		}

		if (connected == V - 1)
			break;

		idx++;
	}

	cout << answer;
	return 0;
}