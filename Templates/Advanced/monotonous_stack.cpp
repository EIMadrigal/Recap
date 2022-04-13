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
        int idx = s.top(); s.pop();
        ans[idx].first = s.empty() ? -1 : s.top();
        ans[idx].second = -1;
    }
    return ans;
} 

// 数组中有重复值, 右侧可以沿用上面代码, 左侧不可
vector<pair<int, int>> monotonousStackRepeat(vector<int>& nums) {
    vector<pair<int, int>> ans(nums.size());  // return index
    stack<vector<int>> s;  // store index, same number's idx stores together 
    
    for (int i = 0; i < nums.size(); ++i) {
        // 求smaller. 若需greater, 改为 nums[i] > nums[s.top()]
        while (!s.empty() && nums[i] < nums[s.top()[0]]) {
            vector<int> pop_idx = s.top(); s.pop();
            int leftSmallIdx = s.empty() ? -1 : s.top()[s.top().size() - 1];
            for (int idx : pop_idx) {
                ans[idx].first = leftSmallIdx;
                ans[idx].second = i;
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
        vector<int> idx = s.top(); s.pop();
        int leftSmallIdx = s.empty() ? -1 : s.top()[s.top().size() - 1];
        for (int i : idx) {
            ans[i].first = leftSmallIdx;
            ans[i].second = -1;
        }
    }
    return ans;
}
