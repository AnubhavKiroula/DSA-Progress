class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> ans;
        for(int i=0;i<words.size();++i){
            bool chk = false;
            for(char c:words[i]){
                if(c == x){
                    chk = true;
                    break;
                }
            }
            if(chk == true) ans.emplace_back(i);
        }
        return ans;
    }
};