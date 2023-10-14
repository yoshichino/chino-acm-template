/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 00:58:13
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-14 18:21:03
 * @FilePath: /chino-acm-template/template/dataStructure/rollbackDisjointSetUnion.h
 * @Description: 可回滚并查集
 */
#include "rollbackArray.h"
#include <cstdlib>
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
        /**
         * @description: 可回滚并查集算法模板构造函数，传入一个最大值N
         * @param {int} N 算法模板使用的最大值N
         * @return {*}
         */
        rollbackDisjointSetUnion(int N)
        {
            data = std::move(chino::rollbackArray<rollbackDisjointSetUnionNode>(N + 1));
            for (auto i = 0; i <= N; ++i)
            {
                data.set(i, {i, 1}, false);
            }
        }

        /**
         * @description: 可回滚并查集初始化
         * @param {int} N需要初始化的长度
         * @note 实际初始化的元素为从0到N，多一个方便不同题目的下标从0或者从1开始。
         * @return {*}
         */
        void init(int N)
        {
            N = std::min(N, (int)data.size() - 1);
            for (auto i = 0; i <= N; ++i)
            {
                data.set(i, {i, 0}, false);
            }
            data.rebase();
        }

        /**
         * @description: 并查集查找代表元素
         * @param {int} x 
         * @return {*}
         */
        int find(int x)
        {
            return data.at(x).father == x ? x : find(data.at(x).father);
        }

        /**
         * @description: 并查集合并
         * @param {int} x 
         * @param {int} y 
         * @return {*}
         */
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

        /**
         * @description: 并查集回退操作
         * @param {unsigned int} timestamp 时间戳
         * @return {*}
         */
        void rollback(unsigned int timestamp)
        {
            data.rollback(timestamp);
        }

        /**
         * @description: 并查集获取时间戳
         * @return {*}
         */
        unsigned int getStamp() const
        {
            return data.getStamp();
        }

        /**
         * @description: 可回退数据结构变基
         * @return {*}
         */
        void rebase()
        {
            data.rebase();
        }
    };
}

