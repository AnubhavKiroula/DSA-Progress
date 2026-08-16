class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int cnt=0;
        unordered_map<char,int> mpp;
        for(char x:jewels){
            mpp[x]++;
        }
        for(char y:stones){
            if(mpp[y] ==1){
                cnt++;
            }
        }
        return cnt;
    }
};