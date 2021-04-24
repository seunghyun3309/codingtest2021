#include <iostream>

using namespace std;

int M, N;
int a, b, c;
int par[1000010]; // i의 부모 노드

int findNode(int x)
{
	if (par[x] == x)
	{
		return x;
	}
	else
	{
		return par[x] = findNode(par[x]); // 재귀적으로 부모를 호출
	}
}

void link(int x, int y)
{
	par[findNode(y)]=findNode(x);
}

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		par[i] = i;
	}

	for (int i = 0; i < M; i++)
	{
		cin >> c>> a >> b;
		if (c == 1) // Yes인지 No인지
		{
			if (findNode(a) == findNode(b))
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
		}
		else if(c==0)
		{
			link(a,b);
		}
		/*for (int k = 0; k < N; k++)
		{
			cout << par[k] << " ";
		}
		cout << endl;*/
	}
	return 0;
}