```cpp
// N - 1种方式将s切成左右2半, 返回有几种切法满足:
// x和y的数目, 至少在左右两块的一块里有相同数量
int strSplit(string s) {
    if (s.empty()) return 0;
    int totalx = 0, totaly = 0;
    for (char c : s) {
        if (c == 'x') ++totalx;
        else if (c == 'y') ++totaly;
    }
    int leftx = 0, lefty = 0, res = 0;
    for (int i = 0; i < s.length() - 1; ++i) {
        if (s[i] == 'x') {
            ++leftx;
        } else if (s[i] == 'y') {
            ++lefty;
        }
        if (leftx == lefty || totalx - leftx == totaly - lefty) {
            ++res;
        }
    }
    return res;
}
```

```cpp
// https://www.bilibili.com/video/BV1qF411B7B8
int numBlock(vector<int>& w, int x, int k) {
    sort(w.begin(), w.end());
    int splits = 1;
    vector<int> needs;
    for (int i = 1; i < w.size(); ++i) {
        if (w[i] - w[i - 1] > x) {
            ++splits;
            needs.push_back(w[i] - w[i - 1]);
        }
    }
    if (splits == 1 || x == 0 || k == 0) {
        return splits;
    }
    sort(needs.begin(), needs.end());
    for (int i = 0; i < needs.size(); ++i) {
        int need = (needs[i] - 1) / x;
        if (k >= need) {
            splits--;
            k -= need;
        } else {
            break;
        }
    }
    return splits;
}
```
