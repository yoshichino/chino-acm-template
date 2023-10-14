/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 02:07:55
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-14 17:20:19
 * @FilePath: /chino-acm-template/template/dataStructure/segmentTreeDivide.h
 * @Description: 线段树分治算法
 */
#include <functional>
#include <vector>
#include <queue>
#include <cstdio>
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

