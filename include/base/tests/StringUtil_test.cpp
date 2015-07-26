#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string.h>
#include "base/StringUtil.h"
using namespace std;

int main()
{
    string str1 = zl::base::toStr(100.123);
    //wstring wstr1 = zl::toStr<double, wchar_t>(100.123);
    cout << str1 << "\n";
    //wcout << wstr1 << "\n";

    //cout << zl::strTo<float, char>(str1) << "\n";
    cout << zl::base::strTo<int>(str1) << "\n";

    string str2 = " fg t5rt $%^   !  ";
    zl::base::trim(str2);  // "fg t5rt $%^   !"
    cout << str2 << "\n";
    str2 = " fg t5rt $%^   !  ";
    zl::base::trimAll(str2);  // "fgt5rt$%^!"
    cout << str2 << "\n";

    str2 = "ttdgfh t34 0-tt";
    zl::base::erase(str2, 't');   // dgfh 34 0-
    cout << str2 << "\n";

    str2 = "ttd gfht t34 0-tt";
    zl::base::replace(str2, std::string("tt"), std::string("123"));   // 123dgfh t34 0-123
    cout << str2 << "\n";

    std::vector<std::string> vec;
    str2 = "ttd gfht t34 0-tt";
    zl::base::split(str2, vec, std::string("t"), true);   // **d gfh* *34 0-***
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<string>(std::cout, "*"));
    cout << "\n";

    vec.clear();
    str2 = "ttd gfht t34 0-tt";
    zl::base::split(str2, vec, std::string("t"), false); // d gfh* *34 0-*
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<string>(std::cout, "*"));
    cout << "\n";

    cout << zl::base::join(vec, "##") << "\n";

    list<string> ls={"hello", "world", "github"};
    cout << zl::base::join(ls, "-") << "\n";

    string s;
    zl::base::stringFormat(&s, "%d-%s-%f", 1234, "hello", "43.21");
    cout << s << "\n";

    s = zl::base::stringFormat("%s-%d\n", "world", 33);
    cout << s ;

    char data[20];
    ::memset(data, 0, 20);
    for(char c = 'A'; c < 'A' + 20 - 1; c++)
        data[c - 'A'] = c;
    s = zl::base::stringFormat("%s", data);
    cout << s << "\n";

    return 0;
}
