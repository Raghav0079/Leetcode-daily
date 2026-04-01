#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);


        sort(indices.begin(), indices.end(), [&](int i, int j) {
            return positions[i] < positions[j];
        });

        stack<int> st; 
        
        for (int i : indices) {
            if (directions[i] == 'R') {
                st.push(i);
            } else {
               
                while (!st.empty() && healths[i] > 0) {
                    int topIdx = st.top();
                    
                    if (healths[topIdx] < healths[i]) {
                        
                        healths[topIdx] = 0;
                        healths[i] -= 1;
                        st.pop();
                    } else if (healths[topIdx] > healths[i]) {
                     
                        healths[topIdx] -= 1;
                        healths[i] = 0;
                    } else {
          
                        healths[topIdx] = 0;
                        healths[i] = 0;
                        st.pop();
                    }
                }
            }
        }


        vector<int> result;
        for (int h : healths) {
            if (h > 0) {
                result.push_back(h);
            }
        }
        return result;
    }
};
