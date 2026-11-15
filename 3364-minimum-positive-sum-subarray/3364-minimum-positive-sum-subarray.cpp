class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int min_sum = INT_MAX;
        for(int i=l;i<=r;++i){
            for(int j=0;j+i<=nums.size();++j){
                int sum = 0;
                for(int k=j;k<j+i;++k){
                    sum += nums[k];
                }
                if(sum >0){
                    min_sum = min(min_sum,sum);
                }
            }
        }
        if(min_sum != INT_MAX) return min_sum;
        return -1;
    }
};