35道选择，涵盖范围非常广。
## 多叉树层序遍历

## LC 1035

## 32位小端转大端
被测评系统坑了，剩10min发现样例都没过。。。为啥没过系统也是绿的呢。。。
```cpp
void convert_little_to_big(uint32_t *numbers, int count) {
    *numbers = ((*numbers) << 24)
        | (((*numbers) & 0x0000FF00) << 8)
        | (((*numbers) & 0x00FF0000) >> 8)
        | ((*numbers) >> 24);
}
```
