#include <iostream>

int i = 0;

int eval(const char* expr);

int main()
{
    const char* expr = "* + 12 * / 48 2 - 26 9 50";
    int res = eval(expr);
    std::cout << res << std::endl;
    return 0;
}

int eval(const char* expr)
{
    while (expr[i] == ' ') ++i;

    // if (expr[i] == '+') {
    //     ++i;
    //     return eval(expr) + eval(expr);
    // }
    // if (expr[i] == '*') {
    //     ++i;
    //     return eval(expr) * eval(expr);
    // }

    switch (expr[i]) {
        case '+':
            i++;
            return eval(expr) + eval(expr);
        case '*':
            i++;
            return eval(expr) * eval(expr);
        case '-':
            i++;
            return eval(expr) - eval(expr);
        case '/':
            i++;
            return eval(expr) / eval(expr);
    }

    int x = 0;
    while (expr[i] >= '0' && expr[i] <= '9') {
        std::cout << (expr[i] - '0') << " ";
        x = 10 * x + (int)(expr[i++] - '0');
    }
    std::cout << "ret " << x << std::endl;
    return x;
}
