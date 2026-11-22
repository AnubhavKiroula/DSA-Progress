class Solution {
public:
    string convertToTitle(int n) {
        vector<int>v;
        int t=n;
        while(t>0){
            t--;
            int r= t%26;
            v.push_back(r);
            t=t/26;
        }
        string s="";
        for(int i=0;i<v.size();i++){
            s+= (char) (v[i]+65);
        }
        reverse(s.begin(), s.end());
        return s;
    }
};