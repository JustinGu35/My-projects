#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> result;
    std::string sentence=trim(rawWords);
    int len=sentence.length();
    int countStart=0;
    for(int i=0;i<len;i++)
    {
        if((sentence[i]<'a'&&(sentence[i]<'0'||sentence[i]>'9'))||sentence[i]>'z')
        {
            if(i-countStart>=2)
            {
                std::string subS=sentence.substr(countStart,i-countStart);
                result.insert(subS);
            }
            countStart=i+1;
        }
        else if(i==len-1&&i-countStart>=1)
        {
            std::string subS=sentence.substr(countStart,i-countStart+1);
            result.insert(subS);
            countStart=i+1;
        }
    }
    return result;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
