#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

string ReadLine() 
{
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() 
{
    int result;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) 
{
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

struct Document {
    int id;
    double relevance;
    int rating;
};

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

class SearchServer {
public:
    void SetStopWords(const string& text) 
    {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument(int document_id, const string& document, DocumentStatus status, const vector<int>& ratings) 
    {
        const vector<string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();
        for (const string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
        documents_.emplace(document_id, DocumentData{ComputeAverageRating(ratings), status});
    }
    
    // Метод, принимающий как один поисковый запрос, так и запрос со статусом
    vector<Document> FindTopDocuments(const string& raw_query, DocumentStatus status = DocumentStatus::ACTUAL) const 
    {
        // Вызываем шаблонную версию и возвращаем результат
        return FindTopDocuments(raw_query, 
                [status](int document_id, DocumentStatus doc_status, int rating) {
                    return doc_status == status;
                });
    }

    // Данный метод принимает вторым аргументом лямбда- или любую другую функцию
    template<typename FilterFunction>
    vector<Document> FindTopDocuments(const string& raw_query, FilterFunction filter_function ) const 
    {
        const Query query = ParseQuery(raw_query);

        auto matched_documents = FindAllDocuments(query, filter_function);
        
        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document& lhs, const Document& rhs) {
                 if (abs(lhs.relevance - rhs.relevance) < 1e-6) {
                     return lhs.rating > rhs.rating;
                 } else {
                     return lhs.relevance > rhs.relevance;
                 }
             });
        
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

    int GetDocumentCount() const {
        return documents_.size();
    }

    tuple<vector<string>, DocumentStatus> MatchDocument(const string& raw_query, int document_id) const 
    {
        const Query query = ParseQuery(raw_query);
        vector<string> matched_words;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            if (word_to_document_freqs_.at(word).count(document_id)) {
                matched_words.push_back(word);
            }
        }
        for (const string& word : query.minus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            if (word_to_document_freqs_.at(word).count(document_id)) {
                matched_words.clear();
                break;
            }
        }
        return {matched_words, documents_.at(document_id).status};
    }

private:
    struct DocumentData 
    {
        int rating;
        DocumentStatus status;
    };

    set<string> stop_words_;
    map<string, map<int, double>> word_to_document_freqs_;
    map<int, DocumentData> documents_;

    bool IsStopWord(const string& word) const 
    {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const 
    {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    static int ComputeAverageRating(const vector<int>& ratings) 
    {
        if (ratings.empty()) {
            return 0;
        }
        int rating_sum = 0;
        for (const int rating : ratings) {
            rating_sum += rating;
        }
        return rating_sum / static_cast<int>(ratings.size());
    }

    struct QueryWord {
        string data;
        bool is_minus;
        bool is_stop;
    };

    QueryWord ParseQueryWord(string text) const 
    {
        bool is_minus = false;
        // Word shouldn't be empty
        if (text[0] == '-') {
            is_minus = true;
            text = text.substr(1);
        }
        return {text, is_minus, IsStopWord(text)};
    }

    struct Query 
    {
        set<string> plus_words;
        set<string> minus_words;
    };

    Query ParseQuery(const string& text) const 
    {
        Query query;
        for (const string& word : SplitIntoWords(text)) {
            const QueryWord query_word = ParseQueryWord(word);
            if (!query_word.is_stop) {
                if (query_word.is_minus) {
                    query.minus_words.insert(query_word.data);
                } else {
                    query.plus_words.insert(query_word.data);
                }
            }
        }
        return query;
    }

    double ComputeWordInverseDocumentFreq(const string& word) const 
    {
        return log(GetDocumentCount() * 1.0 / word_to_document_freqs_.at(word).size());
    }
    
    // Теперь эта функция - шаблонная
    template<typename FilterFunction>
    vector<Document> FindAllDocuments(const Query& query, FilterFunction filter_function) const 
    {
        map<int, double> document_to_relevance;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
            for (const auto [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                if (filter_function(document_id, documents_.at(document_id).status, documents_.at(document_id).rating))
                    document_to_relevance[document_id] += term_freq * inverse_document_freq;
            }
        }

        for (const string& word : query.minus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            for (const auto [document_id, _] : word_to_document_freqs_.at(word)) {
                document_to_relevance.erase(document_id);
            }
        }

        vector<Document> matched_documents;
        for (const auto [document_id, relevance] : document_to_relevance) {
            matched_documents.push_back(
                {document_id, relevance, documents_.at(document_id).rating});
        }
        return matched_documents;
    }
};

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = {1, 2, 3};
    // Сначала убеждаемся, что поиск слова, не входящего в список стоп-слов,
    // находит нужный документ
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("in"s);
        assert(found_docs.size() == 1);
        const Document& doc0 = found_docs[0];
        assert(doc0.id == doc_id);
    }

    // Затем убеждаемся, что поиск этого же слова, входящего в список стоп-слов,
    // возвращает пустой результат
    {
        SearchServer server;
        server.SetStopWords("in the"s);
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        assert(server.FindTopDocuments("in"s).empty());
    }
}

/*
Разместите код остальных тестов здесь
*/

SearchServer GetTestSearchServer(int doc_id, string content, vector<int> ratings) {
    SearchServer server;    

    server.SetStopWords("in the"s);
    server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);

    return server;
}

void TestAddDocument() {
    SearchServer server = GetTestSearchServer(42, "cat in the city"s, {1, 2, 3});
    assert(!server.FindTopDocuments("cat in the bar"s).empty());
    
    server.AddDocument(43, "in the", DocumentStatus::ACTUAL, {2, 3, 2});

    assert(server.FindTopDocuments("in the").empty());
}

void TestStopWords() {
    const SearchServer server = GetTestSearchServer(42, "cat in the city"s, {1, 2, 3});
    assert(server.FindTopDocuments("in the"s).empty());
    assert(server.FindTopDocuments("pig in the"s).empty());
    assert(!server.FindTopDocuments("a dog found in the cat").empty());
}

void TestMatching() {
    int doc_id = 42;
    SearchServer server = GetTestSearchServer(doc_id, "cat in the city"s, {1, 2, 3});
    
    auto [ matched_words, doc_status ] = server.MatchDocument("cat in the city"s, doc_id);
    
    assert(matched_words.size() == 2);

    tie(matched_words, doc_status) = server.MatchDocument("-cat in the bar", 42);
    assert(matched_words.empty());

    doc_id = 33;

    server.AddDocument(doc_id, "hello world cat bat cat", DocumentStatus::ACTUAL, {1, 1, 1, 1, 4});

    tie(matched_words, doc_status) = server.MatchDocument("cat"s, doc_id);
    assert(matched_words.size() == 1);
}

void TestRelevanceSorting() {
    SearchServer server = GetTestSearchServer(42, "cat in the city"s, {1, 2, 3});
    server.AddDocument(43,"dog in the city"s,DocumentStatus::ACTUAL,{1, 2, 2});
    server.AddDocument(44,"pig in the bar"s,DocumentStatus::ACTUAL,{3, 2, 5});
    auto documents = server.FindTopDocuments("cat in the city"s);

    auto documents_sorted(documents);
    
    assert(documents[0].id == 42);
    assert(documents[1].id == 43);

    server.AddDocument(45,"cat in the city"s, DocumentStatus::ACTUAL,{2, 2, 5});
    
    documents = server.FindTopDocuments("cat in the city"s);
    
    assert(documents[0].id == 45);
    assert(documents[1].id == 42);
    assert(documents[2].id == 43);
}

void TestRating() {
    SearchServer server = GetTestSearchServer(42, "cat in the city"s, {1, 2, 3});
    auto document = server.FindTopDocuments("cat"s)[0];

    assert(document.rating == 2);

    server.AddDocument(43,"pig in the subway"s,DocumentStatus::ACTUAL,{1, 4, 5, 6, 4});

    document = server.FindTopDocuments("pig"s)[0];
    assert(document.rating == 4);
}

void TestFilters() {
    SearchServer server = GetTestSearchServer(42, "cat in the city"s, {1, 2, 3});
    server.AddDocument(43, "dog in the city"s, DocumentStatus::ACTUAL, {1, 2, 2});
    server.AddDocument(44, "pig in the bar"s, DocumentStatus::BANNED, {3, 2, 5});
    auto documents = server.FindTopDocuments("Cat"s, 
            [](int document_id, DocumentStatus status, int rating) -> bool 
            {
                return document_id % 2 == 0;
            }
        );
    for (const auto& document : documents) {
        assert(document.id % 2 == 0);
    }

    documents = server.FindTopDocuments("pig"s, 
        [](int document_id, DocumentStatus status, int rating) -> bool 
        {
            return status == DocumentStatus::BANNED;
        });

    assert(documents.size() == 1);
}

void TestRelevance() {
    SearchServer server = GetTestSearchServer(42, "cat in the city"s, {1, 2, 3});
    server.AddDocument(43, "dog in the city"s, DocumentStatus::ACTUAL, {1, 2, 2});
    server.AddDocument(44, "pig in the bar"s, DocumentStatus::BANNED, {3, 2, 5});
    
    const auto documents = server.FindTopDocuments("Cat"s); 
    const vector<double> relevance_values = {log(3), 0, 0};
    const double EPSILON = 10e-6;

    for (int i = 0; i < documents.size(); ++i) {
        assert(abs(relevance_values[i] - documents[i].relevance) < EPSILON);
    }
}

// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
    TestExcludeStopWordsFromAddedDocumentContent();
    TestAddDocument();
    TestStopWords();
    TestMatching();
    TestRelevanceSorting();
    TestRating();
    TestFilters();
    TestRelevance();
}

// --------- Окончание модульных тестов поисковой системы -----------

int main() {
    TestSearchServer();
    // Если вы видите эту строку, значит все тесты прошли успешно
    cout << "Search server testing finished"s << endl;
}