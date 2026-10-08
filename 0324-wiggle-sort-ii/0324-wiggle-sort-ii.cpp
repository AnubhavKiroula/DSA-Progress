class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> s=nums;
        sort(s.begin() , s.end());
        int small = (n+1)/2 -1;
        int large = n-1;
        for(int i=0;i<n;++i){
            if(i%2 == 0){
                nums[i] = s[small];
                small--;
            }else{
                nums[i] = s[large];
                large--;
            }
        }
    }
};