#include "Task.h"

Task::Task(std::string title, std::string group, std::string notes,
           TASK_STATUS status)
    : title(title), group(group), notes(notes), status(status) {}
