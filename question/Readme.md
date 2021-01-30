# Question

## RMQ 问题

### 什么是 RMQ 问题？





### 什么是树状数组？

对我来说树状数组来源于一道leetcode的一道贪心算法题([1505. 最多 K 次交换相邻数位后得到的最小整数](https://leetcode-cn.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/))。该问题需一种单点修改和区间查询的数据结构。同时需要满足单点修改和区间查询的复杂度足够小。
<br>[树状数组]是一种用于维护前缀信息的的数据结构. 能在O(log n)下完成**单点修改**与**区间查询**操作。

简单介绍一下单点修改与区间查询：

单点修改： 指定下标下元素与增量d的之和
区间查询： 指定[x,y]下区间和。

