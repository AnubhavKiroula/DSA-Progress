class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double winsum = 0;
        double maxavg = INT_MIN;
        for(int i=0;i<k;++i){
            winsum += nums[i];
        }
        maxavg = winsum/k;
        for(int i=k;i<nums.size();++i){
            winsum +=nums[i];
            winsum -= nums[i-k];
            double winavg = winsum/k;
            maxavg = max(maxavg,winavg);
        }
        return maxavg;
    }
};