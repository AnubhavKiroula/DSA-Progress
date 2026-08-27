class Solution {
public:
    int maxDifference(string s) {
        int odd=0,even=INT_MAX;
        unordered_map<char,int> mpp;
        for(char c:s) mpp[c]++;
        for(auto it:mpp){
            if(it.second %2 == 0) 
                even = min(even , it.second);
            else
                odd = max(odd,it.second);
        }
        return odd-even;
    }
};