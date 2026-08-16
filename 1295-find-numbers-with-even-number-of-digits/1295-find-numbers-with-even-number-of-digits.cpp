class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int ans =0;
        for(int i=0;i<nums.size();++i){
            int n = nums[i];
            int check =0;
            while(nums[i] > 0){
                int digit = nums[i]%10;
                nums[i] = nums[i]/10;
                check++;
            }
            if(check%2 == 0 ){
                ans++;
            }
        }
        return ans;
    }
};