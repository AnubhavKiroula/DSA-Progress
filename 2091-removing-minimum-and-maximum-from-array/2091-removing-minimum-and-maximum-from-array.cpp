class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int ans;
        int minidx = min_element(nums.begin(),nums.end()) - nums.begin();
        int maxidx = max_element(nums.begin(),nums.end()) - nums.begin();
        if(minidx > maxidx) swap(minidx,maxidx);
        int front = maxidx+1;
        int back = n-minidx;
        int both = (minidx+1) + (n-maxidx);
        ans = min(front,back);
        ans = min(ans,both);
        return ans; 
    }
};