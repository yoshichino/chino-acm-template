#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct rollbackArray
{
    std::vector<T> data;
    std::vector<std::pair<unsigned int, T>> stk;

    rollbackArray(){};

    rollbackArray(int N)
    {
        data.resize(N);
    }

    T at(const size_t idx) const &
    {
        return data[idx];
    }

    void set(const size_t idx, const T &val, bool commit = true)
    {
        if (commit)
        {
            stk.emplace_back(idx, data[idx]);
        }
        data[idx] = val;
    }

    void rebase()
    {
        stk.clear();
    }

    void rollback(unsigned int timestamp)
    {
        if (timestamp < 0)
        {
            rebase();
        }
        while (stk.size() > timestamp)
        {
            auto temp = stk[stk.size() - 1];
            data[temp.first] = temp.second;
            stk.pop_back();
        }
    }

    unsigned int getStamp() const
    {
        return stk.size();
    }
};

struct rollbackDisjointSetUnionNode
{
    int father;
    int rank;
};

struct rollbackDisjointSetUnion
{

    rollbackArray<rollbackDisjointSetUnionNode> data;

    rollbackDisjointSetUnion(int N)
    {
        data = rollbackArray<rollbackDisjointSetUnionNode>(N + 1);
        for (auto i = 0; i <= N; ++i)
        {
            data.set(i, {i, 0}, false);
        }
    }

    void init(int N)
    {
        for (auto i = 0; i <= N; ++i)
        {
            data.set(i, {i, 0}, false);
        }
        data.rebase();
    }

    int find(int x)
    {
        return data.at(x).father == x ? x : find(data.at(x).father);
    }

    void join(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return;
        }

        auto rx = data.at(x).rank;
        auto ry = data.at(y).rank;
        if (rx > ry)
        {
            std::swap(x, y);
            std::swap(rx, ry);
        }
        data.set(y, {y, ry + (rx == ry)});
        data.set(x, {y, rx});
    }

    void rollback(unsigned int timestamp)
    {
        data.rollback(timestamp);
    }

    unsigned int getStamp() const
    {
        return data.getStamp();
    }

    void rebase()
    {
        data.rebase();
    }
};
struct node
{
    int u, v;
};
const int MAXN = 400005;
bool ans[MAXN];
rollbackDisjointSetUnion dsu(2 * MAXN);
int n,m,k;
struct segmentTreeDivide
{

    int N;
    std::vector<std::vector<node>> opers;

    void addOperator_(int l, int r, const node &oper, int root, int L, int R)
    {
        if (l == L && r == R)
        {
            opers[root].push_back(oper);
            return;
        }
        auto mid = (L + R) >> 1;
        if (r <= mid)
        {
            addOperator_(l, r, oper, root << 1, L, mid);
        }
        else if (l > mid)
        {
            addOperator_(l, r, oper, (root << 1) | 1, mid + 1, R);
        }
        else
        {
            addOperator_(l, mid, oper, root << 1, L, mid);
            addOperator_(mid + 1, r, oper, (root << 1) | 1, mid + 1, R);
        }
    }

    void slove_(int root, int L, int R, bool flag)
    {
        unsigned int time_stamp;
        for (const auto &i : opers[root])
        {
            dsu.join(i.u, i.v + n);
            dsu.join(i.v, i.u + n);
            if (dsu.find(i.u) == dsu.find(i.u + n) ||
                dsu.find(i.v) == dsu.find(i.v + n))
            {
                flag = 0;
                return;
            }
        }
        if (L == R)
        {
            ans[L] = true;
            return;
        }
        time_stamp = dsu.getStamp();

        auto mid = (L + R) >> 1;

        slove_(root << 1, L, mid, flag);

        dsu.rollback(time_stamp);

        slove_((root << 1) | 1, mid + 1, R, flag);
    }

public:
    segmentTreeDivide(int N_) : N(N_)
    {
        opers.resize((N + 1) << 2);
    }

    void addOperator(int l, int r, const node &oper)
    {
        addOperator_(l, r, oper, 1, 0, N);
    }

    void slove()
    {
        slove_(1, 0, N, 1);
    }
};
int main(int argc, char const *argv[])
{
    scanf("%d %d %d", &n, &m, &k);
    segmentTreeDivide segtd(k);
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