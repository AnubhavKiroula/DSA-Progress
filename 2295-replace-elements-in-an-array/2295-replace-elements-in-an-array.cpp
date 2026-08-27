class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        unordered_map<int,int> mpp;
        for(int i=0;i<nums.size();++i) mpp[nums[i]] = i;
        for(auto it:operations){
            int index = mpp[it[0]];
            nums[index] = it[1];
            mpp[it[1]] = index;
        }
        return nums;
    }
};