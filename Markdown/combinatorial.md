# -J

## Problem 47

对于单次扔硬币，假设 $Alice$ 先扔

则 $Alice$ 获胜概率为 $\sum\limits_{k=1}^{+\infty} 2^{-2k+1}$

$Bob$ 获胜概率为 $\sum\limits_{k=1}^{+\infty} 2^{-2k}$

$\therefore P(Alice)=2P(Bob)$ ，$P(Alice)+P(Bob)=1$

$\therefore P(Alice)=\frac{2}{3}$ ，$P(Bob)=\frac{1}{3}$

设 $D_{i,j}$ 表示人 $i$ $(i=0:Alice;\ else : Bob)$ 在第 $j$ 局中获胜的概率

$\therefore D_{i,j}=\sum\limits_{k\in[1.2]}\frac{1+[k\not=i]}{3} D_{k,j-1}$

又 $D_{0,1}=\frac{2}{3},D_{1,1}=\frac{1}{3}$

$After calculate:$

$D_{0,k}=\frac{\lfloor\frac{3^k+[k \equiv 1 (\text{ mod }2)]}{2}\rfloor}{3^k}$ 

$\therefore ans=D_{0,6}=\frac{364}{729}$

# -S

## Problem 3

容斥原理

$ans=\sum\limits_{0\le k\le n} \frac{(-1)^k\binom{n}{k}3^k(3n-k)!}{2n!}$

## Problem 4

$ans=\sum\limits_{i\le 10,j\le 9} \binom{i+1}{j}\binom{11-i}{9-j}$

## Problem 12

$\because 3|30$ $\therefore  (x\ \text{mod}\ 3)=(y\ \text{mod}\ 3)=(z\ \text{mod}\ 3)=1$ 或 $2$

$1.$ $x\ \text{mod}\ 3=1$

$\therefore ans=\binom{(30-3)/3+2}{2}=\binom{11}{2}$

$2.$ $x\ \text{mod}\ 3=2$

$\therefore ans=\binom{(30-6)/3+2}{2}=\binom{10}{2}$

综上 $ans=\binom{11}{2}+\binom{10}{2}$

## Problem 13

$[1,9]\cap N^*$ 中，$2$ 的倍数有 $4$ 个，$5$ 的倍数有 $1$ 个

$1.$ $a,b,c$ 中有 $1$ 个 $5$ 的倍数

$ans_1=\binom{3}{1}\left(4^2\times2+4^2\right)$

$=144$

$2. a,b,c$ 中有 $2$ 个 $5$ 的倍数

$ans_2=\binom{3}{2}\times 4=12$

$\therefore ans=180+12=156$

## Problem 14

$ans=\frac{3^8-3(2^8)+3}{6}=966$

## Problem 15

$ans=2^n\binom{n}{k}$

## Problem 16*

法 $1$

```cpp
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    unordered_set<string> us;
    string s="AAAAABBBBBCCCCC";
    do{
        [&](){
            cir(i,0,5) if(s[i]=='A') return;
            cir(i,5,10) if(s[i]=='B') return;
            cir(i,10,15) if(s[i]=='C') return;
            us.insert(s);
        }();
    }while(next_permutation(s.begin(),s.end()));
    cout<<us.size()<<'\n';
    return 0;
}

```

法 $2$

设前 $5$ 个字符中有 $x$ 个 $B$ ，则有 $5-x$ 个 $C$

则中间 $5$ 个字符中有 $x$ 个 $C$ 和 $5-x$ 个 $A$

后 $5$ 个字符中有 $x$ 个 $A$ 和 $5-x$ 个 $C$

$\therefore ans=\sum\limits_{k=0}^5\binom{5}{k}^3=2252$  

## Problem 21

原式 $=\sum\limits_{s\subset S}\left(\sum\limits_k^{|s|}\binom{|s|}{k}2^{(n-|s|)}\right)|s|$

$=\sum\limits_{s\subset S}(2^{n-|s|})\left(\sum\limits_k^{|s|}\binom{|s|}{k}\right)|s|$

$\because[$ 例 $36\ ]$ 

$=\sum\limits_{s\subset S} (2^{n-|s|})(2^{|s|})|s|$ 

$=n\cdot 4^{n-1}$

$Q.E.D$

## Problem 22*

在前 $n+1$ 个形如 $101010101\cdots0101$ 的数中，至少有 $2$ 个 $\text{mod}\ n$ 相同

这两个数的差为 $1010101\cdots0101\times 10^x$

设这两个数的差 $/\ 10^x=w$ 

$\because 2\nmid n\and 5 \nmid n$

$\therefore \gcd(10^x,n)=1$

$\because n|w\times10^x \Longrightarrow n|w$

$Q.E.D$

## Problem 23

设这个数字为 $\overline{n_1n_2n_3\cdots n_{16}}$

设 $all_j=\prod\limits_{k}^j n_j\ \text{mod}\ 2^2\cdot3^2\cdot 5^2\cdot 7^2$ 

则 $\forall j\in [1,16]\cap N^*$ 有 $all_j=2^a\cdot3^b\cdot5^c\cdot7^d$

$(1)$ $\exist j$ 使得 $a_j=b_j=c_j=d_j=0$ 此时前 $j$ 位为完全平方数

$(2)$ $\forall j$ 有 $a_j>0\or b_j>0\or c_j>0\or d_j>0$

此时有 $15$ 种拆分 $all$ 的方法，则一定

$\exist j,k,j<k$ 使得 $a_j=a_k\and b_j=b_k\and c_j=c_k\and d_j=d_k$

则 $j+1$ 位到 $k$ 位之和位完全平方数

$Q.E.D$

## Problem 24

证明:鸽巢原理

## Problem 25*

在这个平面内截取一个 $4\times(4^3+1)$ 的矩形

则每一行都可以选择涂色方法，总共有 $4^3$ 种涂法

$\because 4^3+1>4^3$ 

$\therefore$ 有 $2$ 行必定相同

可以构成一个四角同色矩形

## Problem 27

我们一定可以如下构造一棵树

$1.$ 建立一棵树 $\varnothing$

$2.$ 加入一个 $root$ 

$3.$ 依次加入 $n-1$ 个节点，并于某个已知节点连边

假设对于 $n-1$ 及以下节点数的树都满足 $\chi(T_{n-1};k)=k(k-1)^{n-2}$

对于 $n=1$ 时满足

只需证对于 $T_n$ 满足即可

往 $T_{n-1}$ 中加入 $n$ 号节点，并向节点 $x$ 连边

则 $n$ 号节点有 $k-1$ 中染色方式

故 $\chi(T_n;k)=k(k-1)^{n-1}$

$Q.E.D$

## Problem 28

不包含环的图一定是一个森林，边数 $\le n-1$

故矛盾

$Q.E.D$

## Problem 35

对于每行有 $3k$ 种可能性

$Q.E.D$

## Problem 36

设 $D_n$ 表示长度为 $n$ 的字符串个数

$D_n=4^n-\sum\limits_k^{n-1} D_k\ge 2^n$ 

$Q.E.D$

## Problem 37

设 $D_n$ 表示第 $1$ 位为 $n$ 的状态数

$D_n=D_{n-1}+D_{n-3}+4n-1$

$n\ge 16$

## Problem 38

$S_{max}=\binom{16}{2}=120$

设有 $a$ 名学生答 $A\cdots$ 

$a+b+c+d=16$

又 $\sum\limits_{x\in \{a,b,c,d\}}\binom{x}{2}\ge 4\binom{4}{2}=24$ $(jensen$ 不等式 $)$

故 $24n\le 120$

$\therefore n\le 5$

$Q.E.D$

## Problem 41

```Err:``` $n=3,m=1$ : $\lfloor\sqrt{2n}\rfloor=2$

$real\ ans=0$

## Problem 42

归纳法:

设对于 $n=k$ 时答案为 $A(k)$

假设对于 $n<k-1$ 的情况都成立

证明 $n=k$ 时也成立

易证 $n=1$ 时成立

下证 $k\ge 2$ 时成立

对于 $n=k-1$ 时的所有可选集合

$1. k\in prime$

$k$ 必选，$(A(k)=A(k-1)) \equiv 1 (\text{mod }2)$ 

$2.k\not\in prime$

$A(k)=A(k-1)+\sum\limits_j m\cdot A(j-1)\cdot2^x$，$x>0\and x\in N^*$ ，$m$ 是常数

$\therefore A(k)=A(k-1)+2j$ ，$j\in N$

$\therefore A(k)\equiv 1 (\text{mod }2)$

综上 $A(k)\equiv 1(\text{mod }2)$

$Q.E.D$

## Problem 43

以任一点为圆心，$1$ 为半径作圆，设圆 $i$ 上的点数为 $c_i$

$ans=\frac{1}{2}\sum\limits_kc_k$

又 $\sum\limits_k\binom{c_k}{2}\le n(n-1)$

$\therefore \Theta(ans)=\Theta(n\sqrt n)$

$Q.E.D$

## Problem 44

改变过后平方和不变

平方和 $S^2=\sum\limits_{k=1}^{2015} k^2$ 不变

又操作后得到的数更加接近

$\Longrightarrow <540$ 次

$Q.E.D$

## Problem 45

归纳法:证明一个点在加入后人任会在优先不内结束

## Problem 46

$k$ 能被无穷个 $x\in N$ 整除 $\Longrightarrow k=0$

$Q.E.D$





