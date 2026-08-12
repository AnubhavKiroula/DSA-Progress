class NumArray {
public:
    vector<int> pre;
    NumArray(vector<int>& nums) {
        pre.resize(nums.size());
        pre[0] = nums[0];
        for(int i=1;i<nums.size();i++){
            pre[i] = pre[i-1] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        
        int ans = pre[right];
        if(left > 0){
            ans -= pre[left-1];
        }
        
        return ans;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */