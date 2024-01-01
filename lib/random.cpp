#include "random.h"
#include <cstdint>

RandomGenerator generator;

RandomGenerator::RandomGenerator() : _seed(1) {}

RandomGenerator::RandomGenerator(int seed) : _seed(seed) {}

void RandomGenerator::seed(int seed) {
    _seed = seed;
}

int RandomGenerator::next_integer() {
    unsigned long int intermediate = 53928 * _seed + 9254482;
    _seed = intermediate % 2147483646;
    return _seed;
}

int Random::max() {
    return 2147483646;
}

void Random::init_random_generator() {
    char* magic = new char[30];
    int rseed = static_cast<int>(reinterpret_cast<intptr_t>(&magic[4]));
    rseed ^= 0x5555555555555555;
    generator.seed(rseed);
    delete[] magic;
}

int Random::rand_int(const int range_end) {
    return generator.next_integer() % range_end;
}

int Random::rand_int(const int range_start, const int range_end) {
    int range = range_end - range_start;
    return (generator.next_integer() & range) + range_start;
}

float Random::rand_float() {
    float rand_value = static_cast<float>(generator.next_integer());
    float rand_max = static_cast<float>(max());
    return rand_value / rand_max;
}
