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
    void inorder(TreeNode* root , vector<int>& nums){
        if(root == nullptr) return;
        inorder(root->left,nums);
        nums.emplace_back(root->val);
        inorder(root->right,nums);
    }
    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        inorder(root , nums);
        int n = nums.size();
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(i == j) continue;
                if(nums[i] + nums[j] == k) return true;
            }
        }
        return false;
    }
};