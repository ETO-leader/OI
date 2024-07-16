[[DP]] [[位运算]] [[最短路]] [[状态压缩]] [[差分]]

先将整个序列 $\text{xor}$ 差分，区间操作变成操作区间端点.

注意到花费 $k$ 的代价去 

$$
   a_i \leftarrow a_i \text{ xor } 1, a_{i+1} \leftarrow a_{i+1} \text{ xor } 1
$$

等价于花费 $k$ 的代价去

$$
a_1 \leftarrow a_1 \text{ xor } 1, a_k \leftarrow a_k \text{ xor } 1
$$
于是可以最短路预处理出将 $a_x, a_y$ 同时 $\text{xor } 1$ 的最小代价.

显然我们之后的操作只用关注序列中的 $1$.

整个序列在新操作时 $1$ 显然不会变多，于是只有至多 $2\cdot k$ 个 $1$，可以将 $1$ 状压了之后去 dp.

时间复杂度 $\Theta(nml \times k^24^k)$.


