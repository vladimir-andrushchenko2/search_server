#include "string_processing.h"

#include <sstream>

namespace string_processing {

std::vector<std::string> SplitIntoWords(const std::string& text) {
    std::istringstream text_stream(text);

    std::vector<std::string> words;

    std::string word;
    while (text_stream >> word) {
        words.push_back(word);
    }

    return words;
}

std::vector<std::string_view> SplitIntoWords(std::string_view text) {
    std::vector<std::string_view> result;

    while (true) {
        size_t space = text.find(' ');

        result.push_back(text.substr(0, space));

        if (space == text.npos) {
            break;
        } else {
            text.remove_prefix(space + 1);
        }
    }

    return result;
}

}  // namespace string_processing
