/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-14 19:56:22
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-15 14:29:43
 * @FilePath: /chino-acm-template/template/math/divBlock.h
 * @Description: 整除分块
 */
#include <cmath>
#include <functional>
namespace chino
{
    class divBlock
    {

    private:
        long long n_;
        long long sn_;
        bool f_;

    public:

        /**
         * @description: 整除分块算法模板实例化构造函数
         * @param {long long} n 被除数n
         * @return {*}
         */
        divBlock(long long n)
        {
            n_ = n;
            sn_ = std::sqrt(n_ + 0.5);
            f_ = sn_ != (n_ / sn_);
        }

        /**
         * @description: 获取除数为x时，所在整除分块的第几块
         * @param {long long} x 除数
         * @return {long long} id 表示除数x属于第几块
         */
        long long belone(long long x)
        {
            return (x <= sn_ ? x : (sn_ << 1) - n_ / x + f_) - 1;
        }

        /**
         * @description: 输入id，输出分块后第id块的左端点
         * @param {long long} id
         * @return {long long}l 表示第id块的左端点
         */
        long long l(long long id)
        {
            if (id < 0 || id > belone(n_))
            {
                return -1;
            }
            return id + 1 <= sn_ ? id + 1 : n_ / (belone(n_) - id + 2) + 1;
        }

        /**
         * @description: 输入id，输出分块后第id块的右端点
         * @param {long long} id
         * @return {long long}r 表示第id块的右端点
         */
        long long r(long long id)
        {
            if (id < 0 || id > belone(n_))
            {
                return -1;
            }
            return n_ / (n_ / l(id));
        }
    };

    /**
     * @description: 整除分块算法，枚举所有的块
     * @param {long long} n 被除数
     * @param {function<void(long long id, long long l, long long r)>} cb 自定义回调函数
     * @return {*}
     */
    void divBlockSegments(long long n, std::function<void(long long id, long long l, long long r)> cb)
    {
        for (long long l = 1, r, id = 0; l <= n; id++, l = r + 1)
        {
            r = n / (n / l);
            cb(id, l, r);
        }
    }
}