class MonotonousStack {
public:
    // 左边和右边第一个比nums[i]小的
    vector<pair<int, int>> find(vector<int>& nums) {
        vector<pair<int, int>> ans(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            while (!s.empty() && nums[i] < nums[s.top()]) {
                int popIdx = s.top(); s.pop();
                int leftIdx = s.empty() ? -1 : s.top();
                ans[popIdx].first = leftIdx;
                ans[popIdx].second = i;
            }
            s.push(i);
        }
        while (!s.empty()) {
            int popIdx = s.top(); s.pop();
            int leftIdx = s.empty() ? -1 : s.top();
            ans[popIdx].first = leftIdx;
            ans[popIdx].second = -1;
        }
        return ans;
    } 
private:
    stack<int> s;
};
