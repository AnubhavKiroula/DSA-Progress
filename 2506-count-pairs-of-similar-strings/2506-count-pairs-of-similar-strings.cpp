class Solution {
public:
    int similarPairs(vector<string>& words) {
        int cnt = 0;
        int n = words.size();
        for(int i=0;i<n;++i){
            set<char> st1;
            for(char c:words[i]){
                st1.insert(c);
            }
            for(int j=i+1;j<n;++j){
                 set<char> st2;
                for(char x:words[j]){
                    st2.insert(x);
                }
                if(st1 == st2) cnt++;
            }
        }
        return cnt;
    }
};