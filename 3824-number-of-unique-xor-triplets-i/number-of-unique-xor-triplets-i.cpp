class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        
        // Base cases for small arrays
        if (n < 3) {
            return n;
        }
        
        // Find the number of bits required to represent `n`
        // std::__lg(n) returns the index of the highest set bit (0-indexed)
        int bit_length = std::__lg(n) + 1;
        
        // Total possible unique XOR values is 2^(bit_length)
        return 1 << bit_length;
    }
};