class Solution {
public:
    void RotateMat(vector<vector<int>>& mat){
            int n = mat.size();
            for(int i=0;i<n-1;i++){
                for(int j=i+1;j<n;j++){
                    swap(mat[i][j] , mat[j][i]);
                }
            }
            for(int i=0;i<n;i++){
                reverse(mat[i].begin() , mat[i].end());
            }
    }
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n=mat.size();
        for(int i=0;i<4;++i){
            if(mat == target){
                return true;
            }else{
                RotateMat(mat);
            }
        }
        return false;
    }
};