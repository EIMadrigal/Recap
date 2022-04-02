class MonotonousStack {
public:
    // 左边和右边第一个比nums[i]小(大)的位置 栈自底向上从小到大(从大到小)
    // 数组中无重复值
    vector<pair<int, int>> find(vector<int>& nums) {
        vector<pair<int, int>> ans(nums.size());  // return index
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
    stack<int> s;  // store index
};

// 有重复值, 主要为了处理左侧, 右侧其实可以沿用上面代码
vector<vector<int>> monotonous_stack(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans(n, vector<int>(2, 0));  // return index
    stack<vector<int>> s;  // store index, same number's idx stores together 
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && nums[i] < nums[s.top()[0]]) {
            vector<int> pop_idx = s.top(); s.pop();
            int left_less_idx = s.empty() ? -1 : s.top()[s.top().size() - 1];
            for (int idx : pop_idx) {
                ans[idx][0] = left_less_idx;
                ans[idx][1] = i;
            }
        }
        if (!s.empty() && nums[i] == nums[s.top()[0]]) {
            s.top().emplace_back(i);
        }
        else {
            s.push({i});
        }
    }
    while (!s.empty()) {
        vector<int> pop_idx = s.top(); s.pop();
        int left_less_idx = s.empty() ? -1 : s.top()[s.top().size() - 1];
        for (int idx : pop_idx) {
            ans[idx][0] = left_less_idx;
            ans[idx][1] = -1;
        }
    }
    return ans;
}
