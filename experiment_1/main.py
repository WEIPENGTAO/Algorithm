import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def generate_random_colors(board):
    n = len(board)
    colors = dict()

    colors[-1] = (1.0, 1.0, 1.0)

    for i in range(n):
        for j in range(n):
            while True:
                # 生成 0-1 之间的随机数
                r = np.random.rand()
                g = np.random.rand()
                b = np.random.rand()
                new_color = (r, g, b)
                if new_color not in colors.values():
                    if board[i][j] not in colors.keys():
                        colors[board[i][j]] = new_color
                    break
    
    return colors

def visualize_board(board):
    n = len(board)
    plt.figure(figsize=(8, 8))
    
    colors = generate_random_colors(board)
    
    for i in range(n):
        for j in range(n):
            tile_color = colors[board[i][j]]
            rect = patches.Rectangle((j, n - i - 1), 1, 1, linewidth=1, edgecolor='black', facecolor=tile_color)
            plt.gca().add_patch(rect)
            if board[i][j] == -1:
                rect = patches.Rectangle((j, n - i - 1), 1, 1, linewidth=1, edgecolor='black', facecolor='none', hatch='///')
                plt.gca().add_patch(rect)

    plt.xlim(0, n)
    plt.ylim(0, n)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.xticks([])
    plt.yticks([])
    plt.show()

num = 0

def chessboard_cover(board, size, top_row, left_column, special_x, special_y):
    if size == 1:
        return

    global num

    half = size // 2
    num += 1
    cur_num = num

    # 递归处理左上角
    if special_x < top_row + half and special_y < left_column + half:
        chessboard_cover(board, half, top_row, left_column, special_x, special_y)
    else:
        board[top_row + half - 1][left_column + half - 1] = cur_num
        chessboard_cover(board, half, top_row, left_column, top_row + half - 1, left_column + half - 1)

    # 递归处理右上角
    if special_x < top_row + half and special_y >= left_column + half:
        chessboard_cover(board, half, top_row, left_column + half, special_x, special_y)
    else:
        board[top_row + half - 1][left_column + half] = cur_num
        chessboard_cover(board, half, top_row, left_column + half, top_row + half - 1, left_column + half)

    # 递归处理左下角
    if special_x >= top_row + half and special_y < left_column + half:
        chessboard_cover(board, half, top_row + half, left_column, special_x, special_y)
    else:
        board[top_row + half][left_column + half - 1] = cur_num
        chessboard_cover(board, half, top_row + half, left_column, top_row + half, left_column + half - 1)

    # 递归处理右下角
    if special_x >= top_row + half and special_y >= left_column + half:
        chessboard_cover(board, half, top_row + half, left_column + half, special_x, special_y)
    else:
        board[top_row + half][left_column + half] = cur_num
        chessboard_cover(board, half, top_row + half, left_column + half, top_row + half, left_column + half)


def print_board(board):
    for row in board:
        print('\t'.join(map(str, row)))


def main():
    cases = int(input("请输入测试用例的数量："))
    for case in range(1, cases + 1):
        k, x, y = map(int, input(f"请输入第 {case} 个测试用例的 k、x 和 y 值（以空格分隔）：").split())
        n = 2 ** k
        board = [[0 for _ in range(n)] for _ in range(n)]
        board[x - 1][y - 1] = -1
        chessboard_cover(board, n, 0, 0, x - 1, y - 1)

        print(f"第 {case} 个测试用例：n={n}")
        print_board(board)
        visualize_board(board)


if __name__ == "__main__":
    main()
