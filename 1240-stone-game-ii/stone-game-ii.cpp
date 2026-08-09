class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // suffixSum[i] stores the sum of piles from index i to n-1
        vector<int> suffixSum(n, 0);
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        // Memoization table initialized to 0
        vector<vector<int>> memo(n, vector<int>(n + 1, 0));
        
        auto dfs = [&](auto& self, int i, int m) -> int {
            // Base cases
            if (i >= n) return 0;
            // If the player can take all remaining piles, take them all
            if (i + 2 * m >= n) return suffixSum[i];
            
            // Return cached result if available
            if (memo[i][m] != 0) return memo[i][m];
            
            int maxStones = 0;
            // Try all valid moves X (1 <= X <= 2M)
            for (int x = 1; x <= 2 * m; ++x) {
                maxStones = max(maxStones, suffixSum[i] - self(self, i + x, max(m, x)));
            }
            
            return memo[i][m] = maxStones;
        };
        
        return dfs(dfs, 0, 1);
    }
};