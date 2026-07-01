class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        ios_base :: sync_with_stdio(false);
        cin.tie(NULL);

        int n = grid.size();

        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        vector<vector<int>> safeness(n,vector<int>(n,-1));
        queue<pair<int, int>> q;

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    q.push({r, c});
                    safeness[r][c] = 0;
                }
            }
        }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && safeness[nr][nc] == -1) {
                    safeness[nr][nc] = safeness[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        priority_queue<tuple<int, int, int>> max_heap;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        max_heap.push({safeness[0][0], 0, 0});
        visited[0][0] = true;

        while (!max_heap.empty()) {
            auto [current_safe, r, c] = max_heap.top();
            max_heap.pop();

        if (r == n - 1 && c == n - 1) {
                return current_safe;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    
                    int next_safe = min(current_safe, safeness[nr][nc]);
                    max_heap.push({next_safe, nr, nc});
                }
            }
        }
        return 0 ;
    }
};