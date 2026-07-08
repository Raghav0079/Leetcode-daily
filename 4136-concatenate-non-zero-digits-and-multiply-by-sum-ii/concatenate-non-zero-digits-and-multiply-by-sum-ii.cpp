#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        long long MOD = 1e9 + 7;
        int n = s.length();
        
        // pow10[i] stores (10^i) % MOD
        vector<long long> pow10(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }
        
        // idx[i] = count of non-zero digits up to index i-1
        vector<int> idx(n + 1, 0);
        // x[i] = running concatenated number modulo MOD up to index i-1
        vector<long long> x(n + 1, 0);
        // total[i] = prefix sum of all digits up to index i-1
        vector<long long> total(n + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            int d = s[i] - '0';
            
            total[i + 1] = total[i] + d;
            idx[i + 1] = idx[i] + (d != 0 ? 1 : 0);
            
            if (d != 0) {
                x[i + 1] = (x[i] * 10 + d) % MOD;
            } else {
                x[i + 1] = x[i];
            }
        }
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            
            // 1. Calculate the sum of digits in range [l, r]
            long long current_sum = total[r + 1] - total[l];
            
            // 2. Extract the concatenated non-zero number in range [l, r]
            int num_nonzero = idx[r + 1] - idx[l];
            long long current_x = (x[r + 1] - (x[l] * pow10[num_nonzero]) % MOD + MOD) % MOD;
            
            // 3. Compute final product modulo MOD
            long long result = (current_x * current_sum) % MOD;
            ans.push_back(result);
        }
        
        return ans;
    }
};