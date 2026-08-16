class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.size();
        unordered_set<char> st;
        int start=0;
        int maxlen = 0;
        for(int end=0;end<n;++end){
            while(st.count(s[end])){
                st.erase(s[start]);
                start++;
            }
            st.insert(s[end]);
            maxlen = max(maxlen , end-start+1);
        }
        return maxlen;
    }
};