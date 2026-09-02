class Solution {
public:
    int countDigits(int num) {
        int temp = num;
        int cnt = 0;
        while(temp >0){
            int dig = temp%10;
            if(dig == 0) continue;
            if(num%dig ==0) cnt++;
            temp = temp/10;
        }
        return cnt;
    }
};