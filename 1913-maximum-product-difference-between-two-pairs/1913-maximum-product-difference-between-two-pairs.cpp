class Solution {
public:
    int maxProductDifference(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        int a,b,c,d;
        a = nums[n-1];
        b = nums[n-2];
        c= nums[0];
        d = nums[1];
        return (a*b)-(c*d);
    }
};