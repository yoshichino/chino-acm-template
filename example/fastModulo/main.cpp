/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-15 15:09:47
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-15 22:41:44
 * @FilePath: /chino-acm-template/example/fastModulo/main.cpp
 * @Description: 快速取模示例
 */
#include <bits/stdc++.h>
#include "fastModulo.h"

int main(int argc, char const *argv[])
{
    Mod64::set_mod(1e9 + 7);
    Mod64 n = 1000, x = 5e8 + 4;
    n = n * x;
    printf("ans: %lld\n", n.get());
    return 0;
}
