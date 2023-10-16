/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-17 01:41:38
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-17 01:51:30
 * @FilePath: /chino-acm-template/example/segmentTree/luogu-P1083/main.cpp
 * @Description:
 */
#include <bits/stdc++.h>
#include "segmentTreeSimpleMin.h"
using namespace std;
int main(int argc, char const *argv[])
{
    int n, m, d, s, t;
    vector<int> a;
    scanf("%d %d", &n, &m);
    a.resize(n + 1);
    auto seg = std::move(chino::new_segmentTreeSimpleMin(n));
    seg.valOfLeaf = [&a](const int &pos, chino::segmentTreeSimpleMinData &leaf)
    {
        leaf.data = a[pos];
        leaf.id = pos;
    };
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    seg.build(n);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &d, &s, &t);
        seg.modify(s, t, -d);
        if (seg.query(1, n).data < 0)
        {
            printf("-1\n%d\n", i);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}
