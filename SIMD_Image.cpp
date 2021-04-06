// Type your code here, or load an example.
#include <immintrin.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

#define ARRAY_LENGTH 8

void fillRandomImage(std::vector<unsigned char> &image)
{
    std::srand(unsigned(std::time(nullptr)));

    std::generate(image.begin(), image.end(), std::rand);
}

int main(int argc, char* argv[]) {

    constexpr auto SIZE = 2048*2048;
    std::vector<unsigned char> image1(SIZE);
    fillRandomImage(image1);
    std::vector<unsigned char> image2(SIZE);
    fillRandomImage(image2);
    std::vector<unsigned char> image3(SIZE);

    auto begin = std::chrono::steady_clock::now();
    for (auto i = 0; i < SIZE; i += 1)
    {
        image3[i] = image1[i] + image2[i];
    }
    auto end = std::chrono::steady_clock::now();

    for (
        unsigned short i = 0;
        i < 30;
        i += 1
    ) {
        printf("%d ", image3[i]);
    }
    std::fill(image3.begin(), image3.end(), 0);
    std::cout<< std::endl;
    
    std::cout<<"Scalar loop Time taken:"<< (std::chrono::duration_cast<std::chrono::milliseconds>(end-begin)).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    for (auto i = 0; i+16 < SIZE; i += 16)
    {
        auto first = _mm_load_si128 ((__m128i*)&image1[i]);
        auto second = _mm_load_si128 ((__m128i*)&image2[i]);
        auto result = _mm_add_epi8(first,second);
        _mm_store_si128((__m128i*)&image3[i],result);
    }
    end = std::chrono::steady_clock::now();

    for (
        unsigned short i = 0;
        i < 30;
        i += 1
    ) {
        printf("%d ", image3[i]);
    }
   std::cout<< std::endl;
    std::cout<<"vector loop Time taken:"<< (std::chrono::duration_cast<std::chrono::milliseconds>(end-begin)).count() << "ms" << std::endl;


    auto first = _mm_set_epi16(10, 20, 30, 40, 50, 60, 70, 80);
    auto second = _mm_set_epi16(5, 5, 5, 5, 5, 5, 5, 5);
    auto result = _mm_add_epi16(first, second);

    short* values = (short*) &result;

    for (
        unsigned short i = 0;
        i < ARRAY_LENGTH;
        i += 1
    ) {
        printf("%d ", values[i]);
    }

    return 0;
}