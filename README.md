<!--
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 03:00:18
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-10-15 22:07:48
 * @FilePath: /chino-acm-template/README.md
 * @Description: README.md
-->
# 四糸智乃的算法模板

## 前言

退役后一直想找个时间整理算法模板，然后一直咕咕咕。

本模板并非是一个**适合贴模板过题或者现场赛抄的板子**，它并不简短，甚至冗余，以至于产生比较大的常数，在一定程度上做了接口化和封装。

相比真正在赛场中使用的模板，本模板更类似于另一种方式的**算法教程**，以接口化的方式告诉初学者应该如何修改模板，在使用模板时应该如何填写核心逻辑。

## 接口

在使用本模板时，存在两类接口`外部接口`和`调用接口`。

### 外部接口

外部接口指的是**本算法模板中未实现的部分**，需要使用本模板的人提供，通常时一个std::function对象作为回调函数。例如在使用`线段树模板`时，使用者需要提供对于懒标记的下放逻辑外部接口。

### 调用接口

调用接口指的是**本算法模板中已经实现的部分**，是本算法模板中为使用者提供的调用方法。例如在使用`线段树模板`时，区间修改、区间查询就是调用接口。

## 目录结构说明

`example` 模板使用示例代码根目录

`template` 算法模板根目录

`tutorial` 算法教程根目录
``

## 如何使用

请参考`tutorial`目录下的教程，见下文导航

`example`目录下的项目使用cmake进行编译，如果没有cmake，也可以直接编译`example`底层目录`fullcode`为整合好的单文件源码。

## playground

你可以在[playground](./playground/main.cpp)中测试和使用所有的算法模板，playground将默认链接到所有算法模板项目。

## 导航

### 数据结构

[线段树分治](./tutorial/segmentTreeDivide/README.md)

[可回滚数组](./tutorial/rollbackArray/README.md)

[可回滚并查集](./tutorial/rollbackDisjointSetUnion/README.md)

### 数学

[整除分块](./tutorial/divBlock/README.md)

[int64快速取模（网络模板）](./tutorial/fastModulo/README.md)

[int32模整形（网络模板）](./tutorial/modInt/README.md)

### 动态规划

### 字符串处理