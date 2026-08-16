class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> mpp;
        vector<int> ans;
        vector<int> check;
        for(int i=1;i<=n;++i){
            check.emplace_back(i);
        }
        for(int x : nums){
            mpp[x]++;
        }
        for(auto it:mpp){
            if(it.second > 1){
                ans.emplace_back(it.first);
            }
        }
        for(int y:check){
            mpp[y]--;
        }
        for(auto it:mpp){
            if(it.second < 0){
                ans.emplace_back(it.first);
            }
        }
        return ans;
    }
};