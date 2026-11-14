class Solution {
public:
    vector<int> limitOccurrences(vector<int>& nums, int k) {
        vector<int> ans;
        map<int,int> mpp;
        for(int x:nums){
            mpp[x]++;
        }
        for(auto it:mpp){
            if(it.second == 1){
                ans.emplace_back(it.first);
            }else if(it.second <= k){
                for(int i=0;i<it.second;++i){
                    ans.emplace_back(it.first);
                }
            }else{
                for(int i=0;i<k;++i){
                    ans.emplace_back(it.first);
                }
            }
        }
        return ans;
    }
};