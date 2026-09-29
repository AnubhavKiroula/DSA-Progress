class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int start=0, end=n-1 , left =-1, right =-1;
        while(start<=end){
            int mid = start +(end-start)/2;
            if(nums[mid] == target){
                left = mid;
                end = mid-1;
            }else if(nums[mid] < target) start = mid +1;
            else end = mid -1;
        }
        start=0;
        end=n-1;
        while(start<=end){
            int mid = start +(end-start)/2;
            if(nums[mid] == target){
                right = mid;
                start = mid+1;
            }else if(nums[mid] < target) start = mid +1;
            else end = mid -1;
        }
        vector<int> ans = {left,right};
        return ans;
    }
};