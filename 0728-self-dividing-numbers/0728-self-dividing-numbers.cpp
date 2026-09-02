class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ans;
        for(int i=left;i<=right;++i){
            int n = i;
            int flag = 1;
            while(n>0){
                int digit = n%10;
                if(digit == 0 || i%digit != 0){
                    flag =-1;
                    break;
                }
                n=n/10;
            }
            if(flag == 1) ans.emplace_back(i);
        }
        return ans;
    }
};