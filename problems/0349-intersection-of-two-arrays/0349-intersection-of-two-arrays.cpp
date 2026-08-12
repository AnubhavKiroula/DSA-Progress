class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int n1=nums1.size();
        int n2 = nums2.size();
        set<int> st;
        int ran = min(n2,n1);
        for(int i=0;i<ran;++i){
            if(n1<n2){
                if(find(nums2.begin() , nums2.end(), nums1[i]) != nums2.end()){
                    st.insert(nums1[i]);
                }
            }else{
                if(find(nums1.begin() , nums1.end(), nums2[i]) != nums1.end()){
                    st.insert(nums2[i]);
                }
            }
        }
        vector<int> ans(st.begin() , st.end());
        return ans;
    }
};