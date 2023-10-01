/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 15:13:05
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-01 15:14:07
 * @FilePath: /chino-acm-template/example/segmentTreeDivide/luogu-P5787/fullcode/main.cpp
 * @Description: 线段树分治模板题
 */

#include <functional>
#include <vector>
#include <queue>
#include <cstdio>
namespace chino
{
    template <typename T>
    class segmentTreeDivide
    {
    private:
        int N;
        std::vector<std::vector<T>> opers;
        std::function<void(const T &oper)> doOperator;
        std::function<void()> saveState;
        std::function<void()> loadState;
        std::function<void(int pos)> solveNotify;
 
        void addOperator_(int l, int r, const T &oper, int root, int L, int R)
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
        void slove_(int root, int L, int R)
        {
            if (doOperator)
            {
                for (const auto &i:opers[root])
                {
                    doOperator(i);
                }
            }
            if (L == R)
            {
                if (solveNotify)
                {
                    solveNotify(L);
                }
                return;
            }
            if (saveState)
            {
                saveState();
            }
 
            auto mid = (L + R) >> 1;
            slove_(root << 1, L, mid);
            if (loadState)
            {
                loadState();
            }
            slove_((root << 1) | 1, mid + 1, R);
        }
 
    public:
        segmentTreeDivide(
            int N_,
            std::function<void(const T &oper)> doOperator_,
            std::function<void()> saveState_,
            std::function<void()> loadState_,
            std::function<void(int pos)> solveNotify_) : N(N_),
                                                         doOperator(std::move(doOperator_)),
                                                         saveState(std::move(saveState_)),
                                                         loadState(std::move(loadState_)),
                                                         solveNotify(std::move(solveNotify_))
        {
            opers.resize((N + 1) << 2);
        }
 
        void addOperator(int l, int r, const T &oper)
        {
            addOperator_(l, r, oper, 1, 0, N);
        }
 
        void slove()
        {
            slove_(1, 0, N);
        }
    };
}
#include <vector>
namespace chino
{
    template <typename T>
    class rollbackArray
    {
    private:
        std::vector<T> data;
        std::vector<std::pair<unsigned int, T>> stk;
 
    public:
        rollbackArray() = default;
 
        rollbackArray(int N)
        {
            data.resize(N);
        }
 
        rollbackArray(std::vector<T> data_)
        {
            data = std::move(data_);
        }
 
        rollbackArray(T data_[], int N)
        {
            data.resize(N);
            for (auto i = 0; i < N; ++i)
            {
                data[i] = data_[i];
            }
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
 
        operator std::vector<T>() const
        {
            return data;
        }
 
        size_t size() const
        {
            return data.size();
        }
    };
}
 
 
namespace chino
{
 
    struct rollbackDisjointSetUnionNode
    {
        int father;
        int rank;
    };
 
    class rollbackDisjointSetUnion
    {
    private:
        chino::rollbackArray<rollbackDisjointSetUnionNode> data;
 
    public:
        rollbackDisjointSetUnion(int N)
        {
            data = std::move(chino::rollbackArray<rollbackDisjointSetUnionNode>(N + 1));
            for (auto i = 0; i <= N; ++i)
            {
                data.set(i, {i, 1}, false);
            }
        }
 
        void init(int N)
        {
            N = std::min(N, (int)data.size() - 1);
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
}
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
    vector<pair<int, unsigned int>> stk{{1, 0}}; //是否为二分图 - 可回退并查集当前的时间戳
    int n, q;
    map<pair<int, int>, int> mp;
    chino::rollbackDisjointSetUnion dsu(2 * MAXN);
    auto doOperator = [&](const node &op)
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
    auto saveState = [&]()
    {
        auto now = stk[stk.size() - 1];
        stk.push_back({now.first, dsu.getStamp()});
    };
    auto loadState = [&]()
    {
        dsu.rollback(stk[stk.size() - 1].second);
        stk.pop_back();
    };
    auto solveNotify = [&](int pos)
    {
        ans[pos] = stk[stk.size() - 1].first;
    };
    scanf("%d %d", &n, &q);
    chino::segmentTreeDivide<node> segtd(q, doOperator, saveState, loadState, solveNotify);
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
3 3 3
1 2 0 2
2 3 0 3
1 3 1 2
*/