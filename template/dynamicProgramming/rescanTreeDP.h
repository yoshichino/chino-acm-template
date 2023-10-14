/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-01 19:39:54
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-01 21:40:33
 * @FilePath: /chino-acm-template/template/dynamicProgramming/rescanTreeDP.h
 * @Description: 换根树dp
 */
#include <vector>
#include <functional>
template <typename T>
class rescanTreeDP
{
private:
    int N;
    std::vector<T> dp;
    std::vector<std::vector<int>> G;
    std::function<void(T &des, const T &src)> stateTransition;
    std::function<void(T &des, const T &src)> invStateTransition;
    std::function<T(const int x)> valOfLeaf;
    std::function<void(const int x, const T &dpVal)> solveNotify;
    void slove_(int x, int fa)
    {
        if (valOfLeaf)
        {
            dp[x] = valOfLeaf(x);
        }
        for (auto &i : G[x])
        {
            if (i != fa)
            {
                slove_(i, x);
                if (stateTransition)
                {
                    stateTransition(dp[x], dp[i]);
                }
            }
        }
    }
    void rescan(int x, int fa)
    {
        if (solveNotify)
        {
            solveNotify(x, dp[x]);
        }

        for (auto &i : G[x])
        {
            if (i != fa)
            {
                if (invStateTransition && stateTransition)
                {
                    invStateTransition(dp[x], dp[i]);
                    stateTransition(dp[i], dp[x]);
                    rescan(i, x);
                    invStateTransition(dp[i], dp[x]);
                    stateTransition(dp[x], dp[i]);
                }
            }
        }
    }

public:
    rescanTreeDP(int N_,
                 std::function<void(T &des, const TD &src, const int from, const int to)> link_,
                 std::function<void(T &des, const TD &src, const int from, const int to)> cut_,
                 std::function<void(const int x, const TD dpVal)> solveNotify_) : N(N_),
                                                                                  link(std::move(link_)),
                                                                                  cut(std::move(cut_)),
                                                                                  solveNotify(std::move(solveNotify_))
    {
        G.resize(N + 1);
        dp.resize(N + 1);
    }
    void addEdge(int u, int v)
    {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void slove()
    {
        slove_(1, -1);
        rescan(1, -1);
    }
};
