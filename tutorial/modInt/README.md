### int32模整形
取模整数，来自网络模板

#### 该算法的使用条件

质数取模的情况下，怕忘记取模。

模数必须在编译期给定，不可为scanf输入的变量。

#### 接口说明

#### 调用接口

`int get()` 转换为int类型


#### 快速上手

```c++
using mint=chino::ModInt<7340033>;
//接下来当成正常的int使用即可
//例如
mint a = 1, b = 2;
a /= b;
printf("%d\n", a.get());
```

算法模板源码见：[int32模整形算法模板文件](../../template/math/modInt.h) 
使用示例见：[int32模整形使用示例](../../example/modInt/main.cpp) 