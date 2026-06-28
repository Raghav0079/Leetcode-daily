class Solution {
public:
    typedef long long ll;
    int maximumLength(vector<int>& nums) {
        unordered_map<ll, int> mp;
        for(int num : nums){
            mp[num]++;
        }

        int result = 0;
        if (mp.count(1)) {
            if (mp[1] % 2 == 1) {
                result = mp[1];
            } else {
                result = mp[1] - 1;
            }
        }

        for(auto &[num, _] : mp){
            if(num == 1) continue;
            
            ll curr = num;
            int len = 0;
            while (mp.count(curr) && mp[curr] > 1) {
                len += 2;
                curr = curr * curr;
                if (curr > 1e9) break; 
            }
            if (mp.count(curr) && mp[curr] >= 1) {
                len += 1;
            } else {
                len -= 1;
            }
            if (len > 0) {
                result = max(result, len);  
            }
        }

        return result;
    }
};