1. 统计字符串里中英文字母、空格、数字和其他字符的个数，只能用Java
```java
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.HashMap;

public class Main{
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();
        HashMap<Integer, Integer> cnts = new HashMap<Integer, Integer>();
        for (int i = 0; i < s.length(); ++i) {
            char c = s.charAt(i);
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= 0x0391 && c <= 0xFFE5)) {
                cnts.put(1, 1 + cnts.getOrDefault(1, 0));
            } else if (c >= '0' && c <= '9') {
                cnts.put(2, 1 + cnts.getOrDefault(2, 0));
            } else if (c == ' ') {
                cnts.put(3, 1 + cnts.getOrDefault(3, 0));
            } else {
                cnts.put(4, 1 + cnts.getOrDefault(4, 0));
            }
        }
        for (Integer i : cnts.keySet()) {
            if (i == 1) {
                System.out.println("字母的个数为:" + cnts.get(i));
            } else if (i == 3) {
                System.out.println("空格的个数为:" + cnts.get(i));
            } else if (i == 2) {
                System.out.println("数字的个数为:" + cnts.get(i));
            } else if (i == 4) {
                System.out.println("其他字符个数:" + cnts.get(i));
            }
        }
    }
}
```

2. synchronized锁升级的原理
