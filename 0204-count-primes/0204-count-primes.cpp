class Solution {
public:
    int countPrimes(int n) {
        if (n < 3) {
            return 0;
        }
        bool isprime[n];

        memset(isprime, true, n);

        int result = n / 2;
        for (int i = 3; i * i < n; i += 2) {
            if (isprime[i]) {
                int d = i * 2;
                for (int j = i * i; j < n; j += d) {
                    if (isprime[j]) {
                        isprime[j] = false;
                        result--;
                    }
                }
            }
        }
        return result;
    }
};