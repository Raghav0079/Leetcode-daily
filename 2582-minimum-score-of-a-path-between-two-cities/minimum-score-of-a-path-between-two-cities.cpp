class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int distance = road[2];
            graph[u].push_back({v, distance});
            graph[v].push_back({u, distance});
        }

        // Step 2: Initialize BFS variables
        int min_score = INT_MAX;
        std::queue<int> q;
        std::vector<bool> visited(n + 1, false);

        q.push(1);
        visited[1] = true;

        // Step 3: Traverse the connected component
        while (!q.empty()) {
            int curr_city = q.front();
            q.pop();

            for (const auto& edge : graph[curr_city]) {
                int neighbor = edge.first;
                int distance = edge.second;

                // Track the absolute lowest edge weight seen in this component
                min_score = std::min(min_score, distance);

                // Add unvisited neighbors to the queue
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return min_score;
        
    }
};