#include <iostream>
#include <cstring>
using namespace std;

const int N = 30;

int n;          // 矩阵个数
int matrix[N];  // 矩阵的行列数
int f[N][N];    // f[i][j]: 从第i个矩阵到第j个矩阵的最小乘法次数
int root[N][N]; // root[i][j]: 从第i个矩阵到第j个矩阵的最优分割位置
int case_number = 0;

void solve()
{
    for (int length = 2; length <= n; ++length)
    {
        for (int i = 1; i <= n - length + 1; ++i)
        {
            int j = i + length - 1;
            f[i][j] = 0x7fffffff; // 初始化为一个较大的数
            for (int k = i; k < j; ++k)
            {
                // 计算f[i][j]的最小值和最优分割位置
                int q = f[i][k] + f[k + 1][j] + matrix[i - 1] * matrix[k] * matrix[j];
                if (q < f[i][j])
                {
                    f[i][j] = q;
                    root[i][j] = k;
                }
            }
        }
    }
}

void print(int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else
    {
        if (i != 1 || j != n)
            cout << "(";
        print(i, root[i][j]);
        print(root[i][j] + 1, j);
        if (i != 1 || j != n)
            cout << ")";
    }
}

int main()
{
    while (true)
    {
        ++case_number;
        cin >> n;
        if (n == 0)
            break;

        for (int i = 0; i <= n; ++i)
            cin >> matrix[i];

        memset(f, 0, sizeof(f)); // 初始化f数组
        solve();                 // 调用解决函数

        cout << "Case " << case_number << endl;
        cout << f[1][n] << ' '; // 输出最小乘法次数
        print(1, n);            // 输出最优分割方式

        cout << endl;
    }

    return 0;
}
