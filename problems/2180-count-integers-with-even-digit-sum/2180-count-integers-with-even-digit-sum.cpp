class Solution {
public:
    int countEven(int num) {
        int count=0;
        for(int i=1;i<=num;i++){
            int m =i;
            int sum = 0;
            while(m>0){
                    sum += m%10;
                    m = m/10;
            }
            if (sum%2 == 0){
                count++;
            }  
        }
        return count;
    }
};