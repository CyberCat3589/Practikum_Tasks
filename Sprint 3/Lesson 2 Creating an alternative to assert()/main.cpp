#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void Assert(bool value, const string& hint) {
    // Реализуйте тело функции Assert
    if(!value)
    {
        cout << "Assertion failed" << ". ";;
        if(!hint.empty()) cout << "Hint: " << hint << endl;
        abort();
    }
}

int main() {
    const string greeting = "Hello"s;
    // Намеренная ошибка в условии, чтобы показать работу Assert
    Assert(greeting.empty(), "Greeting must be non-empty"s);
    // Следующая строка не должна выполниться, так как Assert аварийно завершит работу программы
    cout << "This line will not be printed"s << endl;
}