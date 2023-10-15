/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-15 22:19:14
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-15 22:40:43
 * @FilePath: /chino-acm-template/example/modInt/main.cpp
 * @Description: 模整形
 */
#include <bits/stdc++.h>
#include "modInt.h"
using mint = chino::ModInt<7340033>;
int main(int argc, char const *argv[])
{
    mint a = 1, b = 2;
    a /= b;
    printf("%d\n", a.get());
    return 0;
}
