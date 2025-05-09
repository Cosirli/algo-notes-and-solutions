class Triangulation {
private:
    int* edges_;
public:

    int weight(int i, int j, int k)
    {
        return edges_[i] * edges_[j] + edges_[j] * edges_[k] + edges_[i] * edges_[k];
    }

    void min_weight_triangulate(int n, int** t, int** s)
    {
        for (int i = 1; i <= n; ++i) t[i][i] = 0;

        for (int d = 1; d <= n - 1; ++d) {
            for (int i = 1; i <= n - d; ++i) {
                int j = i + d;

                int k = i;
                t[i][j] = 0 + t[i + 1][j] + weight(i - 1, j, k);
                s[i][j] = k;
                for (k = i + 1; k < j; ++k) {
                    int tmp = t[i][k] + t[k + 1][j] + weight(i - 1, j, k);
                    if (tmp < t[i][j]) {
                        t[i][j] = tmp;
                        s[i][j] = k;
                    }
                }
            }
        }
    }

};
