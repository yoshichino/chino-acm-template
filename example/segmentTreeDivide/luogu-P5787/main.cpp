/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 02:54:31
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-14 17:22:09
 * @FilePath: /chino-acm-template/example/segmentTreeDivide/luogu-P5787/main.cpp
 * @Description: 线段树分治模板题
 */
#include "segmentTreeDivide.h"
#include "rollbackDisjointSetUnion.h"
#include <vector>
#include <cstdio>
using namespace std;
const int MAXN = 400005;
struct node
{
    int u, v;
};
bool ans[MAXN];
int main(int argc, char const *argv[])
{
    vector<pair<int, unsigned int>> stk{{1, 0}}; // 是否为二分图 - 可回退并查集当前的时间戳
    int n, m, k;
    chino::rollbackDisjointSetUnion dsu(2 * MAXN);

    scanf("%d %d %d", &n, &m, &k);
    chino::segmentTreeDivide<node> segtd(k);
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
            //first中储存的是答案，first=0表示当前非二分图，first=1表示当前为二分图
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
    while (m--)
    {
        int u, v, l, r;
        scanf("%d %d %d %d", &u, &v, &l, &r);
        if (l == r)
        {
            continue;
        }
        segtd.addOperator(l, r - 1, {u, v});
    }
    segtd.slove();
    for (auto i = 0; i < k; ++i)
    {
        printf("%s\n", ans[i] ? "Yes" : "No");
    }

    return 0;
}

/*
3 3 3
1 2 0 2
2 3 0 3
1 3 1 2
*/