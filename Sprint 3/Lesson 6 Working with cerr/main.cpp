#include <iostream>
#include <string>

using namespace std;

template <typename F>
void RunTestImpl(const F& fnc, const string& fnc_str) 
{
    fnc();
    cerr <<  fnc_str  << " OK"s << endl;
}

#define RUN_TEST(func)  RunTestImpl(func, #func)

void Test1() 
{
    cerr << "Test1 started..."s << endl;
}

int main() 
{
    RUN_TEST(Test1);
}