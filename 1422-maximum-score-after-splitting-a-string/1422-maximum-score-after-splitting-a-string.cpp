class Solution {
public:
    int maxScore(string s) {
        int score = 0;
        string left = "";
        string right = s;
        for(int i=0;i<s.size()-1;++i){
            left += s[i];
            right = right.substr(1);
            int zero = 0;
            int one = 0;
            for(int j=0;j<left.size();++j){
                if(left[j] == '0') zero++;
            }
            for(int k=0;k<right.size();++k){
                if(right[k] == '1') one++;
            }
            int sc = one + zero;
            score = max(score,sc);
        }
        return score;
    }
};