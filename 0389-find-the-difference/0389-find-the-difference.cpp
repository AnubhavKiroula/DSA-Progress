class Solution {
public:
    char findTheDifference(string s, string t) {
        unordered_map<char,int> mpp1,mpp2;
        for(char c1:s) mpp1[c1]++;
        for(char c2:t) mpp2[c2]++;
        for(auto it:mpp2){
            if(it.second> mpp1[it.first]) return it.first;        
        }
        return ' ';
    }
};