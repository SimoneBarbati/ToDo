#include "Task.h"

Task::Task(std::string title, std::string group, std::string notes,
           TaskStatus status)
    : title(title), group(group), notes(notes), status(status) {}
