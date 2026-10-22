
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int k = nums[0];

        bool inc = true, dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (k + i) % n)
                inc = false;

            if (nums[i] != (k - i + n) % n)
                dec = false;
        }

        int ans = INT_MAX;

        if (inc) {
            int a = (n - k) % n;
            ans = min(a, n - a + 2);
        }

        if (dec) {
            int a = (n - k - 1 + n) % n;
            ans = min(ans, 1 + min(a, n - a));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

