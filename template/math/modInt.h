/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-15 13:30:01
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-15 22:37:18
 * @FilePath: /chino-acm-template/template/math/modInt.h
 * @Description: 32位模整形,来自网络
 */
namespace chino
{
    template <int mod>
    class ModInt
    {
    public:
        const static int MD = mod;
        int x;
        ModInt(long long x = 0) : x(x % MD) {}
        int get() { return x; }

        ModInt operator+(const ModInt &that) const
        {
            int x0 = x + that.x;
            return ModInt(x0 < MD ? x0 : x0 - MD);
        }
        ModInt operator-(const ModInt &that) const
        {
            int x0 = x - that.x;
            return ModInt(x0 < MD ? x0 + MD : x0);
        }
        ModInt operator*(const ModInt &that) const { return ModInt((long long)x * that.x % MD); }
        ModInt operator/(const ModInt &that) const { return *this * that.inverse(); }

        ModInt operator+=(const ModInt &that)
        {
            x += that.x;
            if (x >= MD)
                x -= MD;
            return x;
        }
        ModInt operator-=(const ModInt &that)
        {
            x -= that.x;
            if (x < 0)
                x += MD;
            return x;
        }
        ModInt operator*=(const ModInt &that) { return x = (long long)x * that.x % MD; }
        ModInt operator/=(const ModInt &that) { return *this = *this / that; }

        ModInt inverse() const
        {
            int a = x, b = MD, u = 1, v = 0;
            while (b)
            {
                int t = a / b;
                a -= t * b;
                std::swap(a, b);
                u -= t * v;
                std::swap(u, v);
            }
            if (u < 0)
                u += MD;
            return u;
        }
    };
} // namespace chino
