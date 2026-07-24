#include <vector>
#include <algorithm>

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        // Step 1: Collect all unique numbers present in nums
        std::vector<int> U;
        std::vector<bool> seen_u(2048, false);
        for (int x : nums) {
            if (!seen_u[x]) {
                seen_u[x] = true;
                U.push_back(x);
            }
        }

        // Step 2: Find all unique pair XOR values (a ^ b)
        std::vector<bool> P(2048, false);
        for (size_t i = 0; i < U.size(); ++i) {
            for (size_t j = i; j < U.size(); ++j) {
                P[U[i] ^ U[j]] = true;
            }
        }

        // Step 3: Compute all unique triplet XOR values (p ^ c)
        std::vector<bool> T(2048, false);
        for (int p = 0; p < 2048; ++p) {
            if (P[p]) {
                for (int u : U) {
                    T[p ^ u] = true;
                }
            }
        }

        // Step 4: Count unique triplet XOR results
        int count = 0;
        for (int t = 0; t < 2048; ++t) {
            if (T[t]) {
                count++;
            }
        }

        return count;
    }
};