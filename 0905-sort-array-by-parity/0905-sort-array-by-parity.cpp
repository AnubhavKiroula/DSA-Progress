class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int n = nums.size();
        int left =0 , right=n-1;
        while(left<=right){
            if(nums[left] %2 == 0){
                left++;
            }else{
                swap(nums[left],nums[right]);
                right--;
            }
        }
        return nums;
    }
};