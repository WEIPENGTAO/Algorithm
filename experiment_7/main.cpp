#include <iostream>
#include <cstring>
using namespace std;

const int N = 30;
int n, w[N], b[N], bestw, x[N];

void dfs(int u, int c1, int c2, int sum)
{
    if (u == n + 1)
    {
        if (c1 >= 0 && c2 >= 0 && sum > bestw)
        {
            for (int i = 1; i <= n; ++i)
                x[i] = b[i];
            bestw = sum;
        }
        return;
    }

    if (c1 - w[u] >= 0)
    {
        b[u] = 1;
        dfs(u + 1, c1 - w[u], c2, sum + w[u]);
        b[u] = -1;
    }

    if (c2 - w[u] >= 0)
    {
        b[u] = 0;
        dfs(u + 1, c1, c2 - w[u], sum);
        b[u] = -1;
    }

    if (c1 <= w[u] && c2 <= w[u])
        return;
}

int main()
{
    int c1, c2, case_num = 0;

    while (true)
    {
        cin >> n;

        for (int i = 1; i <= n; ++i)
            cin >> w[i];

        cin >> c1 >> c2;

        bestw = 0;
        memset(x, -1, sizeof x);
        memset(b, -1, sizeof b);
        dfs(1, c1, c2, 0);

        cout << "Case " << ++case_num << endl;

        if (x[n] == -1)
            cout << "No" << endl;
        else
        {
            cout << bestw << " ";
            for (int i = 1; i <= n; ++i)
                cout << x[i];
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}