class Solution {
public:
    string removeLeadingZeros(string &binary) {
        int pos = binary.find_first_not_of('0');
        return binary.substr(pos);
    }
    bool hasAlternatingBits(int n) {
        string binary = bitset<32>(n).to_string();
        string bin = removeLeadingZeros(binary);
        bool ans = true;
        for(int i=0;i<bin.size()-1;++i){
            if(bin[i] == bin[i+1]){
                ans = false;
                break;
            }
        }
        return ans;
    }
};