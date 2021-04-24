#include<iostream>
#include<algorithm>

using namespace std;

int T[20];
int P[20];
int N;

int dp[20]; ///i번째까지 일한 날 최대 금액, 돈은 i+t[i]날 돈을 받음

int main()
{
	ios::sync_with_stdio;
	cin.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> T[i] >> P[i];
	}

	for (int i = 1; i <= N + 1; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (i == j + T[j]) // j일의 상담료를 받았을 때
			{
				dp[i] = max(dp[i], dp[j] + P[j]);
			}
			else
			{
				dp[i] = max(dp[i], dp[j]);
			}

		}
	}

	cout << dp[N + 1];
	return 0;
}