class Solution {
public:
    vector<int> evenOddBit(int n) {
        vector<int> ans;
        int even =0;
        int odd = 0;
        bitset<10> bin(n);
        for(int i=0;i<bin.size();++i){
            if(bin[i] == 1 && i%2 == 0){
                even++;
            }else if(bin[i] == 1 && i%2 != 0){
                odd++;
            }
        }
        ans.emplace_back(even);
        ans.emplace_back(odd);
        return ans;
    }
};