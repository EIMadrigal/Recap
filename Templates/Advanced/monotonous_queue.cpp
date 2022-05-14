// 求所有区间长度为k的最大值
vector<int> monotonousQueue(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> q;  // store index, front is the largest

    for (int i = 0; i < nums.size(); ++i) {
        if (!q.empty() && i - q.front() >= k) {
            q.pop_front();
        }
        while (!q.empty() && nums[i] > nums[q.back()]) {  // 改为 < 即求区间最小
            q.pop_back();
        }
        q.push_back(i);
        if (i >= k - 1) {
            res.push_back(nums[q.front()]);
        }
    }
    return res;
}
