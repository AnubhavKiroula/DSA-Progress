class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;
        int n = nums.size();
        if(n==0){
            return 0;
        }
        for(int i=0;i<n;i++){
            st.insert(nums[i]);
        }
        int largest =1;
        int cnt=0;
        for(auto it : st){
            if(st.find(it-1) == st.end()){
                int x= it;
                cnt=1;
                while(st.find(x+1) != st.end()){
                    x= x+1;
                    cnt++;
                }
            }
            largest = max(largest,cnt);
        }
        return largest;
    }
};