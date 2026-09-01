class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        for(int x:nums1){
            auto it = find(nums2.begin() , nums2.end() , x);
            int idx = distance(nums2.begin(),it);
            int next = -1;
            for(int j=idx+1;j<nums2.size();++j){
                if(nums2[j] > nums2[idx]){
                    next = nums2[j];
                    break;
                }
            }
            ans.emplace_back(next);
        }
        return ans;
    }
};