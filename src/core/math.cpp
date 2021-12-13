#include "math.hpp"

#include <random>

int core::math::generateRandom(int min, int max) { // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range/7560151
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    return distr(gen);
}