class Solution {
public:
    long long sumAndMultiply(int n) {
        long long sum_of_digits = 0;
        string non_zero_digits = "";
        
        // Extract digits from the integer
        while (n > 0) {
            int digit = n % 10;
            sum_of_digits += digit;
            
            if (digit != 0) {
                non_zero_digits += to_string(digit);
            }
            n /= 10;
        }
        
        // If there are no non-zero digits, return 0
        if (non_zero_digits.empty()) {
            return 0;
        }
        
        // Because we processed right-to-left, reverse the string to get the original order
        reverse(non_zero_digits.begin(), non_zero_digits.end());
        
        // Convert the concatenated string of non-zero digits back to a number
        long long x = stoll(non_zero_digits);
        
        return x * sum_of_digits;
    }
};