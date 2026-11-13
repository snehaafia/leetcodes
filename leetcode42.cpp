class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0), chain(n + 1, 0);
        for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + nums[i];
        // chain[i] = sum over t >= i of max(nums[i..t]), via next strictly greater element
        vector<int> stk;
        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() && nums[stk.back()] <= nums[i]) stk.pop_back();
            int ng = stk.empty() ? n : stk.back();
            chain[i] = (long long)nums[i] * (ng - i) + chain[ng];
            stk.push_back(i);
        }
        vector<int> dq(n);
        int head = 0, tail = 0;
        long long res = 0;
        int left = 0;
        for (int j = 0; j < n; ++j) {
            while (tail > head && nums[dq[tail - 1]] < nums[j]) --tail;
            dq[tail++] = j;
            while (true) {
                while (dq[head] < left) ++head;
                int c = dq[head]; // leftmost maximum of window, lies on the chain from left
                long long cost = chain[left] - chain[c]
                               + (long long)nums[c] * (j - c + 1)
                               - (prefix[j + 1] - prefix[left]);
                if (cost <= k) break;
                ++left;
            }
            res += j - left + 1;
        }
        return res;
    }
};
