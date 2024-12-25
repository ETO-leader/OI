给定长度为 $n$ 的序列 $a$ 和 $c$，给定正整数 $k$ 和 $d$.

你需要选出恰好 $m$ 个区间 $[l_1,r_1],\cdots,[l_m,r_m]$，满足:

1. $l_i\ge r_{i-1}+d$
2. $|\left\{c_x|(\exist i, x\in [l_i,r_i])\land x \in \mathbb{N}^*\right\}| \ge k$

求 $\max\left(\sum\limits_{i=1}^m \mathop{MEX}(a_{l_i},\cdots,a_{r_i})\right)$.

无解则为 $-1$.

$n, m, d \le 1000$，$k \le 4$

