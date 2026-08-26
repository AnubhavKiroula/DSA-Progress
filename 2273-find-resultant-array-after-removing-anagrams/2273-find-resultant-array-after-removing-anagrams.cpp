class Solution {
public:
    bool IsAnagram(string& s1 , string& s2){
        unordered_map<char,int> st1,st2;
        for(char c: s1) st1[c]++;
        for(char c: s2) st2[c]++;
        if(st1==st2) return true;
        return false;
    }
    vector<string> removeAnagrams(vector<string>& words) {
        for(int i=1;i<words.size();++i){
            if(IsAnagram(words[i] , words[i-1])){
                words.erase(words.begin() + i);
                i=i-1;
            }
        }
        return words;
    }
};