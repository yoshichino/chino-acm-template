/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-17 01:30:35
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-17 01:50:11
 * @FilePath: /chino-acm-template/template/dataStructure/segmentTreeSimpleMin.h
 * @Description: 简单线段树 最小值
 */
#include "segmentTreeBase.h"
namespace chino
{
    struct segmentTreeSimpleMinData
    {
        long long data;
        int id;
    };

    typedef chino::segmentTreeBase<segmentTreeSimpleMinData, long long, long long> segmentTreeSimpleMin;
    segmentTreeSimpleMin new_segmentTreeSimpleMin(int N)
    {
        segmentTreeSimpleMin seg(N);
        seg.pushUpData = [](const segmentTreeSimpleMinData &lch, const segmentTreeSimpleMinData &rch) -> segmentTreeSimpleMinData
        {
            return lch.data < rch.data ? lch : rch;
        };
        seg.pushDownTag = [](const long long &lazy, long long &lch_lz, long long &rch_lz)
        {
            lch_lz += lazy;
            rch_lz += lazy;
        };
        seg.needPush = [](const long long &lazy) -> bool
        {
            return lazy != 0;
        };
        seg.doLazy = [](const long long &lazy, segmentTreeSimpleMinData &data, const int &l, const int &r)
        {
            data.data += lazy;
        };
        seg.setLazy = [](const long long &modify_val, long long &lazy, const int &l, const int &r)
        {
            lazy += modify_val;
        };
        seg.clearLazy = [](long long &lazy)
        {
            lazy = 0;
        };
        return seg;
    }
} // namespace chino