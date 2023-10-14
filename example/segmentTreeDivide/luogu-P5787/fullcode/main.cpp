/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 15:13:05
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-14 17:18:49
 * @FilePath: /chino-acm-template/example/segmentTreeDivide/luogu-P5787/fullcode/main.cpp
 * @Description: 线段树分治模板题
 */
#include <bits/stdc++.h>
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

        /**
         * @description: 构造一个尺寸为N的可回滚数组
         * @param {int} N 尺寸
         */
        rollbackArray(int N)
        {
            data.resize(N);
        }

        /**
         * @description: 根据std::vector构造
         * @param {vector<T>} data_ 输入数据
         */
        rollbackArray(std::vector<T> data_)
        {
            data = std::move(data_);
        }

        /**
         * @description: 根据c语言原始数组构造
         * @param {vector<T>} data_ 输入数据
         * @param {int} N 数组长度
         */
        rollbackArray(T data_[], int N)
        {
            data.resize(N);
            for (auto i = 0; i < N; ++i)
            {
                data[i] = data_[i];
            }
        }

        /**
         * @description: 数组取值
         * @param {size_t} idx 数组下标
         * @return {T}
         */
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

        /**
         * @description: 强制类型转换为std::vector
         * @return rollbackArray中的数据
         */
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
        int father;  //父节点
        int rank;    //秩
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
namespace chino
{
    //!!使用前需要填充所有的外部接口
    // T类型，操作标记，储存任何有关操作的数据
    template <typename T>
    class segmentTreeDivide
    {
    public:
        // 外部接口：
        std::function<void(const T &oper)> doOperator; // 外部接口：如何处理一个操作标记？（传入addOperator添加的操作标记）
        std::function<void()> saveState;               // 外部接口：当处理完成线段树某节点上的所有标记时，如何储存当前状态？
        std::function<void()> loadState;               // 外部接口：当线段树递归完成左子树操作时，如何回溯？
        std::function<void(int pos)> solveNotify;      // 外部接口：当求解完成时（递归到叶子结点），需要做何种操作？传入当前叶子结点下标）

    private:
        int N;
        std::vector<std::vector<T>> opers;

        /**
         * @description:   类似线段树修改操作，将一个区间操作[l,r]拆解为至多2*logN个操作
         * @param {int} l  修改区间的左端点
         * @param {int} r  修改区间的右端点
         * @param {const T&} oper 修改区间的操作标记
         * @param {int} root 线段树遍历的当前根节点（调用者无需关注）
         * @param {int} L    线段树节点的左端点（调用者无需关注）
         * @param {int} R    线段树节点的右端点（调用者无需关注）
         */
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

        /**
         * @description: 线段树分治核心逻辑，实际上就是一次二叉树的先序遍历。
         * @param {int} root 线段树遍历当前根节点（调用者无需关注）
         * @param {int} L    线段树节点的左端点（调用者无需关注）
         * @param {int} R    线段树节点的右端点（调用者无需关注）
         */
        void slove_(int root, int L, int R)
        {
            // 按照懒标记处理修改
            for (const auto &i : opers[root])
            {
                doOperator(i);
            }

            // 达到线段树叶子节点，通知问题已经解决
            if (L == R)
            {
                solveNotify(L);
                return;
            }
            // 否则非叶子结点，首先记录保存当前状态
            saveState();

            auto mid = (L + R) >> 1;
            // 递归先解决左侧问题
            slove_(root << 1, L, mid);
            // 解决完成后撤销修改
            loadState();

            // 撤销后解决右侧问题
            slove_((root << 1) | 1, mid + 1, R);
        }

    public:
        segmentTreeDivide(int N_) : N(N_)
        {
            opers.resize((N + 1) << 2);
        }

        /**
         * @description:   类似线段树修改操作，将一个区间操作[l,r]拆解为至多2*logN个操作
         * @param {int} l  修改区间的左端点
         * @param {int} r  修改区间的右端点
         * @param {const T&} oper 修改区间的操作标记
         */
        void addOperator(int l, int r, const T &oper)
        {
            addOperator_(l, r, oper, 1, 0, N);
        }

        /**
         * @description: 线段树分治核心逻辑，实际上就是一次二叉树的先序遍历。
         * 在求解完成时，通过solveNotify 外部接口通知外部调用者求解完成。
         */
        void slove()
        {
            slove_(1, 0, N);
        }
    };
}
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