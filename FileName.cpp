#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, pn;
string map[1004];
queue<pair<int, int>> q;
queue<pair<pair<int, int>, int>> dist;
pair<int, int> check[1004][1004];
int visited[1004][1004];
int p[10], ans[10];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void input()
{
    cin >> n >> m >> pn;
    for (int i = 1; i <= pn; i++)
        cin >> p[i];
    for (int i = 0; i < n; i++)
        cin >> map[i];

    for (int i = 1; i <= pn; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                char tmp = i + '0';
                if (map[j][k] == tmp)
                {
                    q.push({ j, k });
                    check[j][k].first = i;
                    visited[j][k] = 1;
                }
            }
        }
    }
}

void BFS()
{
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        int s = check[x][y].first;
        q.pop();

        dist.push({ {x, y}, 0 });
        while (!dist.empty())
        {
            int d = dist.front().second;
            int mx = dist.front().first.first;
            int my = dist.front().first.second;
            dist.pop();

            for (int i = 0; i < 4; i++)
            {
                int nx = mx + dx[i];
                int ny = my + dy[i];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m
                    || map[nx][ny] == '#' || (check[nx][ny].first != 0 && check[nx][ny].first != s) 
                    || d >= p[s] || (check[nx][ny].second != 0 && check[nx][ny].second - 1 <= d)) continue;

                q.push({nx, ny});
                dist.push({ {nx, ny}, d + 1 });
                check[nx][ny] = { s, d + 1 };
            }
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans[check[i][j].first]++;

    for (int i = 1; i <= pn; i++)
        cout << ans[i] << " ";
}

void Solve()
{
    input();
    BFS();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();

    return 0;
}
