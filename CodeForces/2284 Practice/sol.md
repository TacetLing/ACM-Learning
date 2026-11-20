# CF2284A2 15K4JR3B (Hard Version)

## 题目描述

— Did you know if you connect Park Kultury, a point not in the northeast, and one more on a map, you'll look like an idiot?— No, I did not know that. Is that true?







This is the hard version of the problem. The difference between the versions is that in this version, in one operation, a point coordinate changes by a power of two.

Unemployed  $ \ast $  Angel places three points  $ A $ ,  $ B $ , and  $ C $  at the origin, and also gives you an array  $ a $  of length  $ n $ .

You must perform exactly  $ n $  operations. During the  $ i $ -th operation, choose one of these points and increase or decrease one of its coordinates by  $ 2^{a_i} $ . In other words, if the chosen point has coordinates  $ (x, y) $ , then in the  $ i $ -th operation you may move it to  $ (x + 2^{a_i}, y) $ ,  $ (x - 2^{a_i}, y) $ ,  $ (x, y + 2^{a_i}) $ , or  $ (x, y - 2^{a_i}) $ .

Unemployed  $ \ast $  Angel asks you to find the maximum doubled area of triangle  $ ABC $  after all operations are performed. As she is your idol, you cannot refuse her.

Since Unemployed  $ \ast $  Angel is very smart, she can show that the value of interest is always an integer.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases  $ t $  ( $ 1 \le t \le 100 $ ). The description of the test cases follows.

The first line of each test case contains one integer  $ n $  ( $ 2 \le n \le 100 $ ) — the length of array  $ a $  and the number of operations.

The second line of each test case contains  $ n $  integers  $ a_1, a_2, \ldots, a_n $  ( $ 0 \le a_i \le 24 $ ) — the elements of array  $ a $ .

## 输出格式

For each test case, output one integer — the maximum doubled area of triangle  $ ABC $ .

## 输入输出样例 #1

### 输入 #1

```
4
2
0 0
3
0 0 1
6
0 1 2 2 4 0
6
24 24 24 0 0 0
```

### 输出 #1

```
1
4
192
562950054084608
```

## 说明/提示

In the first test case, increase the  $ x $ -coordinate of  $ B $  by  $ 2^0 $ , then increase the  $ y $ -coordinate of  $ C $  by  $ 2^0 $ . After these  $ 2 $  operations, the points are  $ A = (0, 0) $ ,  $ B = (1, 0) $ , and  $ C = (0, 1) $ . The doubled area of the resulting triangle is  $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2284A2/519eded19d81286ee72005414dc259f275ca8f1fd0977aee98aa9c3b2d6175d7.png)In the second test case, decrease the  $ x $ -coordinate of  $ A $  by  $ 2^0 $ , then increase the  $ x $ -coordinate of  $ B $  by  $ 2^0 $ , and finally increase the  $ y $ -coordinate of  $ C $  by  $ 2^1 $ . After these  $ 3 $  operations, the points are  $ A = (-1, 0) $ ,  $ B = (1, 0) $ , and  $ C = (0, 2) $ . The doubled area of the resulting triangle is  $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2284A2/038a136f9304e70724b2ce2412d9939c4d403605ee7a3ba9cf15d7189e457b3f.png)



 ### 思路分析

#### 1. 几何转化
设最终三点坐标分别为 $A(x_A, y_A)$、$B(x_B, y_B)$、$C(x_C, y_C)$。将所有 $n$ 次操作按所改变的坐标轴划分为两个集合：改变 $x$ 坐标的操作增量（绝对值）之和记为 $S_x$，改变 $y$ 坐标的操作增量之和记为 $S_y$。显然满足：

$$S_x + S_y = \text{sum} = \sum_{i=1}^n 2^{a_i}, \qquad |x_A| + |x_B| + |x_C| \le S_x, \qquad |y_A| + |y_B| + |y_C| \le S_y$$

三角形 $ABC$ 面积的两倍为：

$$2S_{\triangle ABC} = \left|(x_B - x_A)(y_C - y_A) - (x_C - x_A)(y_B - y_A)\right| = \left|x_A(y_B - y_C) + x_B(y_C - y_A) + x_C(y_A - y_B)\right|$$

由绝对值不等式与三角不等式可得：

$$2S_{\triangle ABC} \le \left(|x_A| + |x_B| + |x_C|\right) \cdot \max\left(|y_B - y_C|, |y_C - y_A|, |y_A - y_B|\right) \le S_x \cdot S_y$$

该上界可以精确取到：只需将所有 $x$ 轴操作以正增量施加于点 $B$（到达 $(S_x, 0)$），将所有 $y$ 轴操作以正增量施加于点 $C$（到达 $(0, S_y)$），点 $A$ 保持在原点 $(0, 0)$，此时恰有 $2S_{\triangle ABC} = S_x \cdot S_y$。

因此，原问题等价于将数组 $\text{arr}[1 \dots n]$（其中 $\text{arr}[i] = 2^{a_i}$）划分为两个子集，设其中一组之和为 $\text{ans}$，另一组之和为 $\text{sum} - \text{ans}$，要求最大化乘积 $(\text{sum} - \text{ans}) \cdot \text{ans}$。

#### 2. 贪心策略与正确性证明
令 $H = \lfloor \frac{\text{sum}}{2} \rfloor$。由于乘积满足

$$(\text{sum} - \text{ans}) \cdot \text{ans} = \frac{\text{sum}^2 - (\text{sum} - 2 \cdot \text{ans})^2}{4}$$

结合两组的对称性，不妨令 $\text{ans} \le H$，目标即转化为：从 $\text{arr}[1 \dots n]$ 中选出一个子集，使其总和 $\text{ans}$ 在不超过 $H$ 的前提下尽可能大。

代码将 $\text{arr}[1 \dots n]$ **降序排序**后从前向后依次枚举，只要当前元素 $\text{arr}[i]$ 满足 $\text{ans} + \text{arr}[i] \le H$ 就将其加入 $\text{ans}$。

下面用数学归纳法证明该贪心策略的正确性：记贪心处理完降序序列的前 $k$ 个元素后得到的结果为 $s_k$（初始 $s_0 = 0$），命题为 **$s_k$ 始终是前 $k$ 个元素中不超过 $H$ 的最大可达子集和**。

- **基础情况**：当 $k = 0$ 时，$s_0 = 0$，显然成立。
- **归纳步骤**：假设命题对 $k - 1$ 成立，考虑第 $k$ 个元素 $x = \text{arr}[k]$，设前 $k$ 个元素所能凑出的任意合法子集和为 $s' \le H$：
  1. **若 $s_{k-1} + x \le H$**：贪心取 $s_k = s_{k-1} + x$。
     - 若 $s'$ 不包含 $x$，则 $s'$ 仅由前 $k - 1$ 个元素组成，故 $s' \le s_{k-1} \le s_k$；
     - 若 $s'$ 包含 $x$，则 $s' - x$ 为前 $k - 1$ 个元素的可达和（且不超过 $H$），由归纳假设有 $s' - x \le s_{k-1}$，从而 $s' \le s_{k-1} + x = s_k$。
  2. **若 $s_{k-1} + x > H$**：贪心跳过 $x$，取 $s_k = s_{k-1}$。假设存在更优的合法解 $s'$ 满足 $s_{k-1} < s' \le H$：
     - 首先 $s'$ 必须包含 $x$（否则 $s'$ 为前 $k - 1$ 个元素的可达和，必有 $s' \le s_{k-1}$，矛盾）。
     - 于是 $s' - x$ 为前 $k - 1$ 个元素的可达和。一方面，由 $s' \le H < s_{k-1} + x$ 得 $s' - x < s_{k-1}$；另一方面，由 $s' > s_{k-1}$ 得 $s' - x > s_{k-1} - x$。联立可得：
       $$s' - x \in (s_{k-1} - x,\; s_{k-1})$$
     - 然而，由于序列降序排列且所有元素均为 $2$ 的幂，前 $k - 1$ 个元素均不小于 $x$，因此全都是 $x$ 的整数倍。故前 $k - 1$ 个元素的任意可达子集和 $s_{k-1}$ 与 $s' - x$ 也必然都是 $x$ 的整数倍。但开区间 $(s_{k-1} - x,\; s_{k-1})$ 的两端点恰好为相邻的两个 $x$ 的倍数，区间内部不含任何 $x$ 的倍数，产生矛盾。
     - 因此 $s' \le s_{k-1} = s_k$，归纳成立。

遍历结束后，$s_n = \text{ans}$ 即为不超过 $\lfloor \frac{\text{sum}}{2} \rfloor$ 的最大可达子集和，输出 $(\text{sum} - \text{ans}) \cdot \text{ans}$ 即可。

### 复杂度分析

- **时间复杂度**：读入并构造 $\text{arr}$ 与贪心遍历均为 $\mathcal{O}(n)$，降序排序耗时 $\mathcal{O}(n \log n)$。单组数据时间复杂度为 $\mathcal{O}(n \log n)$，$t$ 组数据总时间复杂度为 $\mathcal{O}(t \cdot n \log n)$。
- **空间复杂度**：使用长度为 $n + 5$ 的数组 $\text{arr}$ 存储元素，单组及总空间复杂度均为 $\mathcal{O}(n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n;
    cin>>n;
    vector<int> arr(n+5,0);
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i]=(1LL<<arr[i]);
        sum+=arr[i];
    }

    sort(arr.begin()+1,arr.begin()+n+1,greater<int>());

    int ans=0;
    for(int i=1;i<=n;i++){
        if(ans+arr[i]<=sum/2){
            ans+=arr[i];
        }
    }

    cout<<(sum-ans)*ans<<'\n';
    return;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```


# CF2284C2 Disgusting + GCD (Checker Version)

## 题目描述

In this version, you need to implement part of the checker for the constructive version.

In this version, you are ogiyo.

kijjot gives you two integers  $ a $  and  $ b $  such that  $ a \le b $ . In one operation, you can choose a positive integer  $ x $  such that  $ \gcd(a, x) = 1 $  $ ^{\text{∗}} $ , and then increase  $ a $  by  $ x $ .

Your task is to find any sequence of operations of the minimum possible length to transform  $ a $  into  $ b $ . It can be shown that under the given constraints, it is always possible to transform  $ a $  into  $ b $  using at most  $ 15 $  operations.

 $ ^{\text{∗}} $  $ \gcd(x, y) $  denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers  $ x $  and  $ y $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases  $ t $  ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

Each test case contains two integers  $ a $  and  $ b $  ( $ 2 \le a \le 10^5 $ ,  $ a \le b \le 10^9 $ ) — the numbers given to you by kijjot.

## 输出格式

For each test case, output the minimum number of operations  $ k $  ( $ 0 \le k \le 15 $ ) in the first line.

In the second line, output  $ k $  positive integers  $ x_1, x_2, \ldots, x_k $  — the values of  $ x $  chosen in the operations, in order. These operations must be valid and transform  $ a $  into  $ b $ .

If  $ k = 0 $ , you may omit the second line. If there are multiple optimal sequences, output any of them.

## 输入输出样例 #1

### 输入 #1

```
4
2 2
15 25
2184 2200
100000 1000000000
```

### 输出 #1

```
0
2
1 9
3
11 2 3
2
1636673 998263327
```

## 说明/提示

In the first test case,  $ a = b = 2 $ , so no operations are needed.

In the second test case, we can first add  $ 1 $  to obtain  $ 16 $ , and then add  $ 9 $  to obtain  $ 25 $ . Both operations are valid because  $ \gcd(15, 1) = 1 $  and  $ \gcd(16, 9) = 1 $ . It can be shown that fewer than  $ 2 $  operations are not enough.



### 思路分析

设操作过程中依次经过的数值序列为 $a = v_0 < v_1 < \dots < v_k = b$，第 $i$ 步选择的增量为 $x_i = v_i - v_{i-1} > 0$。由于每一步都只能加上正整数，所有中间值严格递增且均落在 $[a, b]$ 区间内。

根据辗转相除法性质 $\gcd(x, y) = \gcd(x, y - x)$，单步合法条件 $\gcd(v_{i-1}, v_i - v_{i-1}) = 1$ 等价于：

$$\gcd(v_{i-1}, v_i) = 1$$

按最少操作次数 $k$ 从小到大分类讨论：

1. **$k = 0$**：当且仅当 $a = b$ 时无需任何操作，直接输出 $0$。
2. **$k = 1$**：若 $a < b$ 且 $\gcd(a, b - a) = 1$，则一次选择 $x_1 = b - a$ 即可到达 $b$。
3. **$k = 2$**：设第一步后的中间值为 $p$（$a < p < b$），则两步的增量分别为 $p - a$ 与 $b - p$。合法条件为 $\gcd(a, p - a) = 1$ 且 $\gcd(p, b - p) = 1$，由辗转相除法可化简为：
   $$\gcd(p, a) = 1 \quad \text{且} \quad \gcd(p, b) = 1$$
   即 $p$ 同时与 $a, b$ 互质（等价于 $\gcd(p, ab) = 1$）。
   - **正确性与间隙上界**：由数据范围 $a \le 10^5, b \le 10^9$ 可知 $ab \le 10^{14}$。因为前 $13$ 个质数的乘积
     $$\prod_{i=1}^{13} p_i = 2 \times 3 \times \dots \times 41 = 304\,250\,263\,527\,210 > 10^{14}$$
     所以 $ab$ 至多有 $\omega(ab) \le 12$ 个不同的质因子。
   - 定义 Jacobsthal 函数 $j(m)$ 为最小的整数 $L$，使得任意连续 $L$ 个整数中至少包含一个与 $m$ 互质的数；记 $h(k)$ 为前 $k$ 个质数乘积对应的 Jacobsthal 函数值。根据 Hajdu 与 Saradha (2012) 对 $\omega(m) \le 23$ 的结果，对任意满足 $\omega(m) \le 12$ 的整数 $m$，均有 $j(m) \le h(12) = 66$。
   - 因此，只要枚举 $p \in (a, b)$，若存在合法解，至多检查 $66$ 次即可命中并直接返回。
4. **$k \ge 3$**：若上述分支均未返回，说明区间 $(a, b)$ 内不存在与 $ab$ 互质的整数，从而必有 $b - a \le 66$。
   - 令 $n = b - a + 1 \le 67$，以偏移量 $u = v - a \in [0, n - 1]$ 表示数值 $v$（其中 $0$ 对应 $a$，$n - 1$ 对应 $b$）。
   - 对于任意 $0 \le u < v < n$，若 $\gcd(a + u, a + v) = 1$，则存在有向边 $u \to v$。特别地，因为相邻整数互质，边 $u \to u + 1$ 恒成立，故从 $0$ 出发必能到达 $n - 1$。
   - 使用队列 `q` 从 $0$ 开始进行广度优先搜索（BFS），配合 $\text{vis}$ 判重与 $\text{parent}$ 记录前驱节点，并在首次访问到 $n - 1$ 时利用 $\text{found}$ 提前终止搜索。最后从 $n - 1$ 沿 $\text{parent}[\text{cur}]$ 回溯至 $0$，依次记录增量 $\text{cur} - \text{parent}[\text{cur}]$ 并反转 $\text{ops}$，即得字典序对应的最优操作序列。

### 复杂度分析

- **时间复杂度**：
  - 当 $k \in \{0, 1\}$ 时，时间复杂度为 $\mathcal{O}(\log b)$。
  - 当 $k = 2$ 时，循环至多执行 $66$ 次，每次调用两次 `__gcd`，时间复杂度为 $\mathcal{O}(\log b)$。
  - 当 $k \ge 3$ 时，区间点数 $n = b - a + 1 \le 67$，BFS 至多检查 $\frac{n(n - 1)}{2}$ 对状态，单次复杂度为 $\mathcal{O}(n^2 \log b)$（其中 $n$ 受常数 $67$ 约束）。
  - 综上，单组数据最坏时间复杂度为 $\mathcal{O}(n^2 \log b)$（$n \le 67$），$t$ 组数据总时间复杂度为 $\mathcal{O}(t \cdot n^2 \log b)$，可在时限内稳定通过。
- **空间复杂度**：
  - 仅在 $k \ge 3$ 时开辟长度为 $\mathcal{O}(n)$ 的辅助数组 $\text{parent}$、$\text{vis}$、队列 `q` 及结果数组 $\text{ops}$。由于 $n \le 67$，单组数据及总空间复杂度均为 $\mathcal{O}(n)$（即 $\mathcal{O}(1)$ 级别常数空间）。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int a,b;
    cin>>a>>b;

    if(a==b){
        cout<<0<<'\n';
        return;
    }

    if(__gcd(a,b-a)==1){
        cout<<1<<'\n'<<(b-a)<<'\n';
        return;
    }

    for(int p=a+1;p<b;p++){
        if(__gcd(p,a)==1 && __gcd(p,b)==1){
            cout<<2<<'\n'<<(p-a)<<" "<<(b-p)<<'\n';
            return;
        }
    }

    int n=(b-a+1);
    vector<int> parent(n,-1);
    vector<bool> vis(n+5,false);
    queue<int> q;
    vis[0]=true;
    q.push(0);
    bool found=false;

    while(!q.empty() && !found){
        int u=q.front();
        q.pop();
        for(int v=u+1;v<n;v++){
            if(!vis[v] && __gcd(a+u,a+v)==1){
                vis[v]=true;
                parent[v]=u;
                q.push(v);
                if(v==n-1){
                    found=true;
                    break;
                }
            }
        }
    }

    vector<int> ops;
    for(int cur=n-1;cur!=0;cur=parent[cur]){
        ops.push_back(cur-parent[cur]);
    }
    reverse(ops.begin(),ops.end());

    cout<<(int)ops.size()<<'\n';
    for(int i=0;i<(int)ops.size();i++){
        cout<<ops[i]<<(i+1==(int)ops.size() ? '\n' : ' ');
    }
    return;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

