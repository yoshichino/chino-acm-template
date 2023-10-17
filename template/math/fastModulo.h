/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-15 13:29:46
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-18 02:53:44
 * @FilePath: /chino-acm-template/template/math/fastModulo.h
 * @Description: int64 快速取模
 */
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
#include <cassert>
class Mod64
{
private:
    u64 n_;
    static u64 init(u64 w) { return reduce(u128(w) * r2); }
    static u64 reduce(u128 x)
    {
        u64 y = u64(x >> 64) - u64((u128(u64(x) * inv) * mod) >> 64);
        return i64(y) < 0 ? y + mod : y;
    }

public:
    Mod64() : n_(0) {}
    Mod64(u64 n) : n_(init(n)) {}
    static u64 modulus() { return mod; }

    static void set_mod(u64 m)
    {
        mod = m;
        assert(mod & 1);
        inv = m;
        for (int i = 0; i < 5; ++i)
            inv *= 2 - inv * m;
        r2 = -u128(m) % m;
    }

    Mod64 &operator+=(Mod64 rhs)
    {
        n_ += rhs.n_ - mod;
        if (i64(n_) < 0)
            n_ += mod;
        return *this;
    }
    Mod64 operator+(Mod64 rhs) const { return Mod64(*this) += rhs; }
    Mod64 &operator*=(Mod64 rhs)
    {
        n_ = reduce(u128(n_) * rhs.n_);
        return *this;
    }
    Mod64 operator*(Mod64 rhs) const { return Mod64(*this) *= rhs; }
    u64 get() const { return reduce(n_); }

    static u64 mod, inv, r2;
};
u64 Mod64::mod, Mod64::inv, Mod64::r2;
