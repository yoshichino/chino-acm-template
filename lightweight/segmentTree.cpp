/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-16 23:16:02
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-17 00:59:11
 * @FilePath: /chino-acm-template/lightweight/segmentTree.cpp
 * @Description: 线段树，轻量级模板
 */
//luogu-P3372
#include <bits/stdc++.h>
using namespace std;
struct segmentTree
{

    int N_;
    int n_;
    std::vector<long long> td_; // tree data
    std::vector<long long> tl_; // tree lazy

    void pushdown_(int root, int L, int R)
    {
        if (tl_[root])
        {
            td_[root] += (R - L + 1) * tl_[root];
            if (L != R)
            {
                tl_[root << 1] += tl_[root];
                tl_[root << 1 | 1] += tl_[root];
            }
            tl_[root] = 0;
        }
    }

    void update_(int root, int L, int R)
    {
        auto mid = (L + R) >> 1;
        pushdown_(root << 1, L, mid);
        pushdown_(root << 1 | 1, mid + 1, R);
        td_[root] = td_[root << 1] + td_[root << 1 | 1];
    }

    void build_(int l, int r, int root, int a[])
    {
        tl_[root] = 0;
        if (l == r)
        {
            td_[root] = a[l];
            return;
        }
        auto mid = (l + r) >> 1;
        build_(l, mid, root << 1, a);
        build_(mid + 1, r, root << 1 | 1, a);
        td_[root] = td_[root << 1] + td_[root << 1 | 1];
    }

    void modify_(int l, int r, int L, int R, int root, const long long &val)
    {
        pushdown_(root, L, R);
        if (l <= L && R <= r)
        {
            tl_[root] += val;
            return;
        }
        auto mid = (L + R) >> 1;
        if (l <= mid)
            modify_(l, r, L, mid, root << 1, val);
        if (r > mid)
            modify_(l, r, mid + 1, R, root << 1 | 1, val);
        update_(root, L, R);
    }

    long long query_(int l, int r, int L, int R, int root)
    {
        pushdown_(root, L, R);
        if (l <= L && R <= r)
        {
            return td_[root];
        }
        auto mid = (L + R) >> 1;
        if (r <= mid)
            return query_(l, r, L, mid, root << 1);
        else if (l > mid)
            return query_(l, r, mid + 1, R, root << 1 | 1);
        else
            return query_(l, mid, L, mid, root << 1) + query_(mid + 1, r, mid + 1, R, root << 1 | 1);
    }

    segmentTree(int N) : N_(N)
    {
        td_.resize(4 * (N + 5));
        tl_.resize(4 * (N + 5));
    }

    void build(int n, int a[])
    {
        n_ = n;
        build_(0, n_, 1, a);
    }

    void modify(int l, int r, const long long &val)
    {
        modify_(l, r, 0, n_, 1, val);
    }

    long long query(int l, int r)
    {
        return query_(l, r, 0, n_, 1);
    }
};

int main(int argc, char const *argv[])
{
    int n, m, x, y, k, op;
    vector<int> a;
    scanf("%d %d", &n, &m);
    a.resize(n + 1);
    auto seg = segmentTree(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    seg.build(n, a.data());
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
