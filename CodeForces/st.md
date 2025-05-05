## A
Given three integers $n$, $k$, and $i$, construct a string $s$ of length $n$ such that the $k$-th largest suffix of $s$ is $s[i..n]$.

## B
You had all the numbers in You have all the integers from $l$ to $r$ and are given another $k$. The question is to take the modulus of the sum of the maximum numbers after inverting certain bits of these n numbers exactly $k$ times, and then take the modulus of $998,244353$.
For each number's each binary bit can only be flipped once.
We can only flip the last $m$ bits of the number.

## C
You have a binary tree $T$ , a linked list $l$ , and a pointer $p$ , with $p$initially pointing to the head of the link. You have three operations with a cost of $1$ each: moving the pointer forward, moving the pointer backward, and adding a point after the pointer. Now you can add all $n$ points using any dfs order. What is the minimum cost?

## D
This is an interactive problem

There is a tree with $n$ nodes ($n \le 10^5$) managed by an interactor, and a chip is located at some unknown node. The chip can move, but you only know the value of $n$ — you don’t know the structure of the tree or where the chip is currently located.

You can perform up to 3000 operations in sequence, and each operation consists of the following steps:

Choose a node $u$.

The interactor will return whether the node $u$ has been visited by the chip before, or whether the chip is currently at node $u$.

If the chip is not currently at $u$, it will move one edge closer to $u$.

Your task is to find the current location of the chip.

## E
You are given a graph with $n$ vertices and $m$ edges at first.Then you have $q$ additional edges. After add the $i$-th additional edge.You need to first remove **at most one** edge, then partition the vertices into two sets $A$ and $B$ such that there are no edges connecting the vertices within $A$ and no edges connecting the vertices within $B$.  Two ways are considered different if and only if their sets $A$ are not identical.  Find the number of valid schemes.
**can be divided into 1(for bf),2(for q=0),3**

## F
There is a tree with $n$ nodes, where the $i$-th node on the tree has a color $a_i$.  
You will receive $m$ queries. For the $i$-th query, determine the maximum distance between two nodes with the same color on the shortest path between nodes $u_i$ and $v_i$.

