class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        vector<int> ans;
        for(int i=0;i<matrix.size();++i){
            for(int j=0;j<matrix.size();++j){
                ans.emplace_back(matrix[i][j]);
            }
        }
        sort(ans.begin() , ans.end());
        return ans[k-1];
    }
};