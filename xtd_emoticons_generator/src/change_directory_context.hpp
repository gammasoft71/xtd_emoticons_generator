#pragma once
#include <xtd/xtd.core>
#include <filesystem>

class change_directory_context {
public:
  explicit change_directory_context(const std::filesystem::path& directory) : change_directory_context(directory.string()) {}
  explicit change_directory_context(const std::string& directory) {
    previous_context_directory_ = xtd::environment::current_directory();
    xtd::environment::current_directory(directory);
  }
  ~change_directory_context() {xtd::environment::current_directory(previous_context_directory_);}
  
private:
  std::string previous_context_directory_;
};
