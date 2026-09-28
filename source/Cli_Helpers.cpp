#include <iostream>
#include <limits>

#include "Cli_Helpers.h"
#include "Codes.h"

std::string Cli::ReadString(int maxLen) {
  std::string res;
  std::getline(std::cin, res);

  if (maxLen > 0 && res.length() > static_cast<size_t>(maxLen))
    res.resize(maxLen);
  return res;
};

int Cli::ReadInt() {
  int res = 0;
  if (!(std::cin >> res))
    std::cin.clear();

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return res;
}

void Cli::Prompt(const char *line) {
  printf("%s > ", line);
  fflush(stdout);
}

void Cli::Print(PRINT_CODES code, const char *line) {
  if (code == INFO)
    printf("<< %s >>\n", line);
  else if (code == WARNING)
    printf("_<! %s !>_\n", line);
  else if (code == ERROR) {
    std::string separator = std::string(SEPARATOR_LEN, '=');
    printf("%s\n-%s-\n%s\n", separator.c_str(), line, separator.c_str());
  }
}

void Cli::ClearScreen() {
  printf("\033[H");  // go to topleft
  printf("\033[0J"); // clear
  fflush(stdout);
}
