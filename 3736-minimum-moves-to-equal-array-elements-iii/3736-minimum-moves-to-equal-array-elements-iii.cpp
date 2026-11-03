class Solution {
public:
    int minMoves(vector<int>& nums) {
        int el = *max_element(nums.begin(),nums.end());
        int cnt = 0;
        for(int i=0;i<nums.size();++i){
            while(nums[i] != el){
                nums[i] = nums[i] + 1;
                cnt++;
            }
        }
        return cnt;
    }
};