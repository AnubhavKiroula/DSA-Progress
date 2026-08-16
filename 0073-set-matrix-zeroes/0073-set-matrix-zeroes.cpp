class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> rowcnt(n);
        vector<int> colcnt(m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j] == 0){
                    rowcnt[i] = 1;
                    colcnt[j] = 1;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(rowcnt[i] ==1 || colcnt[j] == 1){
                    matrix[i][j] = 0;
                }
            }
        }
    }
};