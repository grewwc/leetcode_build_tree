#pragma once 
#include <unordered_map>

namespace leetcode
{
    template <typename K>
    class Counter
    {
    public:
        void put(const K &key, int count)
        {
            if (count == 0)
                return;
            m[key] = count;
        }

        void increase(const K &key)
        {
            if (m[key] == -1)
            {
                m.erase(key);
            }
            else
            {
                m[key]++;
            }
        }

        void decrease(const K &key)
        {
            if (m[key] == 1)
            {
                m.erase(key);
            }
            else
            {
                m[key]--;
            }
        }

        bool empty() const
        {
            return m.empty();
        }

    private:
        std::unordered_map<K, int> m;
    };
}
