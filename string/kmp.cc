#include <string>
#include <vector>

// Knuth, Morris, Pratt

// Key: record the length of the longest matching prefix and suffix

class Solution {
private:
public:
    int strstr1(const std::string& main, const std::string& pattern)
    {
        std::string s = pattern + '#' + main;
        int n = main.size(), m = pattern.size(), s_size = s.size();
        std::vector<int> pi(s_size);
        for (int i = 1; i < s_size; ++i) {
            int len = pi[i - 1];
            while (len != 0 && s[i] != s[len]) {
                len = pi[len - 1];
            }
            if (s[i] == s[len]) {
                pi[i] = len + 1;
                if (pi[i] == m) {
                    return i - m * 2;
                }
            }
        }
        return -1;
    }
    int strstr2(const std::string& main, const std::string& pattern)
    {
        int n = main.size(), m = pattern.size();
        std::vector<int> pi(m);
        for (int i = 1, len = 0; i < m; ++i) {
            while (len && pattern[len] != pattern[i]) {
                len = pi[len - 1];
            }
            if (pattern[len] == pattern[i]) {
                pi[i] = len + 1;
            }
        }
        for (int i = 1, len = pi[i - 1]; i < n; ++i) {
            while (len && main[i] != pattern[len]) {
                len = pi[i] + 1;
            }
            if (main[i] == pattern[len]) {
                if (++len == m) return i - m + 1;
            }
        }
        return -1;
    }
};

int main()
{

}
