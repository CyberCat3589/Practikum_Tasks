#include <iostream>
#include <string>

using namespace std;

template <typename F>
string BruteForce(F check) 
{
    string result;
    // верните строку str, для которой check(str) будет true
    for (char a = 'A'; a <= 'Z'; ++a) 
    {
        for (char b = 'A'; b <= 'Z'; ++b) 
        {
            for (char c = 'A'; c <= 'Z'; ++c) 
            {
                for (char d = 'A'; d <= 'Z'; ++d) 
                {
                    for (char e = 'A'; e <= 'Z'; ++e) 
                    {
                        result += a;
                        result += b;
                        result += c;
                        result += d;
                        result += e;
                        if(check(result)) return result;
                        result = "";
                    }
                }
            }
        }
    }
    return "";
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