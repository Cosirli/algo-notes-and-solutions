#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int parent;
    int length;
    int max_len;
    int out;
    bool is_cut;
    ~Node() {}
};


class dTree {
private:
    Node* tree;
    std::queue<int> q;
    int n, d, cut_count;
public:
    dTree(int n, int d) : n(n), d(d), cut_count(0)
    {
        tree = new Node[n];
        tree[0].parent = -1;
        tree[0].length = 0;

        for (int i = 0; i < n; ++i) {
            int k;
            std::cin >> k;
            tree[i].max_len = 0;
            tree[i].out = k;
            tree[i].is_cut = false;
            for (int j = 0; j < k; ++j) {
                int id, w;
                std::cin >> id >> w;
                tree[id].parent = i;
                tree[id].length = w;
            }
        }
    }
    ~dTree() {}


    void solution()
    {
        for (int i = n - 1; i >= 0; --i) {
            if (tree[i].out == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int temp = q.front();
            q.pop();
            int len = tree[temp].length;
            int par = tree[temp].parent;

            if (tree[par].is_cut == false && tree[temp].max_len + len > d) {
                tree[par].is_cut = true;
                par = tree[par].parent;
                cut_count++;
            } else if (tree[temp].is_cut == false && tree[par].max_len < tree[temp].max_len + len) {
                tree[par].max_len = tree[temp].max_len + len;
            }

            if (--tree[par].out == 0)
                q.push(par);
        }
        std::cout << cut_count << std::endl;
    }
};

class dTree2 {
private:
    Node* tree;
    int n, d, cut_count, qhead, qend;
    int* q;


    void push(int i)
    {
		q[qend] = i;
		qend++;
	}

	int pop()
	{
		int temp = q[qhead++];
		return temp;
	}



public:
    dTree2(int n, int d) : n(n), d(d), cut_count(0), qhead(0), qend(0)
    {
        tree = new Node[n];
        q = new int[n];
        tree[0].parent = -1;
        tree[0].length = 0;

        for (int i = 0; i < n; ++i) {
            int k;
            cin >> k;
            tree[i].max_len = 0;
            tree[i].out = k;
            tree[i].is_cut = false;
            for (int j = 0; j < k; ++j) {
                int id, w;
                cin >> id >> w;
                tree[id].parent = i;
                tree[id].length = w;
            }
        }
    }
	~dTree2() {}
    void solution()
    {
        for (int i = n - 1; i >= 0; --i) {
            if (tree[i].out == 0) push(i);
        }

        while (qhead != qend) {
            int temp = pop();
            int len = tree[temp].length;
            int par = tree[temp].parent;

            if (tree[par].is_cut == false && tree[temp].max_len + len > d) {
                tree[par].is_cut = true;
                par = tree[par].parent;
                cut_count++;
            } else if (tree[temp].is_cut == false && tree[par].max_len < tree[temp].max_len + len) {
                tree[par].max_len = tree[temp].max_len + len;
            }

            if (--tree[par].out == 0)
                push(par);
        }
        cout << cut_count << endl;
    }
};

int main() {
    int n, d;
    cin >> n >> d;
    dTree dt(n, d);
    dt.solution();
    return 0;
}

