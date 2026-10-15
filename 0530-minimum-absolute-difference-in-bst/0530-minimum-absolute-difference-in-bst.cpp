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
    void answer(TreeNode* root , int& ans){
        if(root->left != NULL){
            answer(root->left,ans);
        }
        if(prev!=NULL){
            ans = min(ans,abs(prev->val - root->val));
        }
        prev = root;
        if(prev->right != NULL){
            answer(prev->right,ans);
        }
    }
    int getMinimumDifference(TreeNode* root) {
        int ans = INT_MAX;
        answer(root,ans);
        return ans;
    }
};