
我们均认为 $k,j << n$

| 函数                          | 卷上的函数                      | 结果                                    | 题目       | 复杂度               |
| --------------------------- | -------------------------- | ------------------------------------- | -------- | ----------------- |
| $\mu$                       | $\text{Id}_0$              | $\epsilon$                            | Q8.2.2.1 | $O(n^{2/3})$      |
| $\varphi$                   | 同下                         | 同下                                    | Q8.2.2.1 | $O(n^{2/3})$      |
| $\text{Id}_k \cdot \varphi$ | $\text{Id}_k$              | $\text{Id}_{k+1}$                     | H8.2.2.3 | $O(n^{2/3})$      |
| $\sigma_k$                  | $\mu$                      | $\text{Id}_k$                         | H8.2.2.2 | $O(n^{2/3})$      |
| $\text{Id}_k \cdot \mu$     | $\text{Id}_k$              | $\text{Id}_k \cdot \epsilon=\epsilon$ | /        | $O(n^{2/3})$      |
| $\text{Id}_j\cdot \sigma_k$ | $\text{Id}_k\cdot \varphi$ | $\text{Id}_{k+j}$                     | /        | $O(n^{3/4})$ (疑似) |

