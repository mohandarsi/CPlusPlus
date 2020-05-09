
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>     // std::back_inserter
#include <sstream>


auto extractWordsVector(std::string const& s)
{
    std::vector<std::string> result;
    std::istringstream stream(s);
    std::copy(
        std::istream_iterator<std::string, char>(stream),
        std::istream_iterator<std::string, char>(),
        std::back_inserter(result));

    return result;
}

bool testsPassed()
{
    bool passed = true;
    passed = passed && (extractWordsVector("word1  word2  ") == std::vector<std::string>{"word1", "word2"});
    passed = passed && (extractWordsVector("  word1  word2  ") == std::vector<std::string>{"word1", "word2"});
    passed = passed && (extractWordsVector("  word1  word2") == std::vector<std::string>{"word1", "word2"});
    passed = passed && (extractWordsVector("  ") == std::vector<std::string>{});
    passed = passed && (extractWordsVector("") == std::vector<std::string>{});
    return passed;
}

int main()
{
    std::cout << (testsPassed() ? "TESTS PASSED" : "TESTS FAILED") << '\n';
}


