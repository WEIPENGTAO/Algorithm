#include <iostream>
#include <cstring>
using namespace std;

const int N = 60;

int g[N][N], n;
int dist[N], path[N], st[N], segs[N];

void print_path(int v, int e)
{
    if (v == 0)
        return;

    print_path(path[v], e);
    if (v != e)
        cout << v << "->";
    else
        cout << v;
}

void dijkstra(int s, int e)
{
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    memset(segs, 0x3f, sizeof segs);

    dist[s] = 0;
    segs[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int t = -1;
        for (int j = 1; j <= n; ++j)
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;

        st[t] = true;
        for (int j = 1; j <= n; ++j)
        {
            if (g[t][j] == -1)
                continue;
            if (dist[j] > dist[t] + g[t][j])
            {
                dist[j] = dist[t] + g[t][j];
                path[j] = t;
            }
            else if (dist[j] == dist[t] + g[t][j]) // 如果距离相等，那么就比较路段数
            {
                if (segs[j] > segs[t] + 1)
                {
                    segs[j] = segs[t] + 1;
                    path[j] = t;
                }
                else if (segs[j] == segs[t] + 1) // 如果路段数相等，那么就比较路径字典序
                {
                    if (path[j] > t)
                        path[j] = t;
                }
            }
        }
    }

    cout << "The least distance from " << s << "->" << e << " is: " << dist[e] << endl;
    cout << "The path is ";

    print_path(e, e);
    cout << endl;

    cout << endl;
}

int main()
{
    int case_num = 0, s, e;

    while (cin >> n)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cin >> g[i][j];

        cin >> s >> e;

        cout << "Case " << ++case_num << endl;
        dijkstra(s, e);
    }

    return 0;
}