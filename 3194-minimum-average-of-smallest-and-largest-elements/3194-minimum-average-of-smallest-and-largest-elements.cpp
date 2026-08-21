class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        int n = nums.size();
        vector<double> ans;
        sort(nums.begin(),nums.end());
        int k=1,i=0,j=n-1;
        while(k<=n/2){
            double avg = (nums[i]+nums[j])/2.0;
            ans.emplace_back(avg);
            i++;
            j--;
            k++;
        }
        return *min_element(ans.begin(),ans.end());
    }
};