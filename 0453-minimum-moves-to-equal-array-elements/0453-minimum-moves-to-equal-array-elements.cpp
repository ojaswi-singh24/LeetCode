class Solution {
public:
    int minMoves(vector<int>& nums) {

        int n = nums.size();

        int minVal = *min_element(nums.begin(), nums.end());

        int sum = 0;

        for (int x : nums) {
            sum += x;
        }

        return sum - (n * minVal);
    }
};