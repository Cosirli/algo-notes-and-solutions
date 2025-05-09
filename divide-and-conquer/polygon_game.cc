#include <cstdlib>

// op[1], v[1], op[2], v[2], ..., op[n], v[n]
//
// p(i,j): v[i], op[i + 1], ... , v[i + j - 1].    length: j
//
// op[i + s], 1 <= s <= j - 1  ==> p(i,s) and p(i + s, j - s)
//
class PolygonGame {
private:
    int** m[2];
    int n;
    int* v;
    char* op;

public:
    int poly_max()
    {
        poly_init();
        int minf, maxf;
        for (int j = 0; j <= n; ++j) {
            for (int i = 1; i <= n; ++i) {
                for (int s = 1; s <= j - 1; ++s) {
                    min_max(i, s, j, minf, maxf);
                    m[i][j][0] = (minf > m[i][j][0]) ? m[i][j][0] : minf;
                    m[i][j][1] = (maxf < m[i][j][1]) ? m[i][j][1] : maxf;
                }
            }
        }

        int temp = m[1][n][1];
        for (int i = 2; i <= n; ++i)
            temp = (m[i][n][1] > temp) ? m[i][n][1] : temp;
        return temp;
    }

    void min_max(int i, int s, int j, int& minf, int& maxf)
    {
        int a = m[i][i+s][0], b = m[i][i+s][1];
        int r = (i + s - 1) % n + 1;
        int c = m[r+s][j-s][0], d=m[r+s][j-s][1];

        if (op[r] == '+') {
            minf = a + c;
            maxf = b + d;
        } else if (op[r] == '*') {
            int e[4] = {a*c, a*d, b*c, b*d};
            int tmin = e[0], tmax = e[0];
            for (int k = 1; k < 4; ++k) {
                tmin = (tmin > e[k]) ? e[k] : tmin;
                tmax = (tmax > e[k]) ? e[k] : tmax;
            }
            minf = tmin;
            maxf = tmax;
        } else {
            exit(-1);
        }
    }

    void poly_init()
    {
        for (int i = 1; i <= n; ++i) {
            m[i][1][0] = v[i];
            m[i][1][1] = v[i];
        }
    }

};
