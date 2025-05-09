#include "rng.h"

void random_int_vec_gen(std::vector<int>& vec, size_t array_size, int lowerbound, int upperbound)
{
    std::random_device rd;  // Obtain a random seed from the system
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(lowerbound, upperbound);
    for (int i = 0; i < array_size; ++i) {
        vec.push_back(dist(rd));
    }
}
