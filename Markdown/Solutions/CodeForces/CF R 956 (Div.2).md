# A

唐氏题目，随便构造一下，一种构造是 $a_i=i$.

# B

$1+2\equiv 3$，每行 $\bmod 3$ 相同就行.

# C

$3!=6$ 种情况分别算一下.

# D

交换等于把一段连续区间相邻数对依次交换.

类似冒泡排序，肯定和逆序对数量相关.

只要逆序对个数奇偶性相同且元素全部一样就 OK.

# E

妙妙题

考虑没有 Special 的时候 Alice 的答案是什么.
$$
\lceil\frac{n}{2}\rceil \left(\sum\limits_{x\in a} x\right)
$$

考虑 $n-k$ 个 Normal 的连续段会被 $k$ 个 Special 分成连续段，然后再做.

[Tutorial](https://codeforces.com/blog/entry/131268)

# F

最唐 F

套路地二分答案，套路地使用 Trie + 贪心保留 id 最大的

做完了，$\Theta(n\log^2n)$.

# G

还行吧

套路地，对每一位分别统计贡献.

发现每一位的 xor 贡献形如 ```0000111100001111...```，于是可以维护有规律段，无规律段分别处理.

可以每一位离线下来 dfs 一遍，在线的话题解说可以按位去跳，神秘.

复杂度 $\Theta(n\log V)$，巨大常数.
