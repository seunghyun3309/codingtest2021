#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int par[2020];

struct A {
	int x;
	int y;
	int cost;
};

A a;

bool comp(A a1, A a2)
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

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<A>v(m);

	for (int i = 1; i <= n; i++)
	{
		par[i] = i;
	}

	for (int i = 0; i < m; i++)
	{
		cin >> v[i].x >> v[i].y >> v[i].cost;
	}

	sort(v.begin(), v.end(), comp);

	int ans = 0;

	for (int i = 0; i < m; i++)
	{
		if (findNode(v[i].x) != findNode(v[i].y)) 
		{
			link(v[i].x,v[i].y); //link안에서 부모노드를 찾아감
			ans+=v[i].cost;
		}

	}
	cout << ans;


	return 0;
}