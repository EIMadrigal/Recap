## Speed Typing
注意需要保证2字符串顺序不变
```cpp
#include <bits/stdc++.h>
using namespace std;

void solve(string& I, string& P) {
	int i = 0, j = 0;
	while (i < I.length() && j < P.length()) {
		if (I[i] == P[j]) {
			++i, ++j;
		}
		else {
			++j;
		}
	}
	if (i == I.length()) {
		cout << P.length() - I.length() << "\n";
	}
	else {
		cout << "IMPOSSIBLE\n";
	}
}

int main() {
	int t;
	string I, P;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		cin >> I >> P;
		printf("Case #%d: ", i + 1);
		solve(I, P);
	}
	return 0;
}
```

## Challenge Nine
给一个正整数, 插入一个0-9的字符使得该数能被9整除且最小.  
被9整除意味着所有位加起来模9为0, 看看需要插入哪个数字即可

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve(string& s) {
    int cnt = 0;
    for (char c : s) {
        cnt += (c - '0') % 9;
    }
    cnt = 9 - cnt % 9;
    if (cnt == 9) cnt = 0;
    if (cnt == 0) {
        s.insert(s.begin() + 1, 1, '0');
    }
    else {
        for (int i = 0; i <= s.length(); ++i) {
            if (i == s.length()) {
                s.insert(s.end(), 1, cnt + '0');
                break;
            }
            else if (cnt < s[i] - '0') {
                s.insert(s.begin() + i, 1, cnt + '0');
                break;
            }
        }
    }
    cout << s << "\n";
}

int main() {
    int t;
    string s;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> s;
        printf("Case #%d: ", i + 1);
        solve(s);
    }
    return 0;
}
```

## Palindrome Free Strings
给一个由?01组成的字符串, 将所有?填充为0/1使得字符串中没有长度大于5的回文子串, 是否存在填充方案  
暴力dfs的时间复杂度是O(N^3*2^N)
```cpp
#include <bits/stdc++.h>
using namespace std;

bool palindrome(const string& s) {
    for (int i = 0; i < s.length() / 2; ++i) {
        if (s[i] != s[s.length() - i - 1]) {
            return false;
        }
    }
    return true;
}

bool check(string& s) {
    for (char c : s) {
        if (c == '?') return false;
    }
    for (int i = 0; i < s.length(); ++i) {
        for (int j = i + 4; j < s.length(); ++j) {
            if (palindrome(s.substr(i, j - i + 1))) {
                return false;
            }
        }
    }
    return true;
}

bool dfs(string& s, int i) {
    if (i == s.length()) {
        if (check(s)) return true;
        return false;
    }
    
    if (s[i] != '?') {
        return dfs(s, i + 1);
    }
    s[i] = '1';
    if (dfs(s, i + 1)) {
        return true;
    }
    else {
        s[i] = '0';
        if (dfs(s, i + 1))
            return true;
    }
    s[i] = '?';
    return false;
}

int main() {
    int t, n;
    cin >> t;
    string s;
    for (int i = 1; i <= t; ++i) {
        cin >> n >> s;
        printf("Case #%d: ", i);
        if (dfs(s, 0)) {
            printf("POSSIBLE\n");
        }
        else {
            printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}
```

## Interesting Integers
```cpp
```

