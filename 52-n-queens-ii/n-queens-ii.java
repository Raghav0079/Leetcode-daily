class Solution {

    int count = 0;

    public int totalNQueens(int n) {
        backtrack(n, 0, 0, 0, 0);
        return count;
    }

    private void backtrack(int n, int row, int columns,
                           int diagonals1, int diagonals2) {

        // All queens placed
        if (row == n) {
            count++;
            return;
        }

        // Positions where we can place a queen
        int available = ((1 << n) - 1)
                        & ~(columns | diagonals1 | diagonals2);

        while (available != 0) {

            // Get the rightmost available position
            int position = available & -available;

            // Remove that position
            available -= position;

            // Move to next row
            backtrack(
                n,
                row + 1,
                columns | position,
                (diagonals1 | position) << 1,
                (diagonals2 | position) >> 1
            );
        }
    }
}