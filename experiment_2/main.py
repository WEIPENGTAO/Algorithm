def matrix_chain_order(p):
    n = len(p) - 1
    m = [[0] * (n + 1) for _ in range(n + 1)]   # 用于记录最优解
    s = [[0] * (n + 1) for _ in range(n + 1)]   # 用于记录最优分割位置
    
    for lenth in range(2, n + 1):
        for i in range(1, n - lenth + 2):
            j = i + lenth - 1
            m[i][j] = 0x7fffffff
            for k in range(i, j):
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k
    
    return m, s

def print_optimal_parentheses(s, i, j):
    if i == j:
        print(f"A{i}", end="")
    else:
        print("(", end="")
        print_optimal_parentheses(s, i, s[i][j])
        print_optimal_parentheses(s, s[i][j] + 1, j)
        print(")", end="")

if __name__ == "__main__":
    # 读取输入并处理
    case_number = 0
    while True:
        try:
            n = int(input())
            if n == 0:
                break
            case_number += 1
            dimensions = list(map(int, input().split()))
            
            m, s = matrix_chain_order(dimensions)
            print(f"Case {case_number}")
            print(f"{m[1][n]} ", end="")
            print_optimal_parentheses(s, 1, n)
            print()
            
        except EOFError:
            break
