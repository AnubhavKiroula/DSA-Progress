/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* create(TreeNode* root, int val) {
        TreeNode* node = new TreeNode();
        root = node;
        root->val = val;
        root->left = root->right = NULL;
        return root;
    }
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL)
            root = create(root, val);
        else {
            TreeNode* ptr = root;
            while (true) {
                if (val < ptr->val) {
                    if (ptr->left == NULL) {
                        ptr->left = new TreeNode(val);
                        break;
                    }
                    ptr = ptr->left;
                } else {
                    if (ptr->right == NULL) {
                        ptr->right = new TreeNode(val);
                        break;
                    }
                    ptr = ptr->right;
                }
            }
        }
        return root;
    }
};