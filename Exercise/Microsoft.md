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
