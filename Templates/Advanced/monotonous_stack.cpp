// 左边和右边第一个比nums[i]小(大)的元素索引 栈自底向上从小到大(从大到小)

// 数组中无重复值 first存左侧索引 second存右侧索引
vector<pair<int, int>> monotonousStack(vector<int>& nums) {
    stack<int> s;  // store index
    vector<pair<int, int>> ans(nums.size());  // return index
    
    for (int i = 0; i < nums.size(); ++i) {
        // 求smaller. 若需greater, 改为 nums[i] > nums[s.top()]
        while (!s.empty() && nums[i] < nums[s.top()]) {
            int idx = s.top(); s.pop();
            ans[idx].first = s.empty() ? -1 : s.top();
            ans[idx].second = i;
        }
        s.push(i);
    }
    while (!s.empty()) {
        int popIdx = s.top(); s.pop();
        ans[popIdx].first = s.empty() ? -1 : s.top();
        ans[popIdx].second = -1;
    }
    return ans;
} 

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
