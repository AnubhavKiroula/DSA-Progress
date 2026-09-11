class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int cnt = 0;
        unordered_set<char> all(allowed.begin(), allowed.end());
        for(auto w : words){
            bool chk = true;
            for(char c : w){
                if(all.find(c) == all.end()){
                    chk = false;
                    break;
                }
            }
            if(chk) cnt++;
        }
        return cnt;
    }
};
