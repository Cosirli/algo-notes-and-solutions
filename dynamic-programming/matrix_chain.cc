#include <iostream>

class Matrix {
private:
    int** mat_;
    size_t row_;
    size_t col_;

    static int chain_lookup(int p[], size_t mats_len,
                     size_t** m, size_t** split, int i, int j)
    {
        if (m[i][j] > 0) return m[i][j];
        int k = i;
        m[i][j] = 0 + chain_lookup(p, mats_len, m, split, k + 1, j) + p[i - 1] * p[k] * p[j];
        split[i][j] = k;
        for (k = i + 1; k < j; ++k) {
            int tmp = chain_lookup(p, mats_len, m, split, i, k)
                + chain_lookup(p, mats_len, m, split, k + 1, j)
                + p[i - 1] * p[k] * p[j];
            if (tmp < m[i][j]) {
                m[i][j] = tmp;
                split[i][j] = k;
            }
        }
        return m[i][j];
    }
public:
    Matrix(size_t p_row, size_t p_col) : row_(p_row), col_(p_col)
    {
        mat_ = new int*[row_];
        for (size_t i = 0; i < row_; ++i) {
            mat_[i] = new int[col_];
        }
    }

    ~Matrix()
    {
        for (size_t i = 0; i < row_; ++i) {
            delete[] mat_[i];
        }
        delete mat_;
    }

    static int matrix_chain_rec(int p[], size_t mats_len,
                     size_t** m, size_t** split, int i, int j)
    {
        if (i == j) return 0;
        int k = i;
        m[i][j] = 0 + matrix_chain_rec(p, mats_len, m, split, i + 1, j) + p[i - 1] * p[k] * p[j];
        split[i][j] = k;
        for (k = i + 1; k < j; ++k) {
            int tmp = matrix_chain_rec(p, mats_len, m, split, i, k)
                + matrix_chain_rec(p, mats_len, m, split, k + 1, j)
                + p[i - 1] * p[k] * p[j];
            if (tmp < m[i][j]) {
                m[i][j] = tmp;
                split[i][j] = k;
            }
        }
        return m[i][j];
    }

    static void matrix_chain_dp(int p[], size_t mats_len,
                     size_t** m, size_t** split)
    {
        int n = mats_len - 1;
        for (int i = 1; i <= n; ++i) m[i][i] = 0;

        // d: dist   i: start   k: end (innermost loop)
        for (int d = 1; d <= n - 1; ++d) {
            for (int i = 1; i <= n - d; ++i) {
                int j = i + d;   // End of k marked by j

                // split between m[k] and m[k + 1]
                int k = i;
                m[i][j] = 0 + m[k + 1][j] + p[i - 1] * p[k] * p[j];  // k == i, m[i][k] == 0
                split[i][j] = k;
                for (k = i + 1; k < j; ++k) {
                    int tmp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (tmp < m[i][j]) {
                        m[i][j] = tmp;
                        split[i][j] = k;
                    }
                }
            }
        }
    }

    static int matrix_chain_memoized(int p[], size_t mats_len,
                     size_t** m, size_t** split, int i, int j)
    {
        int n = mats_len - 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                m[i][j] = 0;
            }
        }
        return chain_lookup(p, mats_len, m, split, i, j);
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b);

    int* operator[](size_t i)
    {
        return mat_[i];
    }

    int* operator[](size_t i) const
    {
        return mat_[i];
    }
};

Matrix operator*(const Matrix& a, const Matrix& b)
{
    Matrix c(a.row_, b.col_);
    for (size_t i = 0; i < a.row_; ++i) {
        for (size_t j = 0; j < b.col_; ++j) {
            int sum = 0;
            for (size_t k = 0; k < a.col_; ++k) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
    return c;
}

int main()
{
    Matrix matrices[6]{{30, 35}, {35, 15}, {15, 5}, {5, 10}, {10, 20}, {20, 25}};
    std::cout << std::endl;
    return 0;
}
