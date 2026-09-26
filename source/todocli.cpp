#include <iostream>
#include <limits>
#include <stdio.h>
#include <string>

#include "Codes.h"
#include "Task.h"
#include "TaskManager.h"

const int SEPARATOR_LEN = 100;

std::string ReadString(int maxLen);
void Prompt(const char *line);
void Inform(const char *line);
void ClearScreen();

void PrintActions();
void PrintTaskList();
int GetAction(int min, int max);
int ManageActionInput(int action);

int CliSelectTask();
int CliCreateTask();
int CliRemoveTask();
void CliCheckTask();
void CliUncheckTask();

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

std::string ReadString(int maxLen) {
  std::string res;
  std::getline(std::cin, res);

  if (maxLen > 0 && res.length() > static_cast<size_t>(maxLen))
    res.resize(maxLen);
  return res;
};

int ReadInt() {
  int res = 0;
  if (!(std::cin >> res))
    std::cin.clear();

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return res;
}

void Prompt(const char *line = "") {
  printf("%s > ", line);
  fflush(stdout);
}

void Print(PRINT_CODES code, const char *line = "") {
  if (code == INFO)
    printf("<< %s >>\n", line);
  else if (code == WARNING)
    printf("_<! %s !>_\n", line);
  else if (code == ERROR) {
    std::string separator = std::string(SEPARATOR_LEN, '=');
    printf("%s\n-%s-\n%s\n", separator.c_str(), line, separator.c_str());
  }
}

void ClearScreen() {
  printf("\033[2J"); // clear
  printf("\033F");   // move to bottomleft
  fflush(stdout);
}

void PrintActions() {
  printf("\n- Available Actions:\n"
         "1. Create Task;\n"
         "2. Remove Task;\n"
         "3. Check Task;\n"
         "4. Uncheck Task;\n"
         "5. Show Tasks;\n"
         "6. Quit;\n");
  Prompt();
}

void PrintTaskList() {
  printf("// Task List --\n");
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

  printf(R"(-- Task List \\)"
         "\n");
}

int GetAction(int min, int max) {
  int action = ReadInt();
  if (action < min || action > max)
    return INDEX_OUT_OF_RANGE;

  return action;
}

int ManageActionInput(int action) {
  if (action == -1) {
    printf("-! Action out of bounds !-\n");
    return INDEX_OUT_OF_RANGE;
  }

  ClearScreen();

  switch (action) {
  case 1:
    if (CliCreateTask() == TASK_ADDED_SUCCESSFULLY)
      Print(INFO, "task creation was SUCCESSFUL");
    else
      Print(WARNING, "task creation was UNSUCCESSFUL");
    break;

  case 2:
    if (CliRemoveTask() == TASK_REMOVED_SUCCESSFULLY)
      Print(INFO, "task deletion was SUCCESSFUL");
    else
      Print(WARNING, "task deletion was UNSUCCESSFUL");
    break;

  case 3:
    CliCheckTask();
    break;

  case 4:
    CliUncheckTask();
    break;

  case 5:
    PrintTaskList();
    break;

  default:
    Print(INFO, "Goodbye!");
    return -1;
  }

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

  printf("-Task Creation-\n");

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
  printf("-Task Deletion-\n");

  int index = CliSelectTask();
  return TaskManager::RemoveTask(index);
}

void CliCheckTask() {}

void CliUncheckTask() {}
