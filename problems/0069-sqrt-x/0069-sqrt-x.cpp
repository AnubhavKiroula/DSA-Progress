class Solution {
public:
    int mySqrt(int x) {
      int low,mid,high;
      low = 0;
      high = x;
      while (low <=high){
        mid = (low+high)/2;
        long long m = (long long)mid*mid;
        if(m==x){
            return mid;
        }
        else if( m< x){
            low = mid +1;
        }
        else if(m > x){
            high = mid -1;
        }
      } 
      return high; 
    }
};