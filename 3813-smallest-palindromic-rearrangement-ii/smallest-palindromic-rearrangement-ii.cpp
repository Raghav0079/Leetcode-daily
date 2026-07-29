#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    const long long MAX_VAL = 1000001;

    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n / 2) r = n - r;
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - i + 1) / i;
            if (res >= MAX_VAL) return MAX_VAL;
        }
        return res;
    }

    long long countArrangements(const vector<int>& count) {
        int total = 0;
        for (int c : count) total += c;
        
        long long res = 1;
        for (int c : count) {
            if (c == 0) continue;
            res = res * nCr(total, c);
            if (res >= MAX_VAL) return MAX_VAL;
            total -= c;
        }
        return res;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        vector<int> halfCount(26, 0);
        string midLetter = "";
        for (int i = 0; i < 26; ++i) {
            halfCount[i] = count[i] / 2;
            if (count[i] % 2 != 0) {
                midLetter = string(1, (char)('a' + i));
            }
        }

        if (countArrangements(halfCount) < k) {
            return "";
        }

        int halfLen = 0;
        for (int c : halfCount) halfLen += c;

        string left = "";
        for (int step = 0; step < halfLen; ++step) {
            for (int i = 0; i < 26; ++i) {
                if (halfCount[i] == 0) continue;
                
                halfCount[i]--;
                long long arrangements = countArrangements(halfCount);
                
                if (arrangements >= k) {
                    left += (char)('a' + i);
                    break;
                } else {
                    k -= arrangements;
                    halfCount[i]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());
        return left + midLetter + right;
    }
};