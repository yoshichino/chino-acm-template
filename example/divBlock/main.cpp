/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-10-14 20:15:27
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-15 14:09:44
 * @FilePath: /chino-acm-template/example/divBlock/main.cpp
 * @Description: 整除分块示范
 */
#include "divBlock.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    long long n;
    scanf("%lld", &n);
    chino::divBlock db(n);
    chino::divBlockSegments(n, [&](long long id, long long l, long long r)
    {
        for(auto i=l;i<=r;++i)
        {
            printf("first:%lld %lld %lld\n",id,l,r);
            printf("second:%lld %lld %lld\n",db.belone(i),db.l(id),db.r(id));
            assert(id==db.belone(i));
            assert(l==db.l(id));
            assert(r==db.r(id));
        } 
    });
    return 0;
}
