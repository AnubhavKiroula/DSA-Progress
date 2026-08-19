class Solution {
public:
    int longestValidParentheses(string s) {
        int l=0 , r=0 , len=0;
        for(char c:s){
            if(c== '(') l++;
            else r++;
            if(l==r){
                len = max(len,l+r);
            }
            else if(r>l) {
                r=0;
                l=0;
            }
        }
        l=0;
        r=0;
        for(int i=s.size()-1;i>=0;--i){
            if(s[i]== '(') l++;
            else r++;
            if(l==r){
                len = max(len,l+r);
            }
            else if(l>r) {
                r=0;
                l=0;
            }
        }
        return len;
    }
};