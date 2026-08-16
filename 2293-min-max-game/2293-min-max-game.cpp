class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        int n = nums.size();
        while(n>1){
            vector<int> temp(n/2);
            for(int i=0;i<n/2;++i){
                if(i%2 == 0){
                    temp[i] = min(nums[2*i],nums[2*i+1]);
                }else{
                    temp[i] = max(nums[2*i],nums[2*i+1]);
                }
            }
            nums = temp;
            n = n/2;
        }
        return nums[0];
    }
};