/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-14 19:47:08
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-17 01:48:59
 * @FilePath: /chino-acm-template/template/dataStructure/segmentTreeBase.h
 * @Description: 线段树
 */
#include <functional>
#include <vector>
#include <stack>
namespace chino
{

    template <typename T, typename LT, typename MT>
    class segmentTreeBase
    {
    private:
        int N_;
        int n_;
        std::vector<T> td_;  // tree data
        std::vector<LT> tl_; // tree lazy

        /**
         * @description: 懒标记下推且清理标记
         * @param {int} root 当前节点
         * @param {int} L 当前区间左端点
         * @param {int} R 当前区间右端点
         * @return {*}
         */
        void pushdown_(int root, int L, int R)
        {
            // 如果需要推懒标记
            if (needPush && needPush(tl_[root]))
            {
                // 推标记
                doLazy ? doLazy(tl_[root], td_[root], L, R) : void();
                // 懒标记下放
                if (L != R)
                {
                    pushDownTag ? pushDownTag(tl_[root], tl_[root << 1], tl_[root << 1 | 1]) : void();
                }
                // 标记清空
                clearLazy ? clearLazy(tl_[root]) : void();
            }
        }

        /**
         * @description: 线段树更新数据
         * @param {int} root 当前节点
         * @param {int} L 当前区间左端点
         * @param {int} R 当前区间右端点
         * @return {*}
         */
        void update_(int root, int L, int R)
        {
            auto mid = (L + R) >> 1;
            pushdown_(root << 1, L, mid);
            pushdown_(root << 1 | 1, mid + 1, R);
            td_[root] = std::move(pushUpData(td_[root << 1], td_[root << 1 | 1]));
        }

        /**
         * @description: 线段树建树
         * @param {int} l 当前区级左端点
         * @param {int} r 当前区间右端点
         * @param {int} root 当前节点
         * @return {*}
         */
        void build_(int l, int r, int root)
        {
            clearLazy ? clearLazy(tl_[l]) : void();
            if (l == r)
            {
                valOfLeaf(l, td_[root]);
                return;
            }
            auto mid = (l + r) >> 1;
            build_(l, mid, root << 1);
            build_(mid + 1, r, root << 1 | 1);
            td_[root] = std::move(pushUpData(td_[root << 1], td_[root << 1 | 1]));
        }

        /**
         * @description: 线段树区间修改
         * @param {int} l 修改操作左端点
         * @param {int} r 修改操作右端点
         * @param {int} L 线段树当前区间左端点（外部调用者无需关注）
         * @param {int} R 线段树当前区间右端点（外部调用者无需关注）
         * @param {int} root
         * @param {MT} &val
         * @return {*}
         */
        void modify_(int l, int r, int L, int R, int root, const MT &val)
        {
            pushdown_(root, L, R);
            // 到达递归终点
            if (l <= L && R <= r)
            {
                setLazy ? setLazy(val, tl_[root], L, R) : void();
                return;
            }
            auto mid = (L + R) >> 1;
            if (l <= mid)
                modify_(l, r, L, mid, root << 1, val);
            if (r > mid)
                modify_(l, r, mid + 1, R, root << 1 | 1, val);
            // update
            update_(root, L, R);
        }

        /**
         * @description: 线段树区间查询
         * @param {int} l
         * @param {int} r
         * @param {int} L
         * @param {int} R
         * @param {int} root
         * @return {*}
         */
        T query_(int l, int r, int L, int R, int root)
        {
            pushdown_(root, L, R);
            // 到达递归终点
            if (l <= L && R <= r)
            {
                return td_[root];
            }
            // 不然继续递归，当前节点所表示区间为[L,R]，左子树为[L,mid]，右子树为[mid+1,R]
            auto mid = (L + R) >> 1;
            if (r <= mid)
                return query_(l, r, L, mid, root << 1);
            else if (l > mid)
                return query_(l, r, mid + 1, R, root << 1 | 1);
            else
                return pushUpData(query_(l, mid, L, mid, root << 1), query_(mid + 1, r, mid + 1, R, root << 1 | 1));
        }

    public:
        std::function<void(const int &pos, T &leaf)> valOfLeaf;                                  // 建树时叶子节点如何赋值
        std::function<T(const T &lch, const T &rch)> pushUpData;                                 // 如何上推更新值（区间信息合并）
        std::function<void(const LT &lazy, LT &lch_lz, LT &rch_lz)> pushDownTag;                 // 懒标记如何下放
        std::function<bool(const LT &lazy)> needPush;                                            // 懒标记是否需要下放
        std::function<void(const LT &lazy, T &data, const int &l, const int &r)> doLazy;         // 访问时如何将懒标记数据更新到当前节点
        std::function<void(const MT &modify_val, LT &lazy, const int &l, const int &r)> setLazy; // 修改操作时如何设置懒标记
        std::function<void(LT &lazy)> clearLazy;                                                 // 懒标记如何清空

        segmentTreeBase(int N) : N_(N)
        {
            td_.resize(4 * (N + 5));
            tl_.resize(4 * (N + 5));
        }

        /**
         * @description: 线段树建树
         * @param {int} n 线段树有效区间为[0,n]（多一个方便下标从0或者1开始数）
         * @return {*}
         */
        void build(int n)
        {
            n_ = n;
            build_(0, n_, 1);
        }

        /**
         * @description: 线段树修改
         * @param {int} l 区间修改左端点
         * @param {int} r 区间修改右端点
         * @param {MT} &val 修改的值
         * @return {*}
         */
        void modify(int l, int r, const MT &val)
        {
            modify_(l, r, 0, n_, 1, val);
        }

        /**
         * @description: 线段树查询操作
         * @param {int} l 查询区间左端点
         * @param {int} r查询区间右端点
         * @return {*}
         */
        T query(int l, int r)
        {
            return query_(l, r, 0, n_, 1);
        }
    };

} // namespace chino
