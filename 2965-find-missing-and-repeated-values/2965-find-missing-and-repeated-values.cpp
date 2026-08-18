class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> ans;
        vector<int> chk;
        vector<int> main;
        unordered_map<int,int> mpp;
        for(int i=1;i<= n*n;++i){
            main.emplace_back(i);
        }
        for(auto x:grid){
            for(auto y:x){
                mpp[y]++;
            }
        }
        for(auto it:mpp){
            chk.emplace_back(it.first);
            if(it.second > 1){
                ans.emplace_back(it.first);
            }
        }
        for(int i=0;i<main.size();++i){
            if(find(chk.begin(),chk.end(),main[i])==chk.end()){
                ans.emplace_back(main[i]);
            }
        }
        return ans;
    }
};