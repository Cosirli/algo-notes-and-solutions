#include <iostream>
#include <utility>
#include <vector>

template<typename T>
class Perm {
private:
    static void perm(std::vector<T>& list, size_t begin, size_t end) {
        if (begin == end) {
            for (T item : list) std::cout << item << " ";
            std::cout << std::endl;
            return;
        }
        for (size_t i = begin; i <= end; ++i) {
            std::swap(list[begin], list[i]);
            perm(list, begin + 1, end);
            std::swap(list[begin], list[i]);
        }
    }
public:
    static void perm(std::vector<T>& list) {
        perm(list, 0, list.size() - 1);
    }
};


int main(int argc, char** argv) {
    size_t length = std::atoi(argv[1]);
    std::vector<int> vec(length);
    for (size_t i = 0; i < length; ++i) {
        vec[i] = i + 1;
    }
    Perm<int>::perm(vec);
    return 0;
}
