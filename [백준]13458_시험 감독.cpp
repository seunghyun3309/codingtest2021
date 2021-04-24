#include<iostream>

using namespace std;

long long A[1000010];
long long monitored[1000010];

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);
	int N, B, C;

	cin >> N;
	long long res = N;
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
		monitored[i] = A[i];
	}
	cin >> B >> C;

	for (int i = 0; i < N; i++)
	{
		monitored[i] -= B; //총감독수가 감시하는 만큼 빼
		if (monitored[i] > 0) //부감독이 필요한 경우
		{
			if (monitored[i] % C == 0)
			{
				res += monitored[i] / C;
			}
			else
			{
				res += (monitored[i] / C) + 1;
			}
		}
	}

	cout << res;

	return 0;
}