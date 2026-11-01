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
    int leftheight(TreeNode* root){
        int ht = 0;
        while(root != NULL){
            ht++;
            root = root->left;
        }
        return ht;
    }
    int rightheight(TreeNode* root){
        int ht = 0;
        while(root != NULL){
            ht++;
            root = root->right;
        }
        return ht;
    }
    int countNodes(TreeNode* root) {
        if(root == NULL) return 0;
        int lh = leftheight(root);
        int rh = rightheight(root);
        if(lh == rh) return pow(2,lh) -1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};