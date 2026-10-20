
class Solution {
public:
    bool check(vector<int>& nums, vector<int>& sortedNums, int k) {
        int n = nums.size();

        for (int start = 0; start < n; start += k) {
            unordered_map<int, int> freq;

            for (int j = start; j < start + k; j++) {
                freq[nums[j]]++;
                freq[sortedNums[j]]--;
            }

            for (auto& p : freq) {
                if (p.second != 0)
                    return false;
            }

            int descents = 0;

            for (int j = start; j < start + k - 1; j++) {
                if (nums[j] > nums[j + 1])
                    descents++;
            }

            if (descents > 1)
                return false;

            if (descents == 1 &&
                nums[start + k - 1] > nums[start])
                return false;
        }

        return true;
    }

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        int ans = 0;

        for (int k = 1; k <= n / k; k++) {
            if (n % k != 0)
                continue;

            if (check(nums, sortedNums, k))
                ans += k;

            int other = n / k;

            if (other != k && check(nums, sortedNums, other))
                ans += other;
        }

        return ans;
    }
};

