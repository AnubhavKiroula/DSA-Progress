class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        unordered_map<string,int> mpp1, mpp2;
        for(string &s : words1) mpp1[s]++;
        for(string &s : words2) mpp2[s]++;
        
        int cnt = 0;
        for(auto &it : mpp1){
            if(it.second == 1 && mpp2[it.first] == 1){
                cnt++;
            }
        }
        return cnt;
    }
};
