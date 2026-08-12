class Solution {
public:
    bool isAdjacentDiffAtMostTwo(string s) {
        for(int i=0;i<s.size() -1 ;++i){
            int diff = abs(s[i] - s[i+1]);
            if(diff > 2) return false;
        }
        return true;
    }
};