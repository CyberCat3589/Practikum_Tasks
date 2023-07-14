#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
void AssertImpl(const T& t, const string& t_str, const string& file, const string& func, unsigned line, const string& hint)
{
    if(!t)
    {
        cout << boolalpha;
        cout << file << "("s << line << "): "s;
        cout << func << ": "s;
        cout << "ASSERT("s << t_str << ") failed."s;

        if(!hint.empty())
        {
            cout << " Hint: "s << hint;
        }

        cout << endl;
        abort();
    }
}

#define ASSERT(expr) AssertImpl(expr, #expr, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_HINT(expr, hint) AssertImpl(expr, #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

int main() 
{
    string hello = "hello"s;
    ASSERT(!hello.empty());
    ASSERT_HINT(2 + 2 == 5, "This will fail"s);
    return 0;
}