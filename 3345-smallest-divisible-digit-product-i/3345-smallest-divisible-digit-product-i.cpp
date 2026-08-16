class Solution {
public:
    int smallestNumber(int n, int t) {
        for(int i=n;;++i){
            int num = i;
            int digit_pro = 1;
            while(num>0){
                int digit = num%10;
                digit_pro = digit_pro*digit;
                num = num/10;
            }
            if(digit_pro % t == 0){
                return i;
            }
        }
    }
};