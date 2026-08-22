class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int  n=nums.size();
        if(n<= 1) return 0;
        int sum = nums[0] + nums[1];
        int cnt =1;
        for(int i=2;i<n;i=i+2){
            if(nums[i]+nums[i+1] == sum){
                cnt++;
            }else break;
        }
        return cnt;
        
    }
};