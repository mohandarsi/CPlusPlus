#include <immintrin.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>


using Image = std::vector<unsigned char>;
constexpr auto SIZE = 2048*2048; // 2048 width and 2048 height

void fillRandomImage(Image &image)
{
    //https://stackoverflow.com/questions/21516575/fill-a-vector-with-random-numbers-c
    static std::uniform_int_distribution<unsigned char> distribution(
        std::numeric_limits<unsigned char>::min(),
        std::numeric_limits<unsigned char>::max());
    static std::default_random_engine generator;

    std::generate(image.begin(), image.end(), []() { return distribution(generator); });
}

void print(Image &image)
{
   //print only first few values
   for (unsigned short i = 0; i < 30; i += 1)
   {
        std::cout<< (int)image[i] << ' ';
   }
   std::cout<< std::endl;
}

void vectorizeAdd(const Image &image1, const Image &image2, Image &image3)
{
    auto begin = std::chrono::steady_clock::now();
    for (auto i = 0; i < SIZE; i += 16)
    {
        //load first 16 pixels from image1 & image2
        auto first = _mm_load_si128 ((__m128i*)&image1[i]);
        auto second = _mm_load_si128 ((__m128i*)&image2[i]);
        //Add and clamp to max grey value.
        auto result = _mm_adds_epu8(first,second);
        _mm_store_si128((__m128i*)&image3[i],result);
    }
    auto end = std::chrono::steady_clock::now();

    std::cout<<"vectorize loop took:"<< (std::chrono::duration_cast<std::chrono::milliseconds>(end-begin)).count() << "ms" << std::endl;
}

void scalarAdd(const Image &image1, const Image &image2, Image &image3)
{
    auto begin = std::chrono::steady_clock::now();
    for (auto i = 0; i < SIZE; i += 1)
    {
       const auto result = image1[i] + image2[i];
       //clamp to max grey value.
       image3[i] = result > 255 ? 255: result;
    }
    auto end = std::chrono::steady_clock::now();
 
    std::cout<<"Scalar loop took:"<< (std::chrono::duration_cast<std::chrono::milliseconds>(end-begin)).count() << "ms" << std::endl;
}

int main(int argc, char* argv[]) 
{

    Image image1(SIZE);
    fillRandomImage(image1);
    Image image2(SIZE);
    fillRandomImage(image2);

    //dispaly values in images
    std::cout<<"image 1: "; print(image1);
    std::cout<<"image 1: "; print(image2);

    Image image3(SIZE);
    Image image4(SIZE);

    scalarAdd(image1,image2,image3);
    print(image3);
       
    vectorizeAdd(image1,image2,image4);
    print(image4);

    const auto same = std::equal(image3.begin(), image3.end(), image4.begin(),image4.end());

   if(same)  std::cout << "Both images are same";
   
   return 0;
}
