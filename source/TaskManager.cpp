#include <vector>

#include "Codes.h"
#include "Task.h"
#include "TaskManager.h"

std::vector<Task> TaskManager::taskList;

void TaskManager::Initialize() { taskList.clear(); }

int TaskManager::CheckIndex(int index) {
  if (index >= taskList.size() || index < 0)
    return INDEX_OUT_OF_RANGE;
  return NO_ERRORS;
}

int TaskManager::AddTask(Task *task) {
  if (task == nullptr)
    return TASK_NOT_ADDED;
  taskList.push_back(*task);
  return TASK_ADDED_SUCCESSFULLY;
}

int TaskManager::RemoveTask(int taskIndex) {
  if (CheckIndex(taskIndex) == INDEX_OUT_OF_RANGE)
    return TASK_NOT_REMOVED;

  taskList.erase(taskList.begin() + taskIndex);

  return TASK_REMOVED_SUCCESSFULLY;
}

int TaskManager::CheckTask(int taskIndex) {
  if (CheckIndex(taskIndex) == INDEX_OUT_OF_RANGE)
    return TASK_NOT_CHECKED;
  taskList.at(taskIndex).status = CHECKED;

  return TASK_CHECKED_SUCCESSFULLY;
}

int TaskManager::UncheckTask(int taskIndex) {
  if (CheckIndex(taskIndex) == INDEX_OUT_OF_RANGE)
    return TASK_NOT_UNCHECKED;
  taskList.at(taskIndex).status = UNCHECKED;

  return TASK_UNCHECKED_SUCCESSFULLY;
}
