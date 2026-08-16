class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        vector<int> ans;
        unordered_map<int,int> mpp;
        for(int x:arr){
            mpp[x]++;
        }
        for(auto it:mpp){
            ans.emplace_back(it.second);
        }
        sort(ans.begin() , ans.end());
        for(int i=0;i<ans.size()-1;++i){
            if(ans[i] == ans[i+1]) return false;
        }
        return true;
    }
};