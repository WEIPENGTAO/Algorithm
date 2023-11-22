#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;

// 跳马问题
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

const int N = 10;
int vis[N][N];

int bfs(int sx, int sy, int ex, int ey)
{
    queue<PII> q;
    q.push({sx, sy});
    vis[sx][sy] = 0;

    while (!q.empty())
    {
        PII t = q.front();
        q.pop();

        if (t.first == ex && t.second == ey)
            return vis[ex][ey];

        for (int i = 0; i < 8; i++)
        {
            int x = t.first + dx[i], y = t.second + dy[i];
            if (x < 0 || x >= N || y < 0 || y >= N)
                continue;
            if (vis[x][y] != 0)
                continue;
            vis[x][y] = vis[t.first][t.second] + 1;
            q.push({x, y});
        }
    }
    return -1;
}

// 求最短路径
int dfs(int sx, int sy, int ex, int ey, int step)
{
    if (sx == ex && sy == ey)
        return step;

    int res = 1e9;
    for (int i = 0; i < 8; i++)
    {
        int x = sx + dx[i], y = sy + dy[i];
        if (x < 0 || x >= N || y < 0 || y >= N)
            continue;
        if (vis[x][y] != 0)
            continue;
        vis[x][y] = 1;
        res = min(res, dfs(x, y, ex, ey, step + 1));
        vis[x][y] = 0;
    }
    return res;
}

int main()
{
    char st[3], ed[3];

    while (true)
    {
        cin >> st >> ed;
        int sx = st[0] - 'a', sy = st[1] - '1';
        int ex = ed[0] - 'a', ey = ed[1] - '1';

        memset(vis, 0, sizeof vis);
        time_t start = clock();
        cout << "bfs:" << endl;
        cout << st << "==>" << ed << ": " << bfs(sx, sy, ex, ey) << " moves" << endl;
        cout << "bfs time: " << clock() - start << endl;

        cout << endl;

        memset(vis, 0, sizeof vis);
        start = clock();
        cout << "dfs:" << endl;
        cout << st << "==>" << ed << ": " << dfs(sx, sy, ex, ey, 0) << " moves" << endl;
        cout << "dfs time: " << clock() - start << endl;
    }

    return 0;
}