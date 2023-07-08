#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

/* Подставьте вашу реализацию класса SearchServer сюда */
const int MAX_RESULT_DOCUMENT_COUNT = 5;
const double EPSILON = 1e-6;

// считывание строки из ввода
string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

// считывание числа из ввода
int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

// разбиение строки на слова
vector<string> SplitIntoWords(const string& text) {
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

    // запись стоп-слов из ввода
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    // добавление нового документа
    void AddDocument(int document_id, const string& document, DocumentStatus status,
                     const vector<int>& ratings) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size(); // расчет term frequency
        for (const string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count; 
        }
        documents_.emplace(document_id, DocumentData{ComputeAverageRating(ratings), status});
    }

    // возвращает MAX_RESULT_DOCUMENT_COUNT документов с наибольшей релевантностью/рейтингом
    template <typename KeyMapper>
    vector<Document> FindTopDocuments(const string& raw_query, KeyMapper key_mapper) const {
        const Query query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query, key_mapper);

        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document& lhs, const Document& rhs) {
                 return lhs.relevance > rhs.relevance || ((std::abs(lhs.relevance - rhs.relevance) < EPSILON) && lhs.rating > rhs.rating);
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

    // возвращает MAX_RESULT_DOCUMENT_COUNT документов с наибольшей релевантностью/рейтингом
    // вариант функции с возможностью указать статус документа
    vector<Document> FindTopDocuments(const string& raw_query, DocumentStatus document_status = DocumentStatus::ACTUAL) const {
        const Query query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query, [document_status](int document_id, DocumentStatus status, int rating) { return status == document_status; });

        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document& lhs, const Document& rhs) {
                 return lhs.relevance > rhs.relevance || ((std::abs(lhs.relevance - rhs.relevance) < EPSILON) && lhs.rating > rhs.rating);
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

    // количество документов в системе
    int GetDocumentCount() const
    {
        return static_cast<int>(documents_.size());
    }

    tuple<vector<string>, DocumentStatus> MatchDocument(const string& raw_query, int document_id) const {
        const Query query = ParseQuery(raw_query);
        vector<string> matched_words;
        for (const string& word : query.plus_words) 
        {
          if (word_to_document_freqs_.count(word) == 0) 
          {
            continue;
          }

          if (word_to_document_freqs_.at(word).count(document_id)) 
          {
            matched_words.push_back(word);
          }
        }
        for (const string& word : query.minus_words) 
        {
          if (word_to_document_freqs_.count(word) == 0) 
          {
            continue;
          }
          if (word_to_document_freqs_.at(word).count(document_id)) 
          {
            matched_words.clear();
            break;
          }
        }
        return {matched_words, documents_.at(document_id).status};
    }
    
private:
    struct DocumentData {
        int rating;
        DocumentStatus status;
    };

    set<string> stop_words_;
    map<string, map<int, double>> word_to_document_freqs_; // слова, id документов, tf
    map<int, DocumentData> documents_; // id, рейтинг, статус

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    // разбитие строки на слова и фильтрация стоп-слов
    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    // расчет среднего значения рейтинга документа
    static int ComputeAverageRating(const vector<int>& ratings) {
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

    // возврат слова из запроса и его характеристик: стоп или минус слово
    QueryWord ParseQueryWord(string text) const {
        bool is_minus = false;
        // Word shouldn't be empty
        if (text[0] == '-') {
            is_minus = true;
            text = text.substr(1);
        }
        return {text, is_minus, IsStopWord(text)};
    }

    struct Query {
        set<string> plus_words;
        set<string> minus_words;
    };

    Query ParseQuery(const string& text) const {
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

    // Existence required
    double ComputeWordInverseDocumentFreq(const string& word) const {
        return log(documents_.size() * 1.0 / word_to_document_freqs_.at(word).size());
    }

    // расчет релевантности документа
    template <typename KeyMapper>
    vector<Document> FindAllDocuments(const Query& query, KeyMapper key_mapper) const {
        map<int, double> document_to_relevance;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
            for (const auto [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                if (key_mapper(document_id, documents_.at(document_id).status, documents_.at(document_id).rating)) {
                    document_to_relevance[document_id] += term_freq * inverse_document_freq;
                }
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

// -------- Начало модульных тестов поисковой системы ----------

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = {1, 2, 3};
    SearchServer server;
    server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
    const auto found_docs = server.FindTopDocuments("in"s);
    // Сначала убеждаемся, что поиск слова, не входящего в список стоп-слов,
    // находит нужный документ
    {
        const Document& doc0 = found_docs[0];
        assert(found_docs.size() == 1);
        assert(doc0.id == doc_id);
    }
 
    // Затем убеждаемся, что поиск этого же слова, входящего в список стоп-слов,
    // возвращает пустой результат
    {
        assert(found_docs.empty());
    }
}
 
void TestFindTopDocuments() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar", DocumentStatus::ACTUAL, {8, -3});
  search_server.AddDocument(1, "fluffy cat fluffy tail", DocumentStatus::ACTUAL, {7, 2, 7});
  search_server.AddDocument(2, "groomed dog expressive eyes", DocumentStatus::BANNED, {5, -12, 2, 1});
  
    {
      const auto documents = search_server.FindTopDocuments("fluffy groomed cat");
      assert(documents.size() == 2);  // Only two documents with status ACTUAL should be returned
    }
    
    {
         const auto documents = search_server.FindTopDocuments("fluffy groomed cat", DocumentStatus::BANNED);
          assert(documents.size() == 1);
    }
    
    {
         auto predicate = [](int document_id, DocumentStatus status [[maybe_unused]], int rating [[maybe_unused]]) {
            return document_id % 2 == 0;  // Only accept documents with even ids
          };
          const auto documents = search_server.FindTopDocuments("fluffy groomed cat", predicate);
          assert(documents.size() == 2); 
    }
 
}
 
/*
Разместите код остальных тестов здесь
*/
 
void TestMatchDocument() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3});
  auto [words, status] = search_server.MatchDocument("white cat"s, 0);
  assert(words.size() == 2);
  assert(words[0] == "cat");
  assert(words[1] == "white");
}
 
void TestStopWords() {
  SearchServer search_server;
  search_server.SetStopWords("and"s);
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3});
  vector<Document> results = search_server.FindTopDocuments("and"s);
  assert(results.empty());
}
 
void TestMinusWords() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3});
  vector<Document> results = search_server.FindTopDocuments("cat -white"s);
  assert(results.empty());
}
 
void TestSortByRelevance() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3});
  search_server.AddDocument(1, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3, 10});
  vector<Document> results = search_server.FindTopDocuments("white cat"s);
  assert(results.size() == 2);
  assert(results[0].id == 1);
  assert(results[1].id == 0);
}
 
void TestComputeAverageRating() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3, 10});
  vector<Document> results = search_server.FindTopDocuments("white cat"s);  
  assert(results.at(0).rating == 5);
}
 
void TestPredicateFiltering() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3});
  search_server.AddDocument(1, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3, 10});
  vector<Document> results = search_server.FindTopDocuments(
      "white cat"s, [](int document_id, DocumentStatus , int ) {
        return document_id % 2 == 0;
      });
  assert(results.size() == 1);
  assert(results[0].id == 0);
}
 
void TestStatusFiltering() {
  SearchServer search_server;
  search_server.AddDocument(0, "white cat and fashionable collar"s,
                            DocumentStatus::ACTUAL, {8, -3});
  search_server.AddDocument(1, "white cat and fashionable collar"s,
                            DocumentStatus::BANNED, {8, -3, 10});
  vector<Document> results = search_server.FindTopDocuments(
      "white cat"s, DocumentStatus::ACTUAL);
  assert(results.size() == 1);
  assert(results[0].id == 0);
}
 
// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
    TestExcludeStopWordsFromAddedDocumentContent();
    TestFindTopDocuments();
    TestMatchDocument(); 
    TestStopWords();
    TestMinusWords();
    TestSortByRelevance();
    TestComputeAverageRating();
    TestPredicateFiltering();
    TestStatusFiltering();
    // Не забудьте вызывать остальные тесты здесь
}

// --------- Окончание модульных тестов поисковой системы -----------

int main() {
    TestSearchServer();
    // Если вы видите эту строку, значит все тесты прошли успешно
    cout << "Search server testing finished"s << endl;
}