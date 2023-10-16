/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-16 10:59:46
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-16 11:31:47
 * @FilePath: /chino-acm-template/example/segmentTree/luogu-P3372/main.cpp
 * @Description: 线段树模板
 */
#include <bits/stdc++.h>
#include "segmentTreeSimpleAdd.h"
using namespace std;
int main(int argc, char const *argv[])
{
    int n, m, x, y, k, op;
    vector<int> a;
    scanf("%d %d", &n, &m);
    a.resize(n + 1);
    auto seg = std::move(chino::new_segmentTreeSimpleAdd(n));
    seg.valOfLeaf = [&a](const int &pos, long long &leaf)
    {
        leaf = a[pos];
    };
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    seg.build(n);
    while (m--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d %d %d", &x, &y, &k);
            if (x > y)
            {
                swap(x, y);
            }
            seg.modify(x, y, k);
        }
        else
        {
            scanf("%d %d", &x, &y);
            if (x > y)
            {
                swap(x, y);
            }
            printf("%lld\n", seg.query(x, y));
        }
    }
    return 0;
}
