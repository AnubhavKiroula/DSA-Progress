class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        unordered_map<int,int> mpp;
        for(int x:nums){
            if(x%2== 0) mpp[x]++;
        }
        int cnt=0;
        int ans = INT_MAX;
        for(auto& it:mpp){
            if(it.second > cnt){
                cnt = it.second;
                ans=it.first;
            } 
            else if(it.second == cnt) ans = min(ans,it.first);
        }
        if(ans == INT_MAX) return -1;
        return ans;
    }
};