下面列出 **11 个** 高质量、覆盖面广的资源（至少涵盖全枚举、有标号/无标号、有根/无根树、DAG、有向/无向图、欧拉图、环计数等），供你系统化地学习和查阅「图论计数」及「杨表」相关内容。每个条目后均给出简要说明，并附上对应来源，供进一步深入。

## 资源列表

1. **图论计数 – OI Wiki**  
    覆盖有标号图的连通图、欧拉图、二分图等子类计数，介绍生成函数与递推公式，包含 SPOJ KPGRAPHS 等例题。 ([图论计数 - OI Wiki](https://oi-wiki.org/math/combinatorics/graph-enumeration/?utm_source=chatgpt.com))
    
2. **欧拉图 – OI Wiki**  
    定义欧拉路径/回路与欧拉图、半欧拉图概念，并在生成函数框架下讨论有标号欧拉图的枚举方法。 ([欧拉图 - OI Wiki](https://oi-wiki.org/graph/euler/?utm_source=chatgpt.com))
    
3. **环计数问题 – OI Wiki**  
    重点讲解三元环（3‐cycle）的枚举以及如何进行有向/无向图中的环计数，配以 DP 与生成函数技巧。 ([环计数问题 - OI Wiki](https://oi-wiki.org/graph/rings-count/?utm_source=chatgpt.com))
    
4. **soj299 树计数**  
    包含对 **有标号/无标号、有根/无根** 树的计数，详细给出生成函数、欧拉变换（Pólya Exp）及模块化处理方法。 ([[soj299]树计数](https://yhx-12243.github.io/OI-transit/index.html?redirect=460&utm_source=chatgpt.com))
    
5. **Luogu P6295 有标号 DAG 计数**  
    对弱连通的有标号有向无环图进行计数，基于容斥与拓扑枚举的 DP 推导，并演示多项式优化。
    
    - 题目描述（弱连通 DAG） ([P6295 有标号DAG 计数- 洛谷](https://www.luogu.com.cn/problem/P6295?utm_source=chatgpt.com))
        
    - 容斥推导详解 （yssubt62） ([题解P6295 【有标号DAG 计数】 - 洛谷专栏](https://www.luogu.com.cn/article/yssubt62?utm_source=chatgpt.com), [题解P6295 【有标号DAG 计数】 - 洛谷专栏](https://www.luogu.com.cn/article/l8aczm7k?utm_source=chatgpt.com))
        
6. **Luogu P7364 有标号二分图计数**  
    P6295 的同系列题目，专注于**有标号二分图**的枚举方法，推荐在 P4233 的笔记中查看链接。 ([P4233 射命丸文的笔记 - 洛谷](https://www.luogu.com.cn/problem/P4233?utm_source=chatgpt.com))
    
7. **Prüfer 码讲义 – Paul Johnson / PTWiddle**  
    从算法与组合双重视角，证明并构造 **Cayley 公式**，对 **有标号树（有根/无根）** 的枚举给出完整 Bijective 证明。
    
    - Lecture 8: Prüfer code ([Lecture 8: Prüfer code - Paul Johnson](https://ptwiddle.github.io/MAS341-Graph-Theory-2017/lecturenotes/lecture8.html?utm_source=chatgpt.com))
        
    - Prüfer Codes 详细笔记 ([Prüfer Codes](https://ptwiddle.github.io/Graph-Theory-Notes/s_graphalgorithms_prufer.html?utm_source=chatgpt.com))
        
8. **多项式计数杂谈 – Luogu 专栏**  
    深入探讨生成函数（EGF/OGF）在 **DAG 计数** 中的应用，引入弱连通拆分与取对数技巧。 ([多项式计数杂谈- 洛谷专栏](https://www.luogu.com.cn/article/oy8l7j3n?utm_source=chatgpt.com))
    
9. **简单计数题 – Luogu 题单 (2019)**  
    整理了各类计数 DP、Pólya 定理、Burnside 引理等题目，包含有标号 DAG、部分类无标号图计数。 ([简单计数题- 题单- 洛谷| 计算机科学教育新生态](https://www.luogu.com.cn/training/148579?utm_source=chatgpt.com), [题目列表- 洛谷| 计算机科学教育新生态](https://www.luogu.com.cn/problem/list?page=1&tag=259&utm_source=chatgpt.com))
    
10. **生成函数之 OGF & EGF – Luogu 专栏**  
    讲解有根二叉树、卡特兰数、拉格朗日反演等在 **无标号/有标号树** 计数中的技巧，适合作为树枚举进阶。 ([生成函数之OGF & EGF - 从入门到入土- 题单 - 洛谷](https://www.luogu.com.cn/training/65708?utm_source=chatgpt.com))
    
11. **SPOJ KPGRAPHS Counting Graphs**  
    原题涵盖 **有标号连通图、欧拉图、二分图** 等多种子类的生成函数与递推，OI Wiki 上有完整解析。 ([图论计数 - OI Wiki](https://oi-wiki.org/math/combinatorics/graph-enumeration/?utm_source=chatgpt.com))
    

---

以上资源几乎涵盖了 OI 中所有常见的图枚举分类（有/无标号、有根/无根、DAG、有向/无向、环/欧拉/连通图等）及背后的组合/生成函数方法，足以构建一个「全面」的专题训练与参考库。祝你学习顺利！