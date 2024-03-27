#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

template <typename Documents, typename Term>
vector<double> ComputeTfIdfs(const Documents& documents, const Term& term)
{
    vector<double> tf_idfs;
    double tf = 0;
    double idf = 0;
    int document_freq = 0;

    for(const auto& document : documents)
    {
        if(count(document.begin(), document.end(), term) > 0) ++document_freq;
    }

    for(const auto& document : documents)
    {
         
        for(const auto& word : document)
        {
            if(word == term)
            {
                tf += 1.0 / document.size();
            }
        }

        idf = log(static_cast<double>(documents.size()) / document_freq);

        tf_idfs.push_back(tf * idf);
        tf = 0;
    }

    return tf_idfs;
}

int main() {
    const vector<vector<string>> documents = {
        {"белый"s, "кот"s, "и"s, "модный"s, "ошейник"s},
        {"пушистый"s, "кот"s, "пушистый"s, "хвост"s},
        {"ухоженный"s, "пёс"s, "выразительные"s, "глаза"s},
    };
    const auto& tf_idfs = ComputeTfIdfs(documents, "кот"s);
    for (const double tf_idf : tf_idfs) {
        cout << tf_idf << " "s;
    }
    cout << endl;
    return 0;
}