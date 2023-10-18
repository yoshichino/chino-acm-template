### 整除分块

整除分块是数论里面一个挺重要的东西，数论入门的时候，积性函数枚举因子，枚举除数，都会用到它。

#### 算法使用条件

当需要枚举 $j=\left\lfloor\frac{N}{i}\right\rfloor$ 时使用

#### 模板参数说明

`n`:被除数

#### 接口说明

#### 调用接口

`long long belone(long long x)` 获取除数为`x`时属于第几块。

`long long l(long long id)` 获取第`id`块的左端点`l`。

`long long r(long long id)` 获取第`id`块的右端点`r`。

`divBlockSegments(long long n, std::function<void(long long id, long long l, long long r)> cb)` 整除分块，遍历每一颗并通过回调函数通知外部。

#### 快速上手

算法模板实例化方式

```c++
chino::divBlock db(n);
```

如果只是想枚举$n$的整除分块，则没必要实例化该算法模板,按照如下方式使用即可。

```c++
chino::divBlockSegments(n, [](long long id, long long l, long long r)
{
    printf("%lld %lld %lld\n",id,l,r);
});
```
`chino::divBlock`保证其接口全部为$O(1)$时间复杂度。当`n`的范围非常大，只需要使用例如$l$到$r$所需的整数分块部分时，可以按照如下写法

```c++
chino::divBlock db(n);
for(auto id=db.belone(l);id<=db.belone(r);++id)
{
    printf("%lld %lld %lld\n",id,db.l(id),db.r(id));
}
```

算法模板源码见：[整除分块模板文件](../../template/math/divBlock.h) 

使用示例见：[整除分块使用示例](../../example/divBlock/main.cpp) 