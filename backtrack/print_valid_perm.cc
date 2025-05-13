#include <iostream>
#include <cstring>

static int sum = 0;

static bool valid(char list[], int i, int m)
{
    if (i == m) return true;
    for (int j = i + 1; j <= m; ++j)
        for (int k = j + 1; k <= m; ++k)
            if (list[j] == list[k]) return false;
    return true;
}

static void backtrack(char list[], int k, int m)
{
    if (k > m) {
        for (int i = 0; i <= m; ++i)
            std::cout << list[i];
        std::cout << std::endl;
        sum++;
        return;
    }

    for (int i = k; i <= m; ++i) {
        std::swap(list[i], list[k]);
        if (valid(list, i, m)) {
            backtrack(list, k + 1, m);
        }
        std::swap(list[i], list[k]);
    }
}

int main()
{
    char list[] = "acc";
    backtrack(list, 0, strlen(list) - 1);
    std::cout << sum << std::endl;
    return 0;
}
