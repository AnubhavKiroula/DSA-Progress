class Solution {
public:
    string customSortString(string order, string s) {
        unordered_map<char,int> m;  
        string st,kl;
        for(int i=0;i<s.size();i++){ 
            m[s[i]]++;
        }
        for(int i=0;i<order.size();i++){
        st+=string(m[order[i]],order[i]); 
        m[order[i]]=0;  
        }
        for(auto ele:m){  
            if(ele.second>=1)
            kl+=string(ele.second,ele.first);

        }
        st+=kl;  
        return st;
        
    }
};