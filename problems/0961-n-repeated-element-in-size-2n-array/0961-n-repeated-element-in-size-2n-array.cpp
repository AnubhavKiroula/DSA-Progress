class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int size = nums.size();
        int ans;
        int n = size/2;
        unordered_map<int,int> mpp;
        for(int x:nums){
            mpp[x]++;
        }
        for(auto it:mpp){
            if(it.second == n) ans=it.first;
        }
        return ans;
    }
};