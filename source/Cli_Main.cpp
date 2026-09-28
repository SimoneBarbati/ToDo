#include <stdio.h>
#include <string>
#include <unistd.h>

#include "Cli_Helpers.h"
#include "Cli_Main.h"
#include "Codes.h"
#include "Task.h"
#include "TaskManager.h"

using namespace Cli;

// TODO : Create standard input reading
// TODO : Create standard output

int main() {
  ClearScreen();
  TaskManager::Initialize();

  int running = 1;

  PrintTaskList();

  while (running) {
    PrintActions();
    int action = GetAction(1, 6);
    int actionOut = ManageActionInput(action);
    if (actionOut == -1) {
      running = false;
      continue;
    }
  }

  return 0;
}

void PrintActions() {
  printf("- Available Actions:\n"
         "1. Create Task;\n"
         "2. Remove Task;\n"
         "3. Check Task;\n"
         "4. Uncheck Task;\n"
         "5. Show Tasks;\n"
         "6. Quit;\n");
  Prompt();
}

void PrintTaskList() {
  if (TaskManager::taskList.size() < 1)
    return;

  Print(INFO, "Task List");
  int i = 1;
  for (auto &task : TaskManager::taskList) {
    std::string index = (i < 10 ? "0" : "") + std::to_string(i);
    std::string separator = std::string(SEPARATOR_LEN - 2, '-') + index;

    printf("%s\n", separator.c_str());
    printf("Title: %s\n"
           "Group: %s\n"
           "Notes: %s\n"
           "Status: %i\n",
           task.title.c_str(), task.group.c_str(), task.notes.c_str(),
           task.status);
    printf("%s\n", std::string(SEPARATOR_LEN, '-').c_str());

    i++;
  }

  Print(INFO, "Task List");
}

int GetAction(int min, int max) {
  int action = ReadInt();
  if (action < min || action > max)
    return INDEX_OUT_OF_RANGE;

  return action;
}

int ManageActionInput(int action) {
  int result;

  if (action == -1) {
    Print(ERROR, "Action out of bounds");
    return INDEX_OUT_OF_RANGE;
  }

  ClearScreen();

  switch (action) {
  case 1:
    Print(INFO, "Task Creation");
    result = CliCreateTask();
    ClearScreen();
    if (result == TASK_ADDED_SUCCESSFULLY)
      Print(INFO, "task creation was SUCCESSFUL");
    else
      Print(WARNING, "task creation was UNSUCCESSFUL");
    break;

  case 2:
    Print(INFO, "Task Deletion");
    result = CliRemoveTask();
    ClearScreen();
    if (result == TASK_REMOVED_SUCCESSFULLY)
      Print(INFO, "task deletion was SUCCESSFUL");
    else
      Print(WARNING, "task deletion was UNSUCCESSFUL");
    break;

  case 3:
    Print(INFO, "Task Checking");
    result = CliCheckTask();
    ClearScreen();
    if (result == TASK_CHECKED_SUCCESSFULLY)
      Print(INFO, "task checking was SUCCESSFUL");
    else
      Print(WARNING, "task checking was UNSUCCESSFUL");
    break;

  case 4:
    Print(INFO, "Task Unchecking");
    result = CliUncheckTask();
    ClearScreen();
    if (result == TASK_UNCHECKED_SUCCESSFULLY)
      Print(INFO, "task unchecking was SUCCESSFUL");
    else
      Print(WARNING, "task unchecking was UNSUCCESSFUL");
    break;

  case 5:
    PrintTaskList();
    break;

  default:
    Print(INFO, "Goodbye!");
    return -1;
  }

  usleep(500000);
  Prompt("Enter to Continue");
  ReadString(1);
  ClearScreen();

  return 0;
}

int CliSelectTask() {
  printf("-Task Selection-\n");
  PrintTaskList();
  Prompt("Insert Task Index");
  return ReadInt() - 1;
}

int CliCreateTask() {
  std::string title, notes, date;

  Prompt("Enter Task Title");
  title = ReadString(30);

  Prompt("Enter Task Notes");
  notes = ReadString(100);

  Prompt("Enter Task Due Date (dd/mm/yy)");
  date = ReadString(8);

  Task task = Task(title, "no-group", notes, UNCHECKED);
  return TaskManager::AddTask(&task);
}

int CliRemoveTask() {
  int index = CliSelectTask();
  return TaskManager::RemoveTask(index);
}

int CliCheckTask() {
  int index = CliSelectTask();
  return TaskManager::CheckTask(index);
}

int CliUncheckTask() {
  int index = CliSelectTask();
  return TaskManager::UncheckTask(index);
}
