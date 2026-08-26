class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> st(nums.begin(),nums.end());\
        int i=1;
        while(true){
            if(st.find(k*i) == st.end()){
                return k*i;
                break;
            }else i++;
        }
        return 0;
    }
};