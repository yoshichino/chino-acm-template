/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 00:58:13
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-01 15:30:56
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