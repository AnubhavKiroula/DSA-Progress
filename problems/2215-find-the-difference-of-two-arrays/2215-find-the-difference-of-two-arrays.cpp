class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> ans;
        unordered_set<int> first;
        unordered_set<int> second;
        for(int x:nums1){
            if(count(nums2.begin() , nums2.end() , x) == 0){
                first.insert(x);
            }
        }
        ans.emplace_back(first.begin(), first.end());
        for(int y:nums2){
            if(count(nums1.begin() , nums1.end() , y) == 0){
                second.insert(y);
            }
        }
        ans.emplace_back(second.begin() , second.end());
        return ans;
    }
};