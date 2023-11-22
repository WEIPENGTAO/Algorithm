#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 60;

int m, n; // m = len(x), n = len(y)
int dp[N][N];
char x[N], y[N];
vector<vector<char>> lcs_list;

void find_all_lcs(int i, int j, vector<char> &lcs)
{
    if (i == 0 || j == 0) // 递归边界
    {
        reverse(lcs.begin(), lcs.end()); // 由于得到的是一个逆序的LCS，所以需要将其反转
        lcs_list.push_back(lcs);
        reverse(lcs.begin(), lcs.end()); // 恢复原来的顺序
        return;
    }

    if (x[i] == y[j]) // 如果x[i] == y[j]，则x[i]和y[j]一定在LCS中，在左上角的dp[i-1][j-1]处继续寻找
    {
        lcs.push_back(x[i]);
        find_all_lcs(i - 1, j - 1, lcs);
        lcs.pop_back();
    }
    else
    {
        if (dp[i - 1][j] == dp[i][j])
            find_all_lcs(i - 1, j, lcs);
        if (dp[i][j - 1] == dp[i][j])
            find_all_lcs(i, j - 1, lcs);
    }
}

void lcs()
{
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (x[i] == y[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    lcs_list.clear();
    vector<char> lcs;
    find_all_lcs(m, n, lcs);
}

int main()
{
    int T;
    cin >> T;

    for (int case_num = 1; case_num <= T; ++case_num)
    {
        cin >> m >> n;

        for (int i = 1; i <= m; ++i)
            cin >> x[i];

        for (int i = 1; i <= n; ++i)
            cin >> y[i];

        lcs();

        cout << endl
             << " "
             << "\t";
        for (int i = 1; i <= n; ++i)
            cout << y[i] << "\t";
        cout << endl;

        for (int i = 1; i <= m; ++i)
        {
            cout << x[i] << "\t";
            for (int j = 1; j <= n; ++j)
                cout << dp[i][j] << "\t";
            cout << endl;
        }
        cout << endl;

        for (auto &lcs : lcs_list)
        {
            for (auto &c : lcs)
                cout << c;
            cout << endl;
        }
    }

    system("pause");
    return 0;
}