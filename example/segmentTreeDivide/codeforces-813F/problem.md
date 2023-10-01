# Bipartite Checking

## 题面翻译

给你一个由n个顶点组成的无向图，最初在图中没有边。同时给你q次查询，每次查询时会向图中添加一个无向边或者删除一个无向边。 在每次查询之后，您必须检查结果图是否为二分图（在保证没有连接相同颜色的两个顶点的边的条件下，您可以将图的所有顶点绘制为两种颜色）

Translated by @吉良吉影

## 题目描述

You are given an undirected graph consisting of $ n $ vertices. Initially there are no edges in the graph. Also you are given $ q $ queries, each query either adds one undirected edge to the graph or removes it. After each query you have to check if the resulting graph is bipartite (that is, you can paint all vertices of the graph into two colors so that there is no edge connecting two vertices of the same color).

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2<=n,q<=100000 $ ).

Then $ q $ lines follow. $ i $ th line contains two numbers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}<y_{i}<=n $ ). These numbers describe $ i $ th query: if there is an edge between vertices $ x_{i} $ and $ y_{i} $ , then remove it, otherwise add it.

## 输出格式

Print $ q $ lines. $ i $ th line must contain YES if the graph is bipartite after $ i $ th query, and NO otherwise.

## 样例 #1

### 样例输入 #1

```
3 5
2 3
1 3
1 2
1 2
1 2
```

### 样例输出 #1

```
YES
YES
NO
YES
NO
```