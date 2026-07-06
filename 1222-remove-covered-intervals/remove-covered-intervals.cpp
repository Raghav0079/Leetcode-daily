class Solution {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals) {
        // Sort: Ascending by start; Descending by end if starts are equal
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0];
        });
        
        int remaining_count = 0;
        int max_end = 0;
        
        for (const auto& interval : intervals) {
            // If the current interval's end extends past our max_end,
            // it is NOT covered. We keep it.
            if (interval[1] > max_end) {
                remaining_count++;
                max_end = interval[1]; // Update the boundary
            }
            // Otherwise, it's covered by a previous interval, so we ignore it.
        }
        
        return remaining_count;
    }
};