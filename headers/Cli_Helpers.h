#ifndef CLI_HELPERS_H
#define CLI_HELPERS_H

#include "Codes.h"
#include <string>

namespace Cli {

const int SEPARATOR_LEN = 100;
std::string ReadString(int maxLen);
int ReadInt();

void Prompt(const char *line = "");
void Print(PRINT_CODES code, const char *line = "");
void ClearScreen();

} // namespace Cli
#endif
