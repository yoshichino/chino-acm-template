### 可回滚数组

可回滚数组用于`可回滚并查集`、`可回滚链表`等数据结构的底层存储结构，同时也可用于某些需要回滚操作的场景下。

#### 该算法的使用条件

1、该场景的回滚操作必须具备`O(1)`或者均摊`O(1)`的时间复杂度。

#### 模板参数说明

`T`:可回滚数组中存储的数据类型

`N`:可回滚数组的长度

#### 接口说明

#### 调用接口

`T at(const size_t idx)` 数组取值，相当于`a[idx]`

`set(const size_t idx, const T &val, bool commit)` 数组赋值，相当于`a[idx] = T`，其中`commit`表示是否需要记录为一次可回退操作。
       
`rebase()` 数组变基，相当于清除所有操作记录。

`rollback(unsigned int timestamp)` 回退到 `timestamp` 所记录的版本。

`unsigned int getStamp()` 获取当前可回退数组的时间戳（版本）。

`size_t size()` 获取数组长度

算法模板源码见：[可回滚数组模板文件](../../template/dataStructure/rollbackArray.h) 

#### 快速上手

算法模板实例化方式

```c++
//第一种方式
chino::rollbackArray<T> arr(N);
//第二种方式
std::vector<T> vec;
chino::rollbackArray<T> arr(vec);
//第三种方式
T a[N];
chino::rollbackArray<T> arr(a,N);
```

与std::vector的互相转换

```c++
chino::rollbackArray<T> arr(N);
std::vector<T>vec = arr;
```