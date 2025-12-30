#pragma once
#include <stdexcept>
#include <string>

namespace qis {

struct QisError : std::runtime_error {
  explicit QisError(const std::string& msg) : std::runtime_error(msg) {}
};

} // namespace qis
