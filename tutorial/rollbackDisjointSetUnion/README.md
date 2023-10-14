<!--
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 21:41:41
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-14 18:11:43
 * @FilePath: /chino-acm-template/tutorial/rollbackDisjointSetUnion/README.md
 * @Description: 可回退并查集教程
-->
# 可回滚并查集

基于`可回滚并查集`实现的可回退并查集

 ## 该算法的使用条件

一般配合`线段树`分治，达到可并可拆并查集的效果。

## 模板参数说明

`N`:可回滚并查集的长度（注意，首次使用要填入最大长度）

## 接口说明

### 调用接口

`init(int N)` 并查集初始化，注意`N`不能大于算法模板实例化时传入的`N`。
    
`int find(int x)` 并查集查询祖先节点接口

`join(int x, int y)` 并查集合并接口
     
`rollback(unsigned int timestamp)` 并查集回滚接口，回滚到`timestamp`所表示的版本

`unsigned int getStamp()` 并查集获取当前时间戳（版本）接口。

`void rebase()` 变基，相当于清除历史记录。

算法模板源码见：[可回滚并查集模板文件](../../template/dataStructure/rollbackDisjointSetUnion.h) 

## 快速上手

算法模板实例化方式

```c++
chino::rollbackDisjointSetUnion dsu(N); //这里实例化时要填入一个最大值。
```
