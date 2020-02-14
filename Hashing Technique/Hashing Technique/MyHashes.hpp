#pragma once
#include <string>
#include <vector>

class Hasher
{
public:
    Hasher(int p, int m)
        : p_(p)
        , modulo_(m)
    {
        p_powers = calculate_powers(p_);
    }
    void set_p(int p)
    {
        p_ = p;
    }
    void set_modulo(int m)
    {
        modulo_ = m;
    }
    size_t bad_hash(std::string const& s)
    {

        return 0;
    }
    size_t better_hash(std::string const& s)
    {
        size_t hash = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            hash += (hash + s[i] * p_powers[i]) % modulo_;
        }
        return hash;
    }
    void recalculate_powers()
    {
        p_powers.clear();
        p_powers = calculate_powers(p_);
    }
    std::vector<int64_t> calculate_powers(int p)
    {
        std::vector<int64_t> res = {1};
        int64_t cur = 1;
        for (int i = 0; i < max_power; ++i)
        {
            cur *= p_;
            cur %= modulo_;
            res.push_back(cur);
        }
        return res;
    }

private:
    const int max_power = 27;
    int p_;
    int modulo_;
    std::vector<int64_t> p_powers;
};