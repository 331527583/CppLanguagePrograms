#include <iostream>
#include "Define.h"
#include "base/SmartAssert.h"
using namespace std;
using namespace zl::base;

int main()
{
//    cout << MACRO_CAT(__FILE__, __LINE__) << "\n";
//    cout << MACRO_CAT(__FILE__, "ee") << "\n";
    {
        const static int i = 2;
        //ZL_STATIC_ASSERT(i>3);
        //ZL_STATIC_ASSERT(i>3, "must i>3");
    }
    {
        int i = 2;

        std::vector<int> vec;
        vec.push_back(5);
        ZL_ASSERT_LOG(vec.size() >= i)(i)(vec.size());
        printf("---------------------------------\n");
        ZL_ASSERT_LOG(vec.size() >= i)(i)(vec.size());
        printf("---------------------------------\n");

        ZL_ASSERT(i != 2);
        printf("---------------------------------\n");
        ZL_ASSERTEX(i != 2, "sdfs", 342, "zxcvbnm");
        printf("---------------------------------\n");
        //ZL_STATIC_ASSERT(sizeof(i)>=8);
        ZL_ASSERT(i ==2 )(i);
        ZL_ASSERT(i != 2)(i);
        printf("---------------------------------\n");

    }

    system("pause");
    return 0;
}
