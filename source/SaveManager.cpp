#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "Codes.h"
#include "SaveManager.h"
#include "Task.h"
#include "TaskManager.h"

std::ifstream SaveManager::reader;

int SaveManager::Initialize() {
  InitializeReader();
  ReadSave();
  return 0;
}

int SaveManager::InitializeReader() {
  if (reader.is_open()) {
    reader.close();
  }

  std::filesystem::create_directories("data");

  reader.open("data/save");

  if (!reader.is_open()) {
    std::ofstream writer("data/save");
    if (!writer.is_open()) {
      return FILE_OPEN_FAILED;
    }
    writer.close();

    reader.open("data/save");
  }

  return reader.is_open() ? NO_ERRORS : FILE_OPEN_FAILED;
}

int SaveManager::WriteSave() {
  if (reader.is_open())
    reader.close();

  std::ofstream writer("data/save");
  if (!writer.is_open())
    return FILE_OPEN_FAILED;

  for (const Task &task : TaskManager::taskList) {
    std::string line;
    writer << task.title << '|' << task.group << '|' << task.notes << '|'
           << task.date << '|' << static_cast<int>(task.status) << '\n';
  }

  writer.close();

  InitializeReader();

  return NO_ERRORS;
}

int SaveManager::ReadSave() {
  TaskManager::taskList.clear();
  TASK_STATUS status;

  if (!reader.is_open())
    InitializeReader();

  std::string line;
  while (std::getline(reader, line)) {
    if (line.empty())
      continue;

    std::stringstream linestream(line);
    std::string title, group, notes, date, statusStr;
    if (std::getline(linestream, title, '|') &&
        std::getline(linestream, group, '|') &&
        std::getline(linestream, notes, '|') &&
        std::getline(linestream, date, '|') &&
        std::getline(linestream, statusStr)) {
      int istatus = 0;
      try {
        istatus = std::stoi(statusStr);
      } catch (...) {
        istatus = 0;
      }

      TaskManager::taskList.push_back(
          Task(title, group, notes, date, (TASK_STATUS)istatus));
    }
  }
  return NO_ERRORS;
}
