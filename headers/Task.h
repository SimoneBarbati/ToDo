#ifndef TASK_H
#define TASK_H

#include <string>

#include "Codes.h"

class Task {
public:
  std::string title;
  std::string group;
  std::string notes;
  std::string date;
  TASK_STATUS status;

  Task(std::string title, std::string group, std::string notes,
       std::string date, TASK_STATUS status);
};

#endif
