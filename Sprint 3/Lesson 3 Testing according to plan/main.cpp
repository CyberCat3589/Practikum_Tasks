#include <iostream>
#include <string>

using namespace std;

string RemoveSpaces(const string& text) {
    string words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words += word;
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words += word;
    }

    return words;
}

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные буквы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, - это не палиндромы
bool IsPalindrome(const string& text) {
    // Напишите недостающий код
    string rev_str;

    string temp = RemoveSpaces(text);
    if(temp.empty()) return false;

    for(int i = temp.size() - 1; i >= 0; --i)
    {
        rev_str += temp[i];
    }

    return temp == rev_str;
}

int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}