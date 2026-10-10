

class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();

        vector<int> diff(n);
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diff[i]);
        }

        if (k >= accumulate(diff.begin(), diff.end(), 0LL)) {
            return 0;
        }

        int left = 0, right = maxDiff;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long operations = 0;

            for (int d : diff) {
                if (d > mid) {
                    operations += d - mid;
                }
            }

            if (operations <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        long long ans = 0;

        for (int d : diff) {
            int reduced = min(d, left);
            ans += 1LL * reduced * reduced;
        }

        // Distribute any remaining operations to reduce
        // the squared sum further.
        long long used = 0;
        for (int d : diff) {
            if (d > left) {
                used += d - left;
            }
        }

        long long remaining = k - used;

        for (int i = 0; i < n && remaining > 0; i++) {
            if (diff[i] >= left && left > 0) {
                ans -= 2LL * left - 1;
                remaining--;
            }
        }

        return ans;
    }
};
