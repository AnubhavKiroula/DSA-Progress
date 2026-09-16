class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        long long maxi = INT_MIN;
        for(int i=0;i<n-2;++i){       
            for(int j=i+1;j<n-1;++j){
                for(int k=j+1;k<n;++k){
                    long long val = nums[i] - nums[j];
                    val = val*nums[k];
                    maxi = max(maxi,val);
                }
            }
        }
        if(maxi <= 0) return 0;
        return maxi;
    }
};