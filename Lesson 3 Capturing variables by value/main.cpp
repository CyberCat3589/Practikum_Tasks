#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

int main() {
    const int queryCount = ReadLineWithNumber();

    vector<string> queries(queryCount);
    for (string& query : queries) {
        query = ReadLine();
    }
    const string buzzword = ReadLine();

    cout << count_if(queries.begin(), queries.end(), [buzzword](const string& query) {
        // Реализуйте эту лямбда-функцию
        // Верните true, если query содержит слово buzzword
        set<string> query_words;
        string word;
        
        for(char ch : query)
        {
            if(ch == ' ')
            {
                query_words.insert(word);
                word = "";
            }
            else word += ch;
        }
        query_words.insert(word);
        
        if(query_words.count(buzzword) > 0) return true;
        else return false;
    });
    cout << endl;
}