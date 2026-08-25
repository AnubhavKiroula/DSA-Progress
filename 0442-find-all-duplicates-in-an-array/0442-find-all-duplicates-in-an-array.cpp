class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ans;
        unordered_map<int,int> mpp;
        for(int x:nums) mpp[x]++;
        for(auto it:mpp){
            if(it.second == 2) ans.emplace_back(it.first);
        }
        return ans;
    }
};