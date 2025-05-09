#include <iostream>

/**
 * Fact: Jan 1st 1 AD is a Monday in Gregorian calendar.
 * @return day in a week. 0 for Sunday, 1 for Monday, ..., 6 for Saturday
 */
int day_of_week(int y, int m, int d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int leap = y / 4 - y / 100 + y / 400;
    if (m < 3) --y;
    return (y + leap + t[m - 1] + d) % 7;
}

int dow(int y, int m, int d)
{
    y -= (m < 3);
    return (y + y / 4 - y / 100 + y / 400 + "bed=pen+mad."[m - 1] + d) % 7;
}

// driver
int main(int argc, char* argv[])
{
    int day = 17, month = 4, year = 2025;
    std::cin >> year >> month >> day;
    std::cout << day_of_week(year, month, day) << std::endl;
    std::cout << dow(year, month, day) << std::endl;
    return 0;
}
