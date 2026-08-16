class Solution {
public:
    bool isPathCrossing(string path) {
        vector<int> chk = {0,0};
        map<vector<int>,int> mpp;
        mpp[chk]++;
        for(char c:path){
            if(c=='N'){
                chk[1]++;
                mpp[chk]++;
            }else if(c == 'S'){
                chk[1]--;
                mpp[chk]++;
            }else if(c == 'E'){
                chk[0]++;
                mpp[chk]++;
            }else{
                chk[0]--;
                mpp[chk]++;
            }
        }
        for(auto it:mpp){
            if(it.second>1) return true;
        }
        return false;
    }
};