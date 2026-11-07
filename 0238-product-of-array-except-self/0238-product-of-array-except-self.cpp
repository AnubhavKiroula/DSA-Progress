class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp1(n);
        vector<int> dp2(n);
        vector<int> ans(n);
        dp1[0] = 1;
        for (int i = 1; i < n; i++) {
            dp1[i] = dp1[i - 1] * nums[i - 1];
        }
        dp2[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            dp2[i] = dp2[i + 1] * nums[i + 1];
        }
        for(int i=0;i<n;++i){
            ans[i] = dp1[i]*dp2[i];
        }
        return ans;
    }
};