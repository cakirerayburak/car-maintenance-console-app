/**
 * @file CarMaintenance.h
 * @brief Declarations and definitions for the Car Maintenance application.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "CarMaintenance.h"
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "MainMenu.h"


/**
 * @brief Width of the screen.
 */
int screenWidth = 80;

/**
 * @brief Height of the screen.
 */
int screenHeight = 24;
int x = (screenWidth - 32) / 2;
int y = (screenHeight - 11) / 2;

char username[] = "admin";
char password[] = "123";



const char *loginMenu[] = {
  "             Login             ",
  "            Register           ",
  "           Guest Mod           "
};

const char *authenticetedOptions[] = {
  "   Project and Budget Planning  ",
  "  Task Assignment and Tracking  ",
  "   Cost Analysis and Reporting  ",
  "Supplier and Contractor Database",
  "         Integrations           ",
  "             Exit               "
};

const char *projectOptions[] = {
  "         Create Project         ",
  "          View Project          ",
  "          Edit Project          ",
  "         Delete Project         ",
  "       Return to Main Menu      "
};


const char *taskOptions[] = {
  "          Assign Task           ",
  "          View Tasks            ",
  "       Update Task Status       ",
  "       Return to Main Menu      "
};

const char *costOptions[] = {
  "           Add Expense          ",
  "          View Expenses         ",
  "         Generate Reports       ",
  "       Return to Main Menu      "
};

const char *supplierOptions[] = {
  "           Add Supplier         ",
  "          Edit Supplier         ",
  "         Delete Supplier        ",
  "       Return to Main Menu      "
};

/**
 * @brief Adds users to a file.
 *
 * This function adds the specified users to a file. If the file does not exist,
 * it is created. Each added user is appended to the end of the file.
 *
 * @param users An array containing the users.
 * @return A value representing the success status. 0 indicates success, -1 indicates an error.
 *
 * @note The file name and user information should follow a specific structure.
 * @warning If there is an error opening the file, an error message is printed.
 */
int addUser(struct User users[],size_t userNumber) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "login.bin", "ab");;

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  for(size_t i = 0; i < userNumber; ++i) {
    fwrite(&users[i], sizeof(struct User), 1, fp);
  }

  fclose(fp);
  //fwrite(users, sizeof(struct User), 1, fp);
  //fclose(fp);
  return 1;
}

/**
 * @brief Reads users from a file and prints their information.
 *
 * This function opens the file "login.bin" and reads user information from it.
 * It prints the username, password, and status of each user to the console.
 *
 * @return A value representing the success status. 0 indicates success, 1 indicates an error.
 *
 * @note The file "login.bin" should exist, and the user structure in the file should follow a specific format.
 * @warning If there is an error opening the file, an error message is printed.
 */
int readUser() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "login.bin", "rb");;

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct User users;

  while (fread(&users, sizeof(struct User), 1, fp) == 1) {
    if(users.password!=0) {
      printf("Username: %s, Passsword: %d, Status: %d\n", users.username,users.password,users.status);
    }
  }

  fclose(fp);
  return 1;
}

/**
 * @brief Deletes a user from the file.
 *
 * This function searches for a user with the specified username in the "login.bin" file,
 * and if found, marks the user as deleted by overwriting its data with null values.
 *
 * @param username The username of the user to be deleted.
 * @return A value representing the success status.
 *         - 0 indicates success.
 *         - -1 indicates an error in file opening.
 *         - 1 indicates that the specified user was not found.
 *
 * @note The "login.bin" file should exist, and the user structure in the file should follow a specific format.
 * @warning If there is an error opening the file or the specified user is not found, an error message is printed.
 */
int deleteUser(const char *username) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "login.bin", "rb+");;

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct User currentUser;

  long int currentPosition = ftell(fp);
  int userFound = 0;

  // Find and delete the user with the specified username
  while (fread(&currentUser, sizeof(struct User), 1, fp) == 1) {
    if (strcmp(currentUser.username, username) == 0) {
      userFound = 1;
      break;
    }

    currentPosition = ftell(fp);
  }

  if (!userFound) {
    fclose(fp);
    printf("User with username %s not found.\n", username);
    return -1; // User not found
  }

  // Move the file pointer to the beginning of the user to be deleted
  fseek(fp, currentPosition, SEEK_SET);
  // Overwrite the user with null data
  struct User nullUser = { 0 };
  fwrite(&nullUser, sizeof(struct User), 1, fp);
  fclose(fp);
  return 1;
}

int updateUser() {
  return 0;
}

/**
 * @brief Adds projects to a file.
 *
 * This function adds the specified projects to a file. If the file does not exist,
 * it is created. Each added project is appended to the end of the file.
 *
 * @param project An array containing the projects.
 * @param projectNumber The number of projects in the array.
 * @return A value representing the success status.
 *         - 1 indicates success.
 *         - -1 indicates an error in file opening.
 *
 * @note The file name and project information should follow a specific structure.
 * @warning If there is an error opening the file, an error message is printed.
 */
int addProject(Project project[], size_t projectNumber) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "project.bin", "ab");

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  for (size_t i = 0; i < projectNumber; ++i) {
    fwrite(&project[i], sizeof(struct Project), 1, fp);
  }

  fclose(fp);
  return 1;
}


/**
 * @brief Deletes a project from the file based on the driver's name.
 *
 * This function deletes the project with the specified driver's name from the "project.bin" file.
 *
 * @param driverName The name of the driver associated with the project to be deleted.
 * @return A value representing the success status.
 *         - 1 indicates success.
 *         - -1 indicates an error in file opening.
 *         - 0 indicates the project not found.
 *
 * @note The file "project.bin" should exist, and the project structure in the file should follow a specific format.
 * @warning If there is an error opening the file or the specified project is not found, an error message is printed.
 */
int deleteProject(const char *driverName) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "project.bin", "rb+");;

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Project currentProject;

  long int currentPosition = ftell(fp);
  int projectFound = 0;

  // Find and delete the user with the specified username
  while (fread(&currentProject, sizeof(struct Project), 1, fp) == 1) {
    if (strcmp(currentProject.driverName, driverName) == 0) {
      projectFound = 1;
      break;
    }

    currentPosition = ftell(fp);
  }

  if (!projectFound) {
    fclose(fp);
    printf("User with username %s not found.\n", driverName);
    return -1; // User not found
  }

  // Move the file pointer to the beginning of the user to be deleted
  fseek(fp, currentPosition, SEEK_SET);
  // Overwrite the user with null data
  struct Project nullProject = { 0 };
  fwrite(&nullProject, sizeof(struct Project), 1, fp);
  fclose(fp);
  return 1;
}


/**
 * @brief Reads projects from a file and prints their information.
 *
 * This function opens the file "project.bin" and reads project information from it.
 * It prints the brand, year, action, driver name, driver phone, kilometer, date, status, and other details
 * of each project to the console.
 *
 * @return A value representing the success status. 1 indicates success, 0 indicates an error.
 *
 * @note The file "project.bin" should exist, and the project structure in the file should follow a specific format.
 * @warning If there is an error opening the file, an error message is printed.
 */
int readProject() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "project.bin", "rb+");;

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Project project;

  while (fread(&project, sizeof(struct Project), 1, fp) == 1) {
    if (project.kilometer != 0) {
      printf("Brand: %s, Year: %d, Action: %s, Driver Name: %s, Driver Phone: %d, Kilometer: %d, Date: %s,Durum: %d\n",
             project.brand, project.year, project.action, project.driverName, project.driverPhone,
             project.kilometer, project.date1,project.status);
    }
  }

  fclose(fp);
  return 1;
}

int updateProject() {
  return 0;
}

/**
 * @brief Adds a task to the system.
 *
 * This function adds the specified tasks to the system. If the system file does not exist,
 * it is created. Each added task is appended to the end of the file.
 *
 * @param task An array containing the tasks.
 * @param taskNumber The number of tasks to add.
 * @return A value representing the success status. 1 indicates success, -1 indicates an error.
 *
 * @note The file name and task information should follow a specific structure.
 * @warning If there is an error opening the file, an error message is printed.
 */
int addTask(Task task[], size_t taskNumber) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "ab");;

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  for (size_t i = 0; i < taskNumber; ++i) {
    fwrite(&task[i], sizeof(struct Task), 1, fp);
  }

  fclose(fp);
  return 1;
}

int deleteTask() {
  return 0;
}

/**
 * @brief Updates the status of a task in the task file.
 *
 * This function opens the "task.bin" file and searches for a task with the specified driverName.
 * If the task is found, its status is updated to the provided statusNew.
 *
 * @param task An array of Task structures.
 * @param driverName The name of the driver whose task status needs to be updated.
 * @param statusNew The new status to be set for the task.
 * @return Returns 1 on success, -1 on failure (file opening failure or task not found).
 *
 * @warning This function assumes that the "task.bin" file contains binary data of Task structures.
 * The file should be opened in "rb+" mode for both reading and writing.
 */
int updateTaskStatus(Task task[], const char *driverName, int statusNew) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "rb+");

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Task currentTask;

  long int currentPosition = ftell(fp);
  int taskFound = 0;

  // Find the task with the specified driverName
  while (fread(&currentTask, sizeof(struct Task), 1, fp) == 1) {
    if (strcmp(currentTask.driverName, driverName) == 0) {
      taskFound = 1;
      break;
    }

    currentPosition = ftell(fp);
  }

  if (!taskFound) {
    fclose(fp);
    printf("Task with Driver Name: %s not found.\n", driverName);
    return -1; // Task not found
  }

  // Move the file pointer to the beginning of the task to be updated
  fseek(fp, currentPosition, SEEK_SET);
  // Update the task with null data
  struct Task nullTask = { 0 };
  fwrite(&nullTask, sizeof(struct Task), 1, fp);
  // Move the file pointer to the beginning of the task to be updated again
  fseek(fp, currentPosition, SEEK_SET);
  // Update the task with the new status
  currentTask.status = statusNew;
  fwrite(&currentTask, sizeof(struct Task), 1, fp);
  fclose(fp);
  return 1;
}


/**
 * @brief Reads and prints task information from the "task.bin" file.
 *
 * This function opens the "task.bin" file in read-only mode and prints the information
 * of each task stored in the file. The information includes brand, driver name, description,
 * assignee, date, and status. Tasks with an empty driver name are skipped.
 *
 * @return Returns 1 on success, -1 on failure (file opening failure).
 *
 * @warning This function assumes that the "task.bin" file contains binary data of Task structures.
 * The file should be opened in "rb" mode for reading.
 */
int readTask() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "rb");

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Task task;

  while (fread(&task, sizeof(struct Task), 1, fp) == 1) {
    if (strlen(task.driverName) > 0) {
      printf("Brand: %s, Driver Name: %s, Description: %s, Assignee: %s, Date: %s, Status: %d\n",
             task.brand, task.driverName, task.description, task.assignee, task.date1, task.status);
    }
  }

  fclose(fp);
  return 1;
}

/**
 * @brief Adds cost information to the "cost.bin" file.
 *
 * This function opens the "cost.bin" file in append mode and adds cost information
 * from the provided Cost array to the end of the file.
 *
 * @param cost An array of Cost structures containing the cost information to be added.
 * @param costNumber The number of elements in the cost array.
 * @return Returns 1 on success, -1 on failure (file opening failure).
 *
 * @warning This function assumes that the "cost.bin" file contains binary data of Cost structures.
 * The file should be opened in "ab" mode for appending.
 */
int addCost(Cost cost[], size_t costNumber) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "cost.bin", "ab");;

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  for (size_t i = 0; i < costNumber; ++i) {
    fwrite(&cost[i], sizeof(struct Cost), 1, fp);
  }

  fclose(fp);
  return 1;
}

/**
 * @brief Reads and prints cost information from the "cost.bin" file.
 *
 * This function opens the "cost.bin" file in read-only mode and prints the information
 * of each cost stored in the file. The information includes brand, driver name, date,
 * supplier, price, and material. Costs with an empty driver name are skipped.
 *
 * @return Returns 1 on success, -1 on failure (file opening failure).
 *
 * @warning This function assumes that the "cost.bin" file contains binary data of Cost structures.
 * The file should be opened in "rb" mode for reading.
 */
int readCost() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "cost.bin", "rb");

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Cost cost;

  while (fread(&cost, sizeof(struct Cost), 1, fp) == 1) {
    if (strlen(cost.driverName) > 0) {
      printf("Brand: %s, Driver Name: %s, Date1: %s, Supplier: %s, Price: %f, Material: %s\n",
             cost.brand, cost.driverName, cost.date1, cost.supplier, cost.price, cost.material);
    }
  }

  fclose(fp);
  return 1;
}

/**
 * @brief Adds supplier information to the "supplier.bin" file.
 *
 * This function opens the "supplier.bin" file in append mode and adds supplier information
 * from the provided Supplier array to the end of the file.
 *
 * @param supplier An array of Supplier structures containing the supplier information to be added.
 * @param supplierNumber The number of elements in the supplier array.
 * @return Returns 1 on success, -1 on failure (file opening failure).
 *
 * @warning This function assumes that the "supplier.bin" file contains binary data of Supplier structures.
 * The file should be opened in "ab" mode for appending.
 */
int addSupplier(Supplier supplier[], size_t supplierNumber) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "supplier.bin", "ab");;

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  for (size_t i = 0; i < supplierNumber; ++i) {
    fwrite(&supplier[i], sizeof(struct Supplier), 1, fp);
  }

  fclose(fp);
  return 1;
}

/**
 * @brief Reads and prints supplier information from the "supplier.bin" file.
 *
 * This function opens the "supplier.bin" file in read-only mode and prints the information
 * of each supplier stored in the file. The information includes supplier name, contact number,
 * email, and business type. Suppliers with an empty name are skipped.
 *
 * @return Returns 1 on success, -1 on failure (file opening failure).
 *
 * @warning This function assumes that the "supplier.bin" file contains binary data of Supplier structures.
 * The file should be opened in "rb" mode for reading.
 */
int readSupplier() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "supplier.bin", "rb");

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Supplier supplier;

  while (fread(&supplier, sizeof(struct Supplier), 1, fp) == 1) {
    if (strlen(supplier.supplierName) > 0) {
      printf("Supplier Name: %s, Contact Number: %s, Email: %s, Bussines Type: %s\n",
             supplier.supplierName,supplier.contactNumber,supplier.email,supplier.bussinesType);
    }
  }

  fclose(fp);
  return 1;
}

/**
 * @brief Deletes a supplier from the "supplier.bin" file based on the supplier name.
 *
 * This function opens the "supplier.bin" file in read-write mode and searches for a supplier
 * with the specified name. If the supplier is found, its data is overwritten with null data,
 * effectively deleting the supplier.
 *
 * @param supplierName The name of the supplier to be deleted.
 * @return Returns 1 on success, -1 on failure (file opening failure or supplier not found).
 *
 * @warning This function assumes that the "supplier.bin" file contains binary data of Supplier structures.
 * The file should be opened in "rb+" mode for both reading and writing.
 */
int deleteSupplier(const char *supplierName) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "supplier.bin", "rb+");;

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Supplier currentSupplier;

  long int currentPosition = ftell(fp);
  int supplierFound = 0;

  // Find and delete the user with the specified username
  while (fread(&currentSupplier, sizeof(struct Supplier), 1, fp) == 1) {
    if (strcmp(currentSupplier.supplierName, supplierName) == 0) {
      supplierFound = 1;
      break;
    }

    currentPosition = ftell(fp);
  }

  if (!supplierFound) {
    fclose(fp);
    printf("User with supplier name %s not found.\n", supplierName);
    return -1; // User not found
  }

  // Move the file pointer to the beginning of the user to be deleted
  fseek(fp, currentPosition, SEEK_SET);
  // Overwrite the user with null data
  struct Supplier nullSupplier = { 0 };
  fwrite(&nullSupplier, sizeof(struct Supplier), 1, fp);
  fclose(fp);
  return 1;
}

int setCursorPosition(int x, int y) {
  if (x < 1 || y < 1) {
    // Koordinatlar geçersizse hata kodu döndür
    return -1;
  }

  fprintf(stdout, "\033[%d;%dH", y, x);
  // Baþarý durumunda 0 döndür
  return 0;
}

int setTextColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  return 1;
}

int setBackgorundColor(int backgroundColor) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor << 4);
  return 1;
}




int mainMenu() {
  int selectedOption = 0;
  int x = 30;
  int y = 10;

  while (0 == 0) {
    displayMenu(*loginMenu, selectedOption, 6, x, y);
    char key = _getch();

    if (key == 72 && selectedOption >= 0) {
      if (selectedOption == 0) {
        selectedOption = 5;
      } else {
        selectedOption--;
      }
    } else if (key == 80 && selectedOption <= 5) {
      if (selectedOption == 5) {
        selectedOption = 0;
      } else {
        selectedOption++;
      }
    } else if (key == 13) {
      if (selectedOption == 0) {
        if (false) {
          //loginMenu()) {
          //materialManagementMenu();
        }
      } else if (selectedOption == 5) {
        break;
      } else if (selectedOption == 1) {
        //stockControlMenu();
      } else if (selectedOption == 2) {
        //warehouseOptimizationMenu();
      } else if (selectedOption == 3) {
        //reportingMenu();
      } else if (selectedOption == 4) {
        //integrationMenu();
      }
    }
  }

  return 1;
}

int displayMenu(const char *menuOptions, int selectedOption, int menuSize, int x, int y) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  system("cls");
  setCursorPosition(x + 15, y);

  for (int i = 0; i <= 43; i++) {
    printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  printf("Warehouse Management System Menu");
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
    printf("=");
  }

  for (int i = 0; i < menuSize; i++) {
    setCursorPosition(x + 22, y + 3 + i);

    if (i == selectedOption) {
      setTextColor(10); // 12 numaralý renk kodu kýrmýzý renktir
      printf("> %c <\n", menuOptions[i]);
    } else {
      setTextColor(15); // Varsayýlan renk (beyaz)
      printf(" %c\n", menuOptions[i]);
    }
  }

  setTextColor(15); // Varsayýlan rengine geri dön
  setCursorPosition(x + 15, y + menuSize + 3);

  for (int i = 0; i <= 43; i++) {
    printf("=");
  }

  return 1;
}
