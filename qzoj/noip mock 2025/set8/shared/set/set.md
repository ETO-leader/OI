## 题目描述

给定正整数 $m$，求最大的 $n$，使得存在 $S_1,S_2,\dots,S_m\subseteq \{1,2,\dots,n\}$，满足对于任意的 $j\in\{1,2,\dots,n\}$ 都存在 $I\subseteq \{1,2,\dots,m\}$ 使得 $\bigcap\limits_{i\in I}S_i=\{j\}$。

找出最大的 $n$，构造对应的 $S_1,S_2,\dots,S_m$，并为每个 $j$ 给出对应的 $I$。

## 输入格式

输入数据包含一个整数 $m$。

## 输出格式

先输出一行一个整数表示 $n$。可以证明 $n\leq 2^m$。

接下来 $m$ 行依次表示 $S_1,\dots,S_m$。其中第 $i$ 行先输出一个整数表示 $|S_i|$，再输出 $|S_i|$ 个互不相同的整数表示 $S_i$ 中的元素。

接下来 $n$ 行的第 $j$ 行中，先输出一个正整数 $k$，再输出 $k$ 个整数 $i_1,i_2,\dots,i_k$，它们需满足 $1\leq i_1<i_2<\cdots<i_k\leq m$ 且 $S_{i_1}\cap S_{i_2}\cap \cdots\cap S_{i_k}=\{j\}$。

输出任意一组合法方案均可。

## 样例数据

### 样例 1 输入

```
1
```

### 样例 1 输出

```
1
1 1
1 1
```

## 数据规模与约定

共有 10 个测试点，第 $i$ 个测试点满足 $m=i$。

## 提示

可以使用下发文件中的 `chk.cpp` 以检验你的输出的合法性，使用时先将其编译为可执行文件 `chk`（在 Windows 系统下为编译为 `chk.exe`）。

- Linux 系统使用 `./chk <input‐file> <output‐file> <output‐file>` 测试。
- Windows 系统使用 `chk <input‐file> <output‐file> <output‐file>` 测试。

注意上述检验过程只会检验输出的合法性而并不会检验 $n$ 是否是最大的，但你仍需要确保 $1\leq m\leq 10$ 和 $0\leq n\leq 2^m$ 以保证该检验过程正常工作。


