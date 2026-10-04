#include "General.h"
#include "SaveManager.h"

int QuitApp() {
  SaveManager::WriteSave();
  return 0;
}
