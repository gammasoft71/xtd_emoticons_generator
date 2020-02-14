#pragma once
#include <unistd.h>
#include <json/json.h>
#include <xtd/xtd.core>
#include <xtd/xtd.console>
#include <filesystem>

class emoticons_class_generator {
public:
  emoticons_class_generator(const std::filesystem::path& emoji_data_root_path, const std::filesystem::path& generated_class_root_path) : emoji_data_root_path_(emoji_data_root_path), generated_class_root_path_(generated_class_root_path) {
    if (!exists(emoji_data_root_path_)) throw std::invalid_argument(xtd::strings::format("Path \"{}\" invalid", emoji_data_root_path));
  }
  
  auto emoji_data_root_path() const {return emoji_data_root_path_;}
  auto generated_class_root_path() const {return generated_class_root_path_;}
  auto convert_images_to_xpm() const {return convert_images_to_xpm_;}
  void convert_images_to_xpm(bool convert_images_to_xpm) {convert_images_to_xpm_ = convert_images_to_xpm;}
  auto regenerate() const {return regenerate_;}
  void regenerate(bool regenerate) {regenerate_ = regenerate;}
  auto verbose() const {return verbose_;}
  void verbose(bool verbose) {verbose_ = verbose;}

  auto generate() {
    write_line("emoji_data_root_path = {}", emoji_data_root_path_);
    write_line("generated_class_root_path = {}", generated_class_root_path_);
    write_line();
    if (regenerate_ && exists(generated_class_root_path_)) remove_all(generated_class_root_path_);
    create_directories(generated_class_root_path_);
    create_png_images();
    if (convert_images_to_xpm_)
      create_xpm_images();
  }

private:
  void create_png_images() {
    write_line("create png images...");
    auto target_png_images_path = generated_class_root_path_ / "resources" / "png_images";

    write_line("  create {} path", target_png_images_path);
    create_directories(target_png_images_path);

    change_directory_context directory_context {target_png_images_path};

    auto counter = 0;
    for (auto provider : providers) {
      for (const auto & file : std::filesystem::directory_iterator(emoji_data_root_path_ / xtd::strings::format("img-{}-64", provider))) {
        if (file.path().extension() == ".png") {
          ++counter;
          auto new_file = std::filesystem::path {xtd::strings::format("{}_{}_64x64{}", provider, file.path().stem().string(), file.path().extension().string())};
          write_line("  copy to {}", new_file.string());
          if (!exists(new_file)) {
            copy_file(file.path(), new_file);
          }
        }
      }
    }
    write_line("  {} png image copied", counter);
  }

  void create_xpm_images() {
    write_line("create xpm images...");

    auto target_png_images_path = generated_class_root_path_ / "resources" / "png_images";
    auto target_xpm_images_path = generated_class_root_path_ / "resources" / "xpm_images";

    write_line("  create {} path", target_xpm_images_path);
    create_directories(target_xpm_images_path);

    change_directory_context directory_context {target_xpm_images_path};

    auto counter = 0;
    for (const auto & file : std::filesystem::directory_iterator(target_png_images_path)) {
      if (file.path().extension() == ".png") {
        ++counter;
        auto new_file = std::filesystem::path {xtd::strings::format("{}.xpm", file.path().stem().string())};
        write_line("  convert to {}", new_file.string());
        if (!exists(new_file)) {
          auto pid = fork();
          if (pid == 0) {
            execlp("convert", "convert", file.path().string().c_str(), new_file.string().c_str(), 0);
            exit(0);
          } else {
            waitpid(pid, nullptr, 0);
          }
        }
      }
    }
    write_line("  {} xpm image converted", counter);
  }

  template<typename ... args_t>
  void write(const std::string& fmt, args_t&& ... args) {
    if (verbose_) xtd::console::write(fmt, args...);
  }
  
  void write_line() {
    if (verbose_) xtd::console::write_line();
  }
  
  template<typename ... args_t>
  void write_line(const std::string& fmt, args_t&& ... args) {
    if (verbose_) xtd::console::write_line(fmt, args...);
  }

  std::filesystem::path emoji_data_root_path_;
  std::filesystem::path generated_class_root_path_;
  std::vector<std::string> providers {"apple", "facebook", "google", "twitter"};
  bool convert_images_to_xpm_ = false;
  bool verbose_ = false;
  bool regenerate_ = false;
};
