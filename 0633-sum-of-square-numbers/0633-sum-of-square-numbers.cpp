class Solution {
public:
    bool judgeSquareSum(int c) {
        for(long long a = 0; a * a <= c; a++) {
            long long rem = c - a * a;

            long long b = sqrt(rem);

            if(b * b == rem)
                return true;
        }
        return false;
    }
};