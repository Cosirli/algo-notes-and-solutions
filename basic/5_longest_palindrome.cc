#include <string>

using namespace std;

class Solution {
private:
    bool isParlindrome(const string& s, int p, int r)
    {
        while (p < r) {
            if (s[p] != s[r]) {
                return false;
            }
            p++;
            r--;
        }
        return true;
    }
public:
    string longestPalindrome(string s)
    {
        int start;
        int str_len = s.length();
        int longest_len = 1;
        for (int i = 0; i < str_len; ++i) {
            for (int j = i; j < str_len; ++j) {
                if (!isParlindrome(s, i, j)) {
                    continue;
                }
                int len = j - i + 1;
                if (len > longest_len) {
                    longest_len = len;
                    start = i;
                }
            }
        }
        return s.substr(start, longest_len);
    }
};
