class Solution {
public:
    bool check(vector<int>& nums) {
        int dip = 0;
        int n = nums.size();
        for(int i=0 ; i<n-1;i++){
            if(nums[i] > nums[i+1]){
                dip++;
            }
        }
        if (nums[0] < nums[n-1]){
            dip++;
        }
        return dip<=1;
    }
};