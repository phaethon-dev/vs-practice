#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <cctype>

std::unordered_map<std::string, int> countWords(const std::string &text)
{
    std::unordered_map<std::string, int> counts;

    std::string word;
    //loops through each character in the text, checking if it is a letter. If it is, it adds it to the current word (in lowercase). 
    //If it is not a letter, it checks if there is a current word being built. 
    //If there is, it increments the count for that word in the map and clears the current word.
    for (char c : text){
        if (std::isalpha(c)){
            word += std::tolower(c);
        } else {
            if (!word.empty()){
                counts[word]++;
                word.clear();
            }
        }
    }
    if (!word.empty()){
        counts[word]++;
    }
    return counts;
}

std::string mostCommonWord(const std::string &text)
{
    auto counts = countWords(text);
    std::string mostCommon;
    int maxCount = 0;
    for (const auto &[word, count] : counts){
        if (count > maxCount){
            maxCount = count;
            mostCommon = word;
        }
    }
    return mostCommon;
}

int main()
{
    // Part 1
    auto c = countWords("The cat and the hat.");
    assert(c.size() == 4);
    assert(c["the"] == 2);
    assert(c["cat"] == 1);
    assert(c["hat"] == 1);

    assert(countWords("").empty());
    assert(countWords("  ...!!  ").empty());          // no letters at all

    auto c2 = countWords("Hello, hello... HELLO!");
    assert(c2.size() == 1);
    assert(c2["hello"] == 3);

    auto c3 = countWords("end");                      // word at the very end, no punctuation after
    assert(c3["end"] == 1);

    auto c4 = countWords("don't stop");               // apostrophe splits words
    assert(c4["don"] == 1 && c4["t"] == 1 && c4["stop"] == 1);

    // Part 2 (uncomment when ready)
    assert(mostCommonWord("the cat and the hat") == "the");
    assert(mostCommonWord("a b b c c c") == "c");
    assert(mostCommonWord("") == "");
    assert(mostCommonWord("Fish fish FISH dog") == "fish");

    std::cout << "All tests passed!\n";
    return 0;
}