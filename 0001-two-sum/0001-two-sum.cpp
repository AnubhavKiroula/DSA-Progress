class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> ans;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j){
                    continue;
                }
                if (nums[i] +nums[j] == target){
                    ans.emplace_back(i);
                    ans.emplace_back(j);
                    return ans;
                    break;
                }
            }
        }
        return ans;
    }
};