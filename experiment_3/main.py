def find_all_lcs(X, Y, m, n, dp):
    if m == 0 or n == 0:
        return [[]]
    
    if X[m - 1] == Y[n - 1]:    # 如果X[m - 1] == Y[n - 1]，则X[m - 1]一定在LCS中，从左上角继续寻找
        lcs_list = find_all_lcs(X, Y, m - 1, n - 1, dp)
        for lcs in lcs_list:
            lcs.append(X[m - 1])
        return lcs_list
    else:
        lcs_list = []
        
        if dp[m - 1][n] >= dp[m][n - 1]:    # 如果dp[m - 1][n] >= dp[m][n - 1]，可以从上方继续寻找
            lcs_list.extend(find_all_lcs(X, Y, m - 1, n, dp))
        
        if dp[m][n - 1] >= dp[m - 1][n]:    # 如果dp[m][n - 1] >= dp[m - 1][n]，可以从左方继续寻找
            lcs_list.extend(find_all_lcs(X, Y, m, n - 1, dp))
        
        return lcs_list

def longest_common_subsequences(X, Y):
    m, n = len(X), len(Y)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if X[i - 1] == Y[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    all_lcs = find_all_lcs(X, Y, m, n, dp)
    return dp[m][n], all_lcs

if __name__ == "__main__":
    # 读取输入数据
    T = int(input())
    for case in range(1, T + 1):
        m, n = map(int, input().split())
        X = input().split()
        Y = input().split()
        
        # 求最长公共子序列
        length, lcs_list = longest_common_subsequences(X, Y)
        
        # 输出结果
        print(f"Case {case}")
        print(f"{length} LCS(X,Y):")
        for lcs in lcs_list:
            print(" ".join(lcs))
