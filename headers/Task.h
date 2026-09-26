#ifndef TASK_H
#define TASK_H

#include <string>

#include "Task_Status.h"

class Task {
public:
  std::string title;
  std::string group;
  std::string notes;
  TaskStatus status;

  Task(std::string title, std::string group, std::string notes,
       TaskStatus status);
};

#endif
