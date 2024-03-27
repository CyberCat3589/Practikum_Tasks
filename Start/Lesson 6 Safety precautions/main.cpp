#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Document {
    int id;
    int rating;
};

void PrintDocuments(vector<Document> documents, size_t skip_start, size_t skip_finish) {
    if(documents.empty() || (skip_start + skip_finish >= documents.size())) return;
    // отсортировать документы и вывести не все

    sort(documents.begin(), documents.end(), 
    [](Document lhs, Document rhs)
    {
        return lhs.rating > rhs.rating;
    });

    for(size_t i = skip_start; i + skip_finish < documents.size(); ++i)
    {
        cout << "{ id = " << documents[i].id << ", rating = " << documents[i].rating << " }" << endl;
    }
}

int main() {
    PrintDocuments({{100, 5}, {101, 7}, {102, -4}, {103, 9}, {104, 1}}, 1, 2);
}