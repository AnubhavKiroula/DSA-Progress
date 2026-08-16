class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int max_pro = INT_MIN;
        int i=0;
        int n = nums.size()-1;
        sort(nums.begin() , nums.end());
        int high_pro = nums[n]*nums[n-1]*nums[n-2];
        int sec_high_pro = nums[n]*nums[i]*nums[i+1];
        max_pro = max(high_pro , sec_high_pro);
        return max_pro;
    }
};