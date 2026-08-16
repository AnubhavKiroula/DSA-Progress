class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;
        for(int n : nums){
            string s = to_string(n);
            for(char c : s){
                ans.push_back(c-'0');
            }
        }
        return ans;
    }
};