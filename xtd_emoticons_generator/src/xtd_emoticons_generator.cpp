#include "change_directory_context.hpp"
#include "emoticons_class_generator.hpp"

using namespace std;
using namespace std::filesystem;
using namespace std::literals;
using namespace xtd;

int main() {
  /// @todo check arguments
  if (environment::get_command_line_args().size() != 3)
    throw invalid_argument("No emoji-data root and destination paths arguments");

  /// @todo initialize generator from arguments...
  emoticons_class_generator generator {environment::get_command_line_args()[1], environment::get_command_line_args()[2]};
  generator.verbose(true);
  generator.regenerate(false);
  generator.convert_images_to_xpm(false);

  // run...
  generator.generate();
}
