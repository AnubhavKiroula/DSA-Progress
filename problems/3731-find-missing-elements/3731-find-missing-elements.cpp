class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        sort(nums.begin(),nums.end());
        int n = nums.size();
        int max = nums[n-1];
        int min = nums[0];
        for(int i=min;i<=max;i++){
            auto it = find(nums.begin() , nums.end() , i);
            if(it == nums.end()){
                ans.emplace_back(i);
            }
        }
        sort(ans.begin() , ans.end());
        return ans;
    }
};