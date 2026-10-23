class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int k = (1 << 30) - 1;
        bool sorted = true;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) {
                sorted = false;
                k &= nums[i];
            }
        }

        return sorted ? 0 : k;
    }
};
