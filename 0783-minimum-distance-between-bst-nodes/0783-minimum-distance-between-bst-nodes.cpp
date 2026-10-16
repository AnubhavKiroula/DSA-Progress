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
    TreeNode *prev = NULL;
    void sol(TreeNode *root , int& ans){
        if(root->left !=NULL){
            sol(root->left,ans);
        }
        if(prev != NULL){
            ans = min(ans,abs(prev->val - root->val));
        }
        prev = root;
        if(prev->right != NULL){
            sol(root->right,ans);
        }
    }
    int minDiffInBST(TreeNode* root) {
        int ans = INT_MAX;
        sol(root,ans);
        return ans;
    }
};