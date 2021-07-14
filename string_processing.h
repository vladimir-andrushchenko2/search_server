#pragma once

#include <string>
#include <vector>

namespace string_processing {

std::vector<std::string_view> SplitIntoWords(std::string_view text);

std::vector<std::string> SplitIntoWords(const std::string& text);

}  // namespace string_processing
