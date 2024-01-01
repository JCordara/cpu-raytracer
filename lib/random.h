#ifndef RANDOM_H
#define RANDOM_H

class RandomGenerator {
private:

    int _seed;
    int _max;

public:

    RandomGenerator();
    RandomGenerator(int seed);

    void seed(int seed);
    int next_integer();

};

namespace Random {

    /**
     * Seeds the random number generator using the current time
    */
    void init_random_generator();

    /**
     * Generates a random integer between 0 and Random::max()
    */
   int rand_int();

    /**
     * Generates a random integer between 0 and range_end
    */
    int rand_int(const int range_end);

    /**
     * Generates a random integer between range_start and range_end
    */
    int rand_int(const int range_start, const int range_end);

    /**
     * Generates a random number between 0.0 and 1.0
    */
    float rand_float();

    /**
     * Returns the maximum random integer value
    */
    int max();

}

#endif // RANDOM_H