/*
 * @Author: winterzz1 1002658987@qq.com
 * @Date: 2023-09-30 23:56:47
 * @LastEditors: winterzz1 1002658987@qq.com
 * @LastEditTime: 2023-10-01 01:39:57
 * @FilePath: /chino-acm-template/template/dataStructure/rollbackArray.h
 * @Description: 可回滚数组
 */
#include <vector>
namespace chino
{
    template <typename T>
    class rollbackArray
    {
    private:
        std::vector<T> data;
        std::vector<std::pair<unsigned int, T>> stk;

    public:
        rollbackArray() = default;

        /**
         * @description: 构造一个尺寸为N的可回滚数组
         * @param {int} N 尺寸
         */
        rollbackArray(int N)
        {
            data.resize(N);
        }

        /**
         * @description: 根据std::vector构造
         * @param {vector<T>} data_ 输入数据
         */
        rollbackArray(std::vector<T> data_)
        {
            data = std::move(data_);
        }

        /**
         * @description: 根据c语言原始数组构造
         * @param {vector<T>} data_ 输入数据
         * @param {int} N 数组长度
         */
        rollbackArray(T data_[], int N)
        {
            data.resize(N);
            for (auto i = 0; i < N; ++i)
            {
                data[i] = data_[i];
            }
        }

        /**
         * @description: 数组取值
         * @param {size_t} idx 数组下标
         * @return {T}
         */
        T at(const size_t idx) const &
        {
            return data[idx];
        }

        void set(const size_t idx, const T &val, bool commit = true)
        {
            if (commit)
            {
                stk.emplace_back(idx, data[idx]);
            }
            data[idx] = val;
        }

        void rebase()
        {
            stk.clear();
        }

        void rollback(unsigned int timestamp)
        {
            if (timestamp < 0)
            {
                rebase();
            }
            while (stk.size() > timestamp)
            {
                auto temp = stk[stk.size() - 1];
                data[temp.first] = temp.second;
                stk.pop_back();
            }
        }

        unsigned int getStamp() const
        {
            return stk.size();
        }

        /**
         * @description: 强制类型转换为std::vector
         * @return rollbackArray中的数据
         */
        operator std::vector<T>() const
        {
            return data;
        }

        size_t size() const
        {
            return data.size();
        }
    };
}
