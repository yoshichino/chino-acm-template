/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 14:39:01
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-14 17:03:50
 * @FilePath: /chino-acm-template/example/segmentTreeDivide/codeforces-813F/main.cpp
 * @Description: 线段树分治模板题
 */

#include "segmentTreeDivide.h"
#include "rollbackDisjointSetUnion.h"
#include <vector>
#include <cstdio>
#include <map>
#include <iostream>
using namespace std;
const int MAXN = 200005;
struct node
{
    int u, v;
};
bool ans[MAXN];
int main(int argc, char const *argv[])
{
    vector<pair<int, unsigned int>> stk{{1, 0}}; // 是否为二分图 - 可回退并查集当前的时间戳
    int n, q;
    map<pair<int, int>, int> mp;
    chino::rollbackDisjointSetUnion dsu(2 * MAXN);
    scanf("%d %d", &n, &q);
    chino::segmentTreeDivide<node> segtd(q);

    segtd.doOperator = [&](const node &op)
    {
        if (stk[stk.size() - 1].first == 0)
        {
            return;
        }

        dsu.join(op.u, op.v + n);
        dsu.join(op.v, op.u + n);
        if (dsu.find(op.u) == dsu.find(op.u + n) ||
            dsu.find(op.v) == dsu.find(op.v + n))
        {
            stk[stk.size() - 1].first = 0;
        }
    };

    segtd.saveState = [&]()
    {
        auto now = stk[stk.size() - 1];
        stk.push_back({now.first, dsu.getStamp()});
    };

    segtd.loadState = [&]()
    {
        dsu.rollback(stk[stk.size() - 1].second);
        stk.pop_back();
    };

    segtd.solveNotify = [&](int pos)
    {
        ans[pos] = stk[stk.size() - 1].first;
    };

    for (int i = 0; i < q; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        auto iter = mp.find(make_pair(u, v));
        if (iter == mp.end())
        {
            mp[make_pair(u, v)] = i;
            continue;
        }
        segtd.addOperator(iter->second, i - 1, {u, v});
        mp.erase(iter);
    }
    for (auto &iter : mp)
    {
        segtd.addOperator(iter.second, q, {iter.first.first, iter.first.second});
    }
    segtd.slove();
    for (auto i = 0; i < q; ++i)
    {
        printf("%s\n", ans[i] ? "YES" : "NO");
    }

    return 0;
}
/*
3 5
2 3
1 3
1 2
1 2
1 2
*/