class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        vector<int> ans;
        for(int i=0;i<nums.size();++i){
            int max = *max_element(nums.begin() , nums.begin() + i + 1);
            int min = *min_element(nums.begin() + i , nums.end());
            int score = max -min;
            if(score <=k) ans.emplace_back(i);
        }
        if(ans.size() == 0) return -1;
        return *min_element(ans.begin() , ans.end());
    }
};