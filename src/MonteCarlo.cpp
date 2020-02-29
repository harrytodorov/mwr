#include <iostream>
#include "Utils.h"

/**
 * @brief Estimates the value of Pi using Monte Carlo
 * 
 * Estimates the value of Pi by a Monte Carlo method inspired by the Buffon
 * Needle problem. Throws random samples inside the unit square [-1,1] x [-1,1]
 * and counts the number of samples, which have landed inside the uint cirle.
 * Pi = samplesInsideCircle * 4 / totalNumberOfSamples
 * 
 * @param n
 *      Total number of random samples
 * @return float
 *      Estimateted value of Pi
 */
float estimate_pi_with_n_samples(uint32_t n) {
    uint32_t samplesInsideCircle = 0;
    for (size_t i = 0; i < n; i++) {
        float x = get_random_in_range(-1, 1);
        float y = get_random_in_range(-1, 1);
        if (x*x + y*y < 1) {
            samplesInsideCircle++;
        }
    }
    return samplesInsideCircle * 4 / n;
}

int main(int argc, char const *argv[])
{

    uint32_t numberOfSamples = 1000;
    uint32_t samplesInsideCircle = 0;
    for (size_t i = 0; i < numberOfSamples; i++) {
        float x = get_random_in_range(-1, 1);
        float y = get_random_in_range(-1, 1);
        if (x*x + y*y < 1) {
            samplesInsideCircle++;
        }
    }
    std::cout << "Estimate of Pi: "
              << static_cast<float>(samplesInsideCircle) * 4 / numberOfSamples
              << std::endl;
    return 0;
}
