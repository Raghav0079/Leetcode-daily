#include <vector>
#include <cmath>

class Solution {
public:
    std::vector<bool> pathExistenceQueries(int n, std::vector<int>& nums, int maxDiff, std::vector<vector<int>>& queries) {
        // component[i] stores the group/component ID of node i
        std::vector<int> component(n, 0);
        int current_component_id = 0;
        
        // Step 1: Linear scan to group elements into connected components
        for (int i = 1; i < n; ++i) {
            // If the jump between consecutive elements is too large, 
            // a new connected component begins.
            if (nums[i] - nums[i - 1] > maxDiff) {
                current_component_id++;
            }
            component[i] = current_component_id;
        }
        
        // Step 2: Answer each query in O(1) time
        std::vector<bool> ans;
        ans.reserve(queries.size()); // Optimize memory allocation
        
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            
            // If both nodes belong to the same component, a path exists.
            ans.push_back(component[u] == component[v]);
        }
        
        return ans;
    }
};