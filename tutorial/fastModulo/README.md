### int64快速取模
模板来自日本友人，无命名空间封装

#### 该算法的使用条件

奇质数取模，仅使用加法和乘法的情况下，卡常。使用本模板加速。

#### 接口说明

#### 外部接口

#### 调用接口

`void set_mod(u64 m)` 设置模数，一定要在使用之前调用。

`u64 get()` 转换为uint64类型(unsigned long long)


#### 快速上手

```c++
Mod64::set_mod(1e9 + 7);
Mod64 n = 1000, x = 5e8 + 4;
n = n * x;
n = n + x;
```

算法模板源码见：[int64快速取模算法模板文件](../../template/math/fastModulo.h) 
使用示例见：[int64快速取模使用示例](../../example/fastModulo/main.cpp) 