class Solution {
public:
    int distinctAverages(vector<int>& nums) {
        set<double> st;
        sort(nums.begin(),nums.end());
        int i=0,j=nums.size()-1;
        while(i<j){
            double avg = (nums[i] + nums[j])/2.0;
            st.insert(avg);
            i++;
            j--;
        }
        return st.size();
    }
};