
# 计算机 (computer)

?? 神秘语言

### 基本语句

#### 类型

1. `int`
2. `operation`

#### 内存操作

1. `rd a`: `a`
2. `set(k)`: `k`
3. `alloc<TYPE>`: `new TYPE`
4. `alloc len`: `new int[len]`, `len <= 32`
5. `next a k`: `*(a + k)`

#### 运算操作

1. `sum a b`: `a + b`
2. `shift(k) a`: `a >> k`
3. `compare a k`: `a < k`

#### 分支与循环结构

1. `if [expr] then fi`
2. `signal SIGN`
3. `goto SIGN`

## 常数优化

### Subtask 0

数组

`A[n]`, `n < 10^5`

类 sgt 结构分配内存索引

### Subtask 1

`lowbit(a)`

线段树维护右移, $O(\log \log V)$

### Subtask 2

实现简单的 `std::vector`

### Subtask 3

对 $n$ 个数的动长数组进行排序，尽量减少操作次数

### Subtask 4


## 算法

### Subtask 6

实现树的深搜与树哈希

### Subtask 7

通信 subtask.

小 A 有一颗 prufer 随的树，小 B 没有一棵树

现在小 A 要用一定的存储空间给小 B 发消息，希望还原出一颗树同构的树，子节点无顺序
