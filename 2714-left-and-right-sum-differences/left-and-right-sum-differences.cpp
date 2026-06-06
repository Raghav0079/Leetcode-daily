class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();

        int sum = accumulate(begin(nums) , end(nums) , 0);

        vector<int> result(n);

        int leftSum = 0;

        for(int i =0 ; i<n ; i++){
            sum -= nums[i];

            result[i] = abs(leftSum - sum);

            leftSum += nums[i] ;

        }
        return result;
        
    }
};