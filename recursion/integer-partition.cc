#include <iostream>

class IntegerPartition {
private:
    static int partition(int n, int m) {
        if (n < 1 || m < 1) return 0;
        if (n == 1 || m == 1) return 1;

        if (n == m) return 1 + partition(n, m - 1);
        if (n < m) return partition(n, n);
        return partition(n, m - 1) + partition(n - m, m);
    }

public:
    static int partition(int n) {
        return partition(n, n);
    }
};


int main(int argc, char** argv) {
    size_t n = std::atoi(argv[1]);
    std::cout << IntegerPartition::partition(n) << std::endl;
    return 0;
}
