class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        while(n>1){
            vector<int> temp(n-1);
            for(int i=0;i<n-1;++i){
                temp[i] = (nums[i] + nums[i+1])%10;
            }
            nums = temp;
            n--;
        }
        return nums[0];
    }
};