#include <vector>

#include "Task.h"

class TaskManager {
public:
  static std::vector<Task> taskList;

  static void Initialize();

  static int CheckIndex(int index);

  static int AddTask(Task *task);
  static int RemoveTask(int taskIndex);
  static int CheckTask(int taskIndex);
  static int UncheckTask(int taskIndex);
};
