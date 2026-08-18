class Solution {
public:
    bool areOccurrencesEqual(string s) {
        set<int> st;
        unordered_map<char,int> mpp;
        for(char c:s){
            mpp[c]++;
        }
        for(auto it:mpp){
            st.insert(it.second);
        }
        if(st.size() == 1) return true;
        return false;
    }
};