#include "Task.h"

Task::Task(std::string title, std::string group, std::string notes,
           std::string date, TASK_STATUS status)
    : title(title), group(group), notes(notes), date(date), status(status) {}
