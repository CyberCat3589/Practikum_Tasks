#include <iostream>
#include <string>

using namespace std;

template <typename F>
string BruteForce(F check) 
{
    // верните строку str, для которой check(str) будет true
    
}

int main() 
{
    string pass = "ARTUR"s;
    auto check = [pass](const string& s) 
    {
        return s == pass;
    };
    cout << BruteForce(check) << endl;
}