/*
S Samarth Reddy
B19109
Group 25
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long int

int n, m;

bool valid(int x, int y)
{
	if (x < 0 || y < 0 || x >= n || y >= m)return 0;
	return 1;
}

void solve()
{

	cin >> n >> m;

	int mat[n][m];          //the matrix
	int time[n][m];           //time of each cell infection
	queue<pair<int, int>> Q;    //queue for bfs
	int MaxTime = 0;              //total time taken

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mat[i][j];
			time[i][j] = 0;
			if (mat[i][j] == 2) Q.push({ i,j });
		}
	}

	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	while (!Q.empty())
	{
		pair<int, int> P = Q.front();
		Q.pop();

		for (int i = 0; i < 4; i++)
		{
			int x = P.first + dir[i][0], y = P.second + dir[i][1];
			if (valid(x, y) && mat[x][y] == 1) {
                mat[x][y] = 2;
                Q.push({ x, y });
                time[x][y] = time[P.first][P.second] + 1;
            }
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (mat[i][j] == 1) { cout << "-1\n"; return; }
			MaxTime = max(MaxTime, time[i][j]);
		}
	cout << MaxTime << "\n";
}

int main() {
    solve();
    return 0;
}
