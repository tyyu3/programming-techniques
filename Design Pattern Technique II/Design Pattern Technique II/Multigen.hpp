#pragma once
#include <vector>
#include <random>

namespace strategy
{
  constexpr int array_size = 10;

class GenStrategy
{
public:
    virtual std::vector<int> Gen(const int a, const int b, const size_t size) const = 0;
    virtual std::string Info() const = 0;
    ~GenStrategy()
    {
        std::cout << "Old engine is destroyed!\n";
    }
};

class GenStrategyLC : public GenStrategy
{
public:
    std::vector<int> Gen(const int a, const int b, const size_t size) const override
    {
        std::random_device rd;
        std::minstd_rand gen(rd());
        std::uniform_int_distribution<> dis(a, b);
        std::vector<int> res;
        res.reserve(b - a + 1);
        for (size_t i = 0; i < size; i++)
        {
            res.push_back(dis(gen));
        }
        return res;
    }
    virtual std::string Info() const override
    {
        return "linear_congruential_engine";
    }
};
    class GenStrategyMT : public GenStrategy
    {
    public:
        std::vector<int> Gen(const int a, const int b, const size_t size) const override
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(a, b);
            std::vector<int> res;
            res.reserve(b - a + 1);
            for (size_t i = 0; i < size; i++)
            {
                res.push_back(dis(gen));
            }
            return res;
        }
        virtual std::string Info() const override
        {
            return "mersenne_twister_engine";
        }
    };

    class GenStrategySC : public GenStrategy
    {
    public:
        std::vector<int> Gen(const int a, const int b, const size_t size) const override
        {
            std::random_device rd;
            std::ranlux24_base gen(rd());
            std::uniform_int_distribution<> dis(a, b);
            std::vector<int> res;
            res.reserve(b - a + 1);
            for (size_t i = 0; i < size; i++)
            {
                res.push_back(dis(gen));
            }
            return res;
        }
        virtual std::string Info() const override
        {
            return "subtract_with_carry_engine";
        }
    };
    class IntGenerator 
    {

    private:
        std::unique_ptr<GenStrategy> strategy_ptr;
    public:
        IntGenerator(std::unique_ptr<GenStrategy> strategy = nullptr)
            : strategy_ptr(std::move(strategy))
        {
        }
        void set_generator(std::unique_ptr<GenStrategy> strategy)
        {
            strategy_ptr = std::move(strategy);
        }
        void PrintName() const
        {
            if (strategy_ptr)
                std::cout << strategy_ptr->Info() << "\n";
            else
                std::cout << "Please set a generator\n";
        }
        std::vector<int> gen(const int a, const int b, const size_t size) const
        {
            if (strategy_ptr)
            {
                return strategy_ptr->Gen(a, b, size);
            }
            else
                throw std::exception("No generator set!");

        }
    };
}
