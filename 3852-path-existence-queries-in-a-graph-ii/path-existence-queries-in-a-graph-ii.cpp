class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 1. Store and sort indices based on their values in nums
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), [&](int i, int j) {
            return nums[i] < nums[j];
        });

        // rank[i] will store the position of original node 'i' in the sorted array
        vector<int> rank(n);
        for (int i = 0; i < n; ++i) {
            rank[p[i]] = i;
        }

        // 2. Precompute the furthest right index reachable in 1 hop for each sorted element
        // Since it's sorted, we can use a two-pointer approach
        vector<int> next_hop(n);
        int r = 0;
        for (int l = 0; l < n; ++l) {
            while (r < n && nums[p[r]] - nums[p[l]] <= maxDiff) {
                r++;
            }
            next_hop[l] = r - 1; // max index reachable from l
        }

        // 3. Build the Binary Lifting Table
        int max_power = 20; // 2^20 > 10^5
        vector<vector<int>> up(n, vector<int>(max_power));
        for (int i = 0; i < n; ++i) {
            up[i][0] = next_hop[i];
        }
        for (int j = 1; j < max_power; ++j) {
            for (int i = 0; i < n; ++i) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        // Lambda function to check if target can be reached within 'k' hops
        auto can_reach = [&](int start, int target, int k) {
            int curr = start;
            for (int j = 0; j < max_power; ++j) {
                if ((k >> j) & 1) {
                    curr = up[curr][j];
                }
            }
            return curr >= target;
        };

        // 4. Answer Queries
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int u = rank[q[0]];
            int v = rank[q[1]];
            
            if (u == v) {
                ans.push_back(0);
                continue;
            }
            if (u > v) swap(u, v); // Ensure we are jumping from left to right

            // Check if u and v are even in the same connected component
            // We can do this by jumping maximum possible hops from u and checking if it can ever reach v
            if (!can_reach(u, v, n)) {
                ans.push_back(-1);
                continue;
            }

            // Binary search for the minimum hops required
            int low = 1, high = n, best = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (can_reach(u, v, mid)) {
                    best = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            ans.push_back(best);
        }

        return ans;
    }
};