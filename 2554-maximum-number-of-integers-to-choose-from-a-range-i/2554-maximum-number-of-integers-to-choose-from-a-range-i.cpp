class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
       vector<int> ans;
       int cnt =0,sum=0;
       unordered_set<int> st(banned.begin(),banned.end());
       for(int i=1;i<=n;++i){
        if(st.find(i) == st.end()) ans.emplace_back(i);
       }
       sort(ans.begin(),ans.end());
       for(int x:ans){
        if(sum + x <= maxSum){
            sum += x;
            cnt++;
        }else break;
       }
       return cnt;
    }
};