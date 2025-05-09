#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        int len = len1 + len2;
        vector<int> nums(len);
        int i = 0, j = 0, k = 0;
        for (; j < len1 && k < len2; ++i) {
            if (nums1[j] < nums2[k]) {
                nums[i] = nums1[j++];
            } else {
                nums[i] = nums2[k++];
            }
        }
        while (j < len1) {
            nums[i] = nums1[j];
            ++i;
            ++j;
        }
        while (k < len2) {
            nums[i] = nums2[k];
            ++i;
            ++k;
        }
        return (len % 2 == 0) ? (nums[len / 2 - 1] + nums[len / 2]) / 2.0 : nums[len/2];
    }
};

int main() {
    Solution s;
    vector<int> nums1{1,2};
    vector<int> nums2{3,4};
    s.findMedianSortedArrays(nums1, nums2);
}
