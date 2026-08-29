class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        set<int> st1(nums1.begin(), nums1.end());
        set<int> st2(nums2.begin(), nums2.end());
        set<int> st3(nums3.begin(), nums3.end());
        set<int> res;
        vector<int> ans;
        for(int x : st1) if(st2.count(x)) res.insert(x);
        for(int x : st2) if(st3.count(x)) res.insert(x);
        for(int x : st1) if(st3.count(x)) res.insert(x);
        for(int x : res) ans.push_back(x);
        return ans;
    }
};
