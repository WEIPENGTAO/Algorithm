#include <iostream>
#include <queue>
using namespace std;

// 哈夫曼树节点
struct Node
{
    int weight;         // 权重
    Node *left, *right; // 左右孩子
    int id;             // 节点编号
    string code;        // 编码

    Node(int weight, int id) : weight(weight), id(id), left(nullptr), right(nullptr) {}
};

// 优先队列的比较函数
struct cmp
{
    bool operator()(Node *a, Node *b) // 重载()运算符
    {
        if (a->weight == b->weight) // 如果权重相同，编号小的优先级高
        {
            return a->id < b->id;
        }
        return a->weight > b->weight; // 否则权重大的优先级高
    }
};

// 哈夫曼树
class HuffmanTree
{
private:
    Node *root;                               // 根节点
    Node **node_list;                         // 节点列表
    int node_list_size;                       // 节点列表大小
    void delete_tree(Node *root);             // 删除以root为根的子树
    void generate_code(Node *root, string s); // 生成编码
public:
    HuffmanTree(int *weight, int n); // 根据权重数组weight构造哈夫曼树
    ~HuffmanTree();                  // 析构函数
    void print();                    // 打印编码
};

// 构造函数
HuffmanTree::HuffmanTree(int *weight, int n)
{
    // 初始化节点列表
    node_list = new Node *[n];
    node_list_size = n;

    for (int i = 0; i < n; ++i)
    {
        node_list[i] = new Node(weight[i], i);
    }

    // 构造哈夫曼树
    priority_queue<Node *, vector<Node *>, cmp> pq;
    for (int i = 0; i < n; ++i)
    {
        pq.push(node_list[i]);
    }

    int id = n;

    while (pq.size() > 1)
    {
        Node *a = pq.top();
        pq.pop();
        Node *b = pq.top();
        pq.pop();
        Node *c = new Node(a->weight + b->weight, id++);
        c->left = b;
        c->right = a;
        pq.push(c);
    }
    root = pq.top();
    pq.pop();
}

// 析构函数
HuffmanTree::~HuffmanTree()
{
    delete_tree(root);
    delete[] node_list;
}

// 删除以root为根的子树
void HuffmanTree::delete_tree(Node *root)
{
    if (root == nullptr)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

// 生成编码
void HuffmanTree::generate_code(Node *root, string s)
{
    if (root == nullptr)
        return;
    if (root->left == nullptr && root->right == nullptr)
    {
        root->code = s;
        return;
    }
    generate_code(root->left, s + "0");
    generate_code(root->right, s + "1");
}

// 打印编码
void HuffmanTree::print()
{
    generate_code(root, "");
    for (int i = 0; i < node_list_size; ++i)
    {
        cout << node_list[i]->weight << " " << node_list[i]->code << endl;
    }
}

int main()
{
    int T;
    cin >> T;

    for (int case_num = 1; case_num <= T; ++case_num)
    {
        int n;
        cin >> n;

        int *weight = new int[n];
        for (int i = 0; i < n; ++i)
            cin >> weight[i];

        HuffmanTree huffman_tree(weight, n);

        cout << "Case " << case_num << endl;
        huffman_tree.print();
        cout << endl;

        delete[] weight;
    }

    system("pause");
    return 0;
}