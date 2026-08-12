class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxsum = INT_MIN;
        int cursum = 0;
        for(int x : nums){
            cursum += x;
            maxsum= max(cursum , maxsum);
            if(cursum <0){
                cursum =0;
            }
        }
        return maxsum;
    }
};