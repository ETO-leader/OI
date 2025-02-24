
| Date          | Problem    | Score                | Reason                                                                                                                          |
| ------------- | ---------- | -------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| 31 Dec, 2024  | domino     | $55 \rightarrow 0$   | `auto operator[](auto)` 的定义在 GCC 9.4.0 和 GCC 7.5.0 是不支持的，导致 CE                                                                  |
| 10 Feb, 2025  | perm       | $100 \rightarrow 88$ | `__builtin_popcount(unsigned)` 和 `__builtin_popcountll(unsigned long long)` 是不同的，导致 WA                                          |
| 11 Feb, 2025  | partial    | $75 \rightarrow 50$  | 类内成员在构造函数中未初始化不会有 warning，且 `-fsanitize` 会改变程序行为，且初始值依赖编译器，导致 WA                                                                |
| 13 Feb, 2025  | pub        | $15 \rightarrow 10$  | 输出样例错误粘贴，导致 WA                                                                                                                  |
| 13 Feb, 2025  | ono        | $8 \rightarrow 0$    | 理应输出 $n$ 个 `0` 但是输出了 $m$ 个，导致 WA                                                                                                |
| 21 Feb, 2025  | dag        | $40 \rightarrow 25$  | $n \le 2 \times 10^5$ 只初始化了 $10^5$，导致 TLE                                                                                       |
| 21 Feb, 2025  | pnc        | $100 \rightarrow 0$  | 没有写 spj / gen 与极弱样例导致的多个错误 1. 树剖访问 `bottom` 应用 `bottom[top[u]]` 而不是 `bottom[u]` 2. 错误处理了答案 3. 该开 $64\text{-bit}$ `int` 没开，导致 WA |
| 21 Feb, 2025  | rochelimit | $48 \rightarrow 40$  | 错误的认为 `std::__gcd(x,y)` 可以正确的处理负数实际上不能，导致 WA                                                                                    |
| 22 Feb, 2025  | flow       | $100 \rightarrow 45$ | 被卡常，导致 TLE: 做法不够优秀                                                                                                              |
| 24 Oct, 2024  | unnamed    | $100 \rightarrow 50$ | 该开 $64\text{-bit}$ `int` 没开，没有在需要排序的情况下对 $O(\sqrt n)$ 求出的约数排序，导致 WA                                                             |
| 02 Nov, 2024  | set        | $100 \rightarrow 90$ | 被卡常，导致 TLE: 哈希不够优秀，没有快读                                                                                                         |
| 18, Nov, 2024 | memory     | $100 \rightarrow 60$ | 被卡常，导致 TLE: xyd 特性? 两发单点相差 1s                                                                                                   |
| 20, Nov, 2024 | substr     | $100 \rightarrow 90$ | 被卡常，导致 TLE: 随机撒点撒太多了                                                                                                            |
| 23, Nov, 2024 | array      | $51 \rightarrow 26$  | 更好的做法没交上去                                                                                                                       |
| 27, Nov, 2024 | garden     | $100 \rightarrow 90$ | 没去重，导致 WA                                                                                                                       |
| 27, Nov, 2024 | rand       | $???$                | 太唐了所以记录: 多项式除二项式可以直接 $O(n)$ 除而不是写 poly                                                                                          |
|               |            |                      |                                                                                                                                 |
