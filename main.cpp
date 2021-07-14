#include <execution>
#include <iostream>
#include <string>
#include <vector>

#include "process_queries.h"
#include "search_server.h"
#include "test_search_server.h"

int main() {
    TestSearchServer();

    SearchServer search_server("and with"s);

    int id = 0;
    for (const std::string& text : {
             "white cat and yellow hat"s,
             "curly cat curly tail"s,
             "nasty dog with big eyes"s,
             "nasty pigeon john"s,
         }) {
        search_server.AddDocument(++id, text, DocumentStatus::ACTUAL, {1, 2});
    }

    std::cout << "ACTUAL by default:"s << std::endl;
    // последовательная версия
    for (const Document& document : search_server.FindTopDocuments("curly nasty cat"s)) {
        PrintDocument(document);
    }
    std::cout << "BANNED:"s << std::endl;
    // последовательная версия
    for (const Document& document :
         search_server.FindTopDocuments(std::execution::seq, "curly nasty cat"s, DocumentStatus::BANNED)) {
        PrintDocument(document);
    }

    std::cout << "Even ids:"s << std::endl;
    // параллельная версия
    for (const Document &document : search_server.FindTopDocuments(
             std::execution::par, "curly nasty cat"s,
             [](int document_id, DocumentStatus status, int rating) { return document_id % 2 == 0; })) {
        PrintDocument(document);
    }

    return 0;
}