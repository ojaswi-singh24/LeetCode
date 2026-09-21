class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        
        int n = nums.size();

        // dp[r] = number of subarrays ending at the previous index
        //         whose product % k == r
        vector<long long> dp(k, 0);

        // result[r] = total number of subarrays
        //              whose product % k == r
        vector<long long> result(k, 0);

        for (int num : nums) {

            vector<long long> newDp(k, 0);

            // Start a new subarray with only num
            int single = num % k;
            newDp[single]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {

                if (dp[r] == 0)
                    continue;

                int newRemainder = (r * single) % k;

                newDp[newRemainder] += dp[r];
            }

            // All subarrays ending at this position
            // contribute to the final answer
            for (int r = 0; r < k; r++) {
                result[r] += newDp[r];
            }

            // Move to the next position
            dp = newDp;
        }

        return result;
    }
};