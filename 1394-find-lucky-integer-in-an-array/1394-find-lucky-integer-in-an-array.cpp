class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int,int> mpp;
        int ans=0;
        for(int x:arr) mpp[x]++;
        for(auto it:mpp){
            if(it.first == it.second) ans=max(ans,it.first);
        }
        if(ans ==0) return -1;
        else return ans;
    }
};