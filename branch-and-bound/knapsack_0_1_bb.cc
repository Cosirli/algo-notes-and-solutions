#include <vector>

class KnapsackPQBB {
private:
    static int n;
    static double capacity;    // weight limit
    static double cw;
    static double cp;
    static double up;    // upper bound of value
    static std::vector<double> w;
    static std::vector<double> p;

    static double bound(int i)
    {
        double cleft = capacity - cw;
        double b = cp;    // acquired value
        while (i <= n && w[i] <= cleft) {
            cleft -= w[i];
            b += p[i];
            i++;
        }
        if (i <= n)
            b += (p[i] / w[i]) * cleft;

        return b;
    }


public:
    static double max_knapsack()
    {

    }
};
