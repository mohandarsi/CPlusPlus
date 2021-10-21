#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

int main(int, char**) {
    auto vecStr = std::make_unique<std::vector<std::string>>();
    for(auto i=0;i<5;i++)
    {
        std::stringstream stream;
        stream << "Hello world :" << i;
        vecStr->push_back(stream.str());
    }
    for(auto &itr:*(vecStr.get()))
    {
        std::cout<<itr<<std::endl;
    }
}
