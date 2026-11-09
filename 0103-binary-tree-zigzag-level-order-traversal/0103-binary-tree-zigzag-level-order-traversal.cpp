/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> q;
        if(root== NULL) return ans;
        q.push(root);
        int flag = 0;
        while(!q.empty()){
            int size = q.size();
            vector<int> lev;
            for(int i=0;i<size;++i){
                TreeNode* node = q.front();
                q.pop();
                if(node->left != NULL) q.push(node->left);
                if(node->right != NULL) q.push(node->right);
                lev.push_back(node->val);
            }
            if(flag == 0){
                ans.emplace_back(lev);
                flag = 1;
            }else{
                reverse(lev.begin(),lev.end());
                ans.emplace_back(lev);
                flag = 0;
            }
        }
        return ans;
    }
};