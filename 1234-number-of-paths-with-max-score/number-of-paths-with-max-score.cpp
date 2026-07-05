#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;

        // dp[i][j] stores {max_score, number_of_paths}
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {0, 0}));

        // Base case: Start at the bottom-right cell 'S'
        dp[n-1][n-1] = {0, 1}; 

        // Directions to check for each cell: Down, Right, Bottom-Right Diagonal
        int dirs[3][2] = {{1, 0}, {0, 1}, {1, 1}};

        // Traverse backwards from the bottom-right to top-left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // Skip the starting square or obstacles
                if (board[i][j] == 'X' || board[i][j] == 'S') continue;

                int max_score = -1;
                long long path_count = 0;

                // Look at the 3 valid preceding cells
                for (auto& dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];

                    // Check boundaries and if the neighbor is reachable
                    if (ni < n && nj < n && dp[ni][nj].second > 0) {
                        if (dp[ni][nj].first > max_score) {
                            max_score = dp[ni][nj].first;
                            path_count = dp[ni][nj].second;
                        } else if (dp[ni][nj].first == max_score) {
                            path_count = (path_count + dp[ni][nj].second) % MOD;
                        }
                    }
                }

                // If this cell is reachable from at least one valid neighbor
                if (max_score != -1) {
                    int current_val = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                    dp[i][j] = {max_score + current_val, (int)path_count};
                }
            }
        }

        // Return the result for the top-left cell 'E'
        return {dp[0][0].first, dp[0][0].second};
    }
};