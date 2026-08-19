class Solution {
public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(auto x:matrix){
            set<int> st;
            for(int i=0;i<n;++i){
                st.insert(x[i]);
            }
            if( st.size() != n) return false;
        }
        for(int i=0;i<n;++i){
            set<int> ck;
            for(int x=0;x<n;++x){
                ck.insert(matrix[x][i]);
            }
            if(ck.size() != n) return false;
        }
        return true;
    }
};