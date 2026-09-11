class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        unordered_set<int> st;
        int n = digits.size();
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                for(int k=0;k<n;++k){
                    if(i==j || j==k || i==k) continue;
                    int a = digits[i];
                    int b = digits[j];
                    int c = digits[k];
                    if(a == 0) continue;
                    if(c%2 != 0) continue;
                    int num = a*100+b*10+c;
                    st.insert(num);
                }
            }
        }
        return st.size();
    }
};