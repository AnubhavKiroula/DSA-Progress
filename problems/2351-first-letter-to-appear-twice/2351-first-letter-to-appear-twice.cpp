class Solution {
public:
    char repeatedCharacter(string s) {
        unordered_set<int> st;
        char ans;
        for(int i=0;i<s.size();++i){
            if(st.find(s[i]) != st.end()){
                ans= s[i];
                break;
            }else{
                st.insert(s[i]);
            }
        }
        return ans;
    }
};