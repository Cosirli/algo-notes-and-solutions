#include <string>
#include <unordered_map>

using namespace std;

/*
Given a string s, find the length of the longest without duplicate characters.

Example:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. Notice that
the answer must be a substring, "pwke" is a subsequence and not a substr.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        int str_sz = s.size(), start = 0;
        std::unordered_map<char, int> seen;
        int longest_len = 0, len = 0;

        for (int end = 0; end != str_sz; ++end) {
            char ch = s[end];
            if (seen.count(ch) && seen[ch] >= start) {
                start = seen[ch] + 1;
            }
            seen[ch] = end;
            len = end - start + 1;
            longest_len = max(len, longest_len);
        }
        return longest_len;
    }

};
