class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n= nums.size();
        int sum;
        vector<int> arr[2];
    
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                sum=nums[i]+nums[j];
                if (sum == target){
                    return {i,j};
                }
            }
        }
        return {};
        
    }
};