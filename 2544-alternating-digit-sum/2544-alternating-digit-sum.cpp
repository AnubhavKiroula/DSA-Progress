class Solution {
public:
    int alternateDigitSum(int n) {
        int sum=0;
        vector<int> num;
        while(n>0){
            int digit = n%10;
            n = n/10;
            num.emplace_back(digit);
        }
        for(int i=0;i<num.size();i++){
            if(num.size()%2 ==0){
                if(i%2 !=0){
                    sum += num[i];
                }else{
                    sum -= num[i];
                }
            }else{
                if(i%2 !=0){
                    sum -= num[i];
                }else{
                    sum += num[i];
                }
            }
        }
        return sum;
    }
};