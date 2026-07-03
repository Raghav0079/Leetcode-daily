#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        vector<vector<pair<int, int>>> adj(n);
        vector<int> in_degree(n, 0);
        set<int> unique_costs;

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];

            if (!online[u] || !online[v]) continue;

            adj[u].push_back({v, cost});
            in_degree[v]++;
            unique_costs.insert(cost);
        }

        vector<int> topo_order;
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        vector<int> sorted_costs(unique_costs.begin(), unique_costs.end());

        auto isValid = [&](int target_min) -> bool {
            vector<long long> dist(n, 1e18); 
            dist[0] = 0;

            for (int u : topo_order) {
                if (dist[u] == 1e18) continue;

                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    int cost = edge.second;

                    if (cost >= target_min) {
                        if (dist[u] + cost < dist[v]) {
                            dist[v] = dist[u] + cost;
                        }
                    }
                }
            }
            return dist[n - 1] <= k;
        };


        int low = 0;
        int high = sorted_costs.size() - 1;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int guess = sorted_costs[mid];

            if (isValid(guess)) {
                ans = guess;       
                low = mid + 1;
            } else {
                high = mid - 1;    
            }
        }

        return ans;
    }
};