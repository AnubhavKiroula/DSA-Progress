class Solution {
public:
    //USING BUBBLE SORT..
    vector<int> sortEvenOdd(vector<int>& nums) {
        // for even
        int n = nums.size();
        for(int i=n-1;i>=1;i= i-1){
            for(int j = 0;j+2<n;j=j+2){
                if(nums[j]>nums[j+2]){
                    swap(nums[j],nums[j+2]);
                }
            }
        }
        //for odd
        for(int i=n-1;i>=1;i=i-1){
            for(int j=1;j+2<n;j=j+2){
                if(nums[j]<nums[j+2]){
                    swap(nums[j],nums[j+2]);
                }
            }
        }
        return nums;
    }
};