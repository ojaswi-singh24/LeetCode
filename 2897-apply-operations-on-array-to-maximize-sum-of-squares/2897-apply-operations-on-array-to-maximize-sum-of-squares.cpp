
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;
        vector<long long> ans(k, 0);

        // Count how many numbers contain each bit
        for (int bit = 0; bit < 32; bit++) {
            int count = 0;

            for (int num : nums) {
                if (num & (1LL << bit)) {
                    count++;
                }
            }

            // Distribute this bit among the k numbers
            for (int i = 0; i < min(count, k); i++) {
                ans[i] |= (1LL << bit);
            }
        }

        long long result = 0;

        for (long long num : ans) {
            result = (result + num * num) % MOD;
        }

        return result;
    }
};
