#include <iostream>
#include <string>

int const UpperLowerGap = 'A' - 'a';

char MakeChar(char const& Char)
{
    if ('a' <= Char && Char <= 'z')
    {
        return Char + ::UpperLowerGap;
    }
    else if ('A' <= Char && Char <= 'Z')
    {
        return Char - ::UpperLowerGap;
    }
    else return '0';
}

std::string MakeString(std::string const& String)
{
    std::string StringToReturn = "";
    for (char const& Char: String)
    {
        StringToReturn += MakeChar(Char);
    }
    return StringToReturn;
}

int main(void) {
    std::string str;
    std::cin >> str;
    std::cout << MakeString(str) << std::endl;
    
    return 0;
}