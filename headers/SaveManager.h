#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <fstream>

class SaveManager {
public:
  static std::ifstream reader;
  static std::ofstream writer;

  static int Initialize();
  static int InitializeReader();
  static int WriteSave();
  static int ReadSave();
};

#endif
