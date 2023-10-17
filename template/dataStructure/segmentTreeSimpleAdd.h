/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-16 10:40:14
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-18 00:35:04
 * @FilePath: /chino-acm-template/template/dataStructure/segmentTreeSimpleAdd.h
 * @Description: 简单线段树——区间和
 */
#include "segmentTreeBase.h"
namespace chino
{
    typedef chino::segmentTreeBase<long long, long long, long long> segmentTreeSimpleAdd;
    segmentTreeSimpleAdd new_segmentTreeSimpleAdd(int N)
    {
        segmentTreeSimpleAdd seg(N);
        seg.pushUpData = [](const long long &lch, const long long &rch) -> long long
        {
            return lch + rch;
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
        seg.doLazy = [](const long long &lazy, long long &data, const int &l, const int &r)
        {
            data += lazy * (r - l + 1);
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