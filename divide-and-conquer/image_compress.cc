#include <iostream>

// p[1:n]  --   pixel
// b[1:n]  --   bits for each pixel in the segment
// l[1:m]  --   length (number of pixels) of the segment
// t[1:m]  --   t[i] = l[1] + l[2] + ... + l[i - 1]

// S[1:m]  --   segment, S[i] == p[(t[i] + 1):(t[i] + l[i])]
// h[1:m]  --   for p[k] in s[i], ceil(log(max{p[k] + 1}))
// s[1:n]  --   s[i] ==> bits needed to store p[1:i]

// bmax(i,j) -- for k in [i,j], ceil(log(max{p[k]} + 1))
// s[1:n]  -- for k in [1, min{i, 256}]
//              s[i] = min{s[i - k] + k * bmax(i - k + 1, i) + 11}


static int length_in_bits(int x)
{
    int len = 1;    // at least of length 1
    x >>= 1;
    while (x > 0) {
        x >>= 1;
        ++len;
    }
    return len;
}

// len[1:n]
// bits[1:n]
void compress(int n, int* p, int* s, int* len, int* bits)
{
    const int lmax = 255;
    const int header = 11;
    s[0] = 0;
    for (int i = 1; i <= n; ++i) {
        bits[i] = length_in_bits(p[i]);

        int k = 1, bmax = bits[i];
        int num_bits = s[i - k] + k * bmax;    // s[i]
        len[i] = k;
        for (k = 2; k <= i && k <= lmax; ++k) {
            if (bmax < bits[i - k + 1]) {
                bmax = bits[i - k + 1];
            }
            if (num_bits > s[i - k] + k * bmax) {
                num_bits = s[i - k] + k * bmax;
                len[i] = k;
            }
        }
        s[i] = num_bits + header;
    }
}

// l[m] == len[n], b[m] == bits[n]
// l[m - 1] == len[n - len[n]]
// b[m] == bits[n - len[n]]
void compress_traceback(int n, int* res, int* len, int* bits, int& m)
{
    if (n == 0) return;
    compress_traceback(n - len[n], res, len, bits, m);
    res[m++] = n - len[n];
}

void compress_output(int n, int* s, int* len, int* bits)
{
    std::cout << "The optimal value: " << s[n] << std::endl;
    int m = 0;
    compress_traceback(n, s, len, bits, m);
    s[m] = n;
    std::cout << "Segments: " << m << std::endl;
    for (int i = 1; i <= m; ++i) {
        int k = s[i];
        len[i] = len[k];
        bits[i] = bits[k];
    }
    for (int i = 1; i <= m; ++i) {
        std::cout << "Segment length: " << len[i] << " bits: "
            << bits[i] << std::endl;
    }
}
