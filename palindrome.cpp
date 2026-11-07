#include <iostream>
#include <string>
#include <cassert>
#include <cctype> // for std::tolower and std::isalnum

bool isPalindrome(const std::string &s)
{
    for (int i = 0, j = s.size() - 1; i < j;)
    {
        while (i < j && !std::isalnum(s[i]))
        {
            ++i;
        }
        while (i < j && !std::isalnum(s[j]))
        {
            --j;
        }
        if (std::tolower(s[i]) != std::tolower(s[j]))
        {
            return false;
        }
        ++i;
        --j;
    }
    return true;
}

int main()
{
    // Simple cases
    assert(isPalindrome("racecar") == true);
    assert(isPalindrome("hello") == false);
    assert(isPalindrome("abba") == true); // even length
    assert(isPalindrome("abca") == false);

    // Edge cases
    assert(isPalindrome("") == true);  // empty string
    assert(isPalindrome("a") == true); // single character
    assert(isPalindrome("ab") == false);

    // Case and punctuation
    assert(isPalindrome("Racecar") == true);
    assert(isPalindrome("A man, a plan, a canal: Panama") == true);
    assert(isPalindrome("No 'x' in Nixon") == true);
    assert(isPalindrome("race a car") == false);
    assert(isPalindrome(".,!") == true); // nothing left after removing punctuation

    std::cout << "All tests passed!\n";
    return 0;
}