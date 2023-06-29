#include <iostream>
#include <vector>

using namespace std;

template <typename Documents, typename term>
vector<double> ComputeTfIdfs(Documents, term)
{
    vector<double> tf_idfs;
    double tf = 0;
    int document_freq;

    for(const auto& document : Documents)
    {
        for(const auto& word : document)
        {
            if(word == term)
            {
                tf += 1.0 / document.size();
                document_freq = 1;
            }
            
        }
        // here
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