/**
 * @file CarMaintenance.h
 * @brief Declarations and definitions for the Car Maintenance application.
 */
#define _CRT_SECURE_NO_WARNINGS
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

#include <stdio.h>
#include <stdlib.h>
#include "CarMaintenance.h"
#include <string.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "MainMenu.h"


int updateProjectFlag = 0;
int updateSupplierFlag = 0;





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

const char *authenticatedOptions[] = {
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
  "          Daily Reports         ",
  "       Return to Main Menu      "
};

const char *supplierOptions[] = {
  "           Add Supplier         ",
  "          Edit Supplier         ",
  "         Delete Supplier        ",
  "         View Suppliers         ",
  "       Return to Main Menu      "
};

const char* guestOption[] = {
  "          View Project          ",
  "          View Tasks            ",
  "          View Expenses         ",
  "         View Suppliers         ",
  "      Return to Login Menu      "
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
int addUser() {
    FILE* fp;
    errno_t err = fopen_s(&fp, "login.bin", "ab");

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }

    struct User users;

    int x = 30;
    int y = 10;

    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    printf("           Add User            ");
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 22, y + 3);
    printf("Username:");
    setCursorPosition(x + 31, y + 3);
    scanf("%s", users.username);

    setCursorPosition(x + 22, y + 4);
    printf("Password:");
    setCursorPosition(x + 31, y + 4);
    scanf("%d", &users.password);  // Use %d to read an integer

    users.status = 0;

    fwrite(&users, sizeof(struct User), 1, fp);

    fclose(fp);
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
int addProject() {

      FILE *fp;
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      errno_t err = fopen_s(&fp, "project.bin", "ab");

      time_t currentTime = time(nullptr);
      struct tm* tmStruct = localtime(&currentTime);
      char date[40];  // Yeterli boyutta bir karakter dizisi seçin
      strftime(date, sizeof(date), "%Y-%m-%d %H:%M", tmStruct);

      if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
      }

      struct Project projects;

      int x = 30;
      int y = 5;


      system("cls");

      setCursorPosition(x + 15, y);
      for (int i = 0; i <= 43; i++) {
          printf("=");
      }

      setCursorPosition(x + 20, y + 1);
      if (updateProjectFlag == 0) { printf("        Create Project          "); }
      if (updateProjectFlag == 1) { printf("        Update Project          "); }
      setCursorPosition(x + 15, y + 2);                                                         

      for (int i = 0; i <= 43; i++) {
          printf("=");
      }



      setCursorPosition(x + 22, y + 3);
      printf("Car's Brand:");
      setCursorPosition(x + 34, y + 3);
      scanf(" %[^\n]", projects.brand);
      fflush(stdin);
      

      setCursorPosition(x + 22, y + 4);
      printf("Car's Model Year:");
      setCursorPosition(x + 40, y + 4);
      scanf("%d", &projects.year);  // Use %d to read an integer
      fflush(stdin);


      setCursorPosition(x + 22, y + 5);
      printf("What To Do:");
      setCursorPosition(x + 34, y + 5);
      scanf(" %[^\n]", projects.action);
      fflush(stdin);


      setCursorPosition(x + 22, y + 6);
      printf("Driver Name:");
      setCursorPosition(x + 35, y + 6);
      scanf(" %[^\n]", projects.driverName);
      fflush(stdin);


      setCursorPosition(x + 22, y + 7);
      printf("Driver Phone:");
      setCursorPosition(x + 36, y + 7);
      scanf("%s", projects.driverPhone);
      fflush(stdin);


      setCursorPosition(x + 22, y + 8);
      printf("Kilometer:");
      setCursorPosition(x + 33, y + 8);
      scanf("%d", &projects.kilometer);
      fflush(stdin);

      projects.status = 0;
      strcpy(projects.date1, date);
      

      fwrite(&projects, sizeof(struct Project), 1, fp);

      setCursorPosition(x + 25, y + 9);
      SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
      if(updateProjectFlag==0){printf("Project Added Successfully");}
      if (updateProjectFlag == 1) { printf("Project Updated Successfully"); }
      Sleep(2000);
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
      

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
int deleteProject() {
    FILE* fp;
    errno_t err = fopen_s(&fp, "project.bin", "rb+");;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }



    int x = 30;
    int y = 5;


    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    if (updateProjectFlag == 0) { printf("        Delete Project          "); }
    if (updateProjectFlag == 1) { printf("        Update Project          "); }
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }
    char driverName[30];
    setCursorPosition(x + 22, y + 3);
    printf("Driver's Name:");
    setCursorPosition(x + 37, y + 3);
    scanf(" %[^\n]", driverName);
    fflush(stdin);

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
    setCursorPosition(x + 27, y + 10);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    if(updateProjectFlag==0){printf("Project Deleted Successfully");}
    if (updateProjectFlag == 1) { printf("Project Updated Successfully"); }
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
  Sleep(2000);
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
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  if (err != 0) {
      printf("Exception While File Opening: %d\n", err);
      return -1;
  }

  struct Project project;

  int x = 30;
  int y = 5;


  system("cls");

  setCursorPosition(x + 15, y);
  for (int i = 0; i <= 43; i++) {
      printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  printf("         View Project           ");
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
      printf("=");
  }
  char driverName[30];
  setCursorPosition(x + 22, y + 3);
  printf("Driver's Name:");
  setCursorPosition(x + 37, y + 3);
  scanf(" %[^\n]", driverName);
  fflush(stdin);

  while (fread(&project, sizeof(struct Project), 1, fp) == 1) {
      

      if (strcmp(driverName, project.driverName)==0 && project.year>0) {


              system("cls");

              setCursorPosition(x + 15, y);
              for (int i = 0; i <= 43; i++) {
                  printf("=");
              }

              setCursorPosition(x + 20, y + 1);
              printf("         View Project           ");
              setCursorPosition(x + 15, y + 2);

              for (int i = 0; i <= 43; i++) {
                  printf("=");
              }

              setCursorPosition(x + 22, y + 3);
              printf("Driver Name: %s", project.driverName);
              setCursorPosition(x + 22, y + 4);
              printf("Driver Phone: %s", project.driverPhone);
              setCursorPosition(x + 22, y + 5);
              printf("Car's Brand: %s", project.brand);
              setCursorPosition(x + 22, y + 6);
              printf("Model Year: %d", project.year);
              setCursorPosition(x + 22, y + 7);
              printf("What To Do: %s", project.action);
              setCursorPosition(x + 22, y + 8);
              printf("Car's Kilometer: %d", project.kilometer);
              setCursorPosition(x + 22, y + 9);
              printf("Date Added: %s", project.date1);

              int status = project.status;
              if (status == 0) {
                  setCursorPosition(x + 25, y + 10);
                  SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                  printf("Waiting For Repair");
              }
              if (status == 1) {
                  setCursorPosition(x + 27, y + 10);
                  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                  printf("Repairing...");
              }
              if (status == 2) {
                  setCursorPosition(x + 27, y + 10);
                  SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                  printf("Finished!");
              }
              
              strcpy(driverName, "");
              SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
              _getch();
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
int addTask() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "ab");;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  time_t currentTime = time(nullptr);
  struct tm* tmStruct = localtime(&currentTime);
  char date[40];  // Yeterli boyutta bir karakter dizisi seçin
  strftime(date, sizeof(date), "%Y-%m-%d %H:%M", tmStruct);

  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }


  struct Task tasks;

  int x = 30;
  int y = 5;


  system("cls");

  setCursorPosition(x + 15, y);
  for (int i = 0; i <= 43; i++) {
      printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  printf("           Add Task             ");
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
      printf("=");
  }



  setCursorPosition(x + 22, y + 3);
  printf("Asssignee:");
  setCursorPosition(x + 32, y + 3);
  scanf(" %[^\n]", tasks.assignee);
  fflush(stdin);


  setCursorPosition(x + 22, y + 4);
  printf("Car's Brand:");
  setCursorPosition(x + 34, y + 4);
  scanf("%s", tasks.brand);  // Use %d to read an integer
  fflush(stdin);


  setCursorPosition(x + 22, y + 5);
  printf("Driver Name:");
  setCursorPosition(x + 34, y + 5);
  scanf(" %[^\n]", tasks.driverName);
  fflush(stdin);

  if (readTaskControl(tasks.driverName) == -1) { setCursorPosition(x + 27, y + 6); printf("Driver Not Found"); Sleep(3000); return 0; }

  setCursorPosition(x + 22, y + 6);
  printf("Task's Description:");
  setCursorPosition(x + 42, y + 6);
  scanf(" %[^\n]", tasks.description);
  fflush(stdin);

  tasks.status = 1;
  strcpy(tasks.date1, date);


  fwrite(&tasks, sizeof(struct Task), 1, fp);

  setCursorPosition(x + 25, y + 9);
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
  printf("Task Added Successfully");
  Sleep(2000);
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

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
int updateTaskStatus() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "rb+");
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  if (err != 0) {
      printf("Exception While File Opening: %d\n", err);
      return -1;
  }

  int x = 30;
  int y = 5;


  system("cls");

  setCursorPosition(x + 15, y);
  for (int i = 0; i <= 43; i++) {
      printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  printf("      Update Task Status        ");
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
      printf("=");
  }
  char driverName[30];
  setCursorPosition(x + 22, y + 3);
  printf("Driver's Name:");
  setCursorPosition(x + 37, y + 3);
  scanf(" %[^\n]", driverName);
  fflush(stdin);
  

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


  system("cls");

  setCursorPosition(x + 15, y);
  for (int i = 0; i <= 43; i++) {
      printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  printf("      Update Task Status        ");
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
      printf("=");
  }
  int statusNew;

  do {
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
      setCursorPosition(x + 22, y + 3);
      printf("Press 0 For Waiting For Repair Status");

      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
      setCursorPosition(x + 22, y + 4);
      printf("Press 1 For Repairing Status");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
      SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
      setCursorPosition(x + 22, y + 5);
      printf("Press 2 For Finished Status");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
      int keyPressed = _getch(); 
      if (keyPressed == '0') {
          statusNew = 0;
      }
      else if (keyPressed == '1') {
          statusNew = 1;
      }
      else if (keyPressed == '2') {
          statusNew = 2;
      }

  } while (statusNew == -1); // Kullanıcı geçerli bir seçenek yapana kadar döngü devam eder

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
    FILE* fp;
    errno_t err = fopen_s(&fp, "task.bin", "rb+");;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }

    struct Task task;

    int x = 30;
    int y = 5;


    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    printf("           View Task            ");
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }
    char driverName[30];
    setCursorPosition(x + 22, y + 3);
    printf("Driver's Name:");
    setCursorPosition(x + 37, y + 3);
    scanf(" %[^\n]", driverName);
    fflush(stdin);

    while (fread(&task, sizeof(struct Task), 1, fp) == 1) {


        if (strcmp(driverName, task.driverName) == 0) {


            system("cls");

            setCursorPosition(x + 15, y);
            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 20, y + 1);
            printf("           View Task            ");
            setCursorPosition(x + 15, y + 2);

            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 22, y + 3);
            printf("Assignee: %s", task.assignee);
            setCursorPosition(x + 22, y + 4);
            printf("Driver Name: %s", task.driverName);
            setCursorPosition(x + 22, y + 5);
            printf("Car's Brand: %s", task.brand);
            setCursorPosition(x + 22, y + 6);
            printf("Task Description: %s", task.description);
            setCursorPosition(x + 22, y + 7);
            printf("Date Added: %s", task.date1);

            int status = task.status;
            if (status == 0) {
                setCursorPosition(x + 25, y + 8);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("Waiting For Repair");
            }
            if (status == 1) {
                setCursorPosition(x + 27, y + 8);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                printf("Repairing...");
            }
            if (status == 2) {
                setCursorPosition(x + 27, y + 8);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("Finished!");
            }

            strcpy(driverName, "");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            _getch();
        }
    }



    fclose(fp);
    return 1;



}
int readTaskControl(const char *driverName) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "project.bin", "rb");

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Project project;

  while (fread(&project, sizeof(struct Project), 1, fp) == 1) {
    if (strcmp(driverName,project.driverName)==0) {
        return 1;
    }
  }

  fclose(fp);
  return -1;
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



int addCost() {
    FILE* fp;
    errno_t err = fopen_s(&fp, "cost.bin", "ab");;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    time_t currentTime = time(nullptr);
    struct tm* tmStruct = localtime(&currentTime);
    char date[40];  // Yeterli boyutta bir karakter dizisi seçin
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M", tmStruct);

    if (err != 0) {
        // Hata durumunda
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }


    struct Cost cost;

    int x = 30;
    int y = 5;


    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    printf("           Add Cost             ");
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }



    setCursorPosition(x + 22, y + 3);
    printf("Driver Name:");
    setCursorPosition(x + 36, y + 3);
    scanf(" %[^\n]",cost.driverName);
    fflush(stdin);

    if (readTaskControl(cost.driverName) == -1) { setCursorPosition(x + 27, y + 6); printf("Driver Not Found"); Sleep(3000); return 0; }

    setCursorPosition(x + 22, y + 4);
    printf("Car's Brand:");
    setCursorPosition(x + 35, y + 4);
    scanf("%s", cost.brand);  // Use %d to read an integer
    fflush(stdin);


    setCursorPosition(x + 22, y + 5);
    printf("Material:");
    setCursorPosition(x + 33, y + 5);
    scanf(" %[^\n]", cost.material);
    fflush(stdin);

    

    setCursorPosition(x + 22, y + 6);
    printf("Supplier:");
    setCursorPosition(x + 33, y + 6);
    scanf(" %[^\n]", cost.supplier);
    fflush(stdin);

    setCursorPosition(x + 22, y +7);
    printf("Price:");
    setCursorPosition(x + 33, y +7);
    scanf("%d", &cost.price);
    


    
    strcpy(cost.date1, date);


    fwrite(&cost, sizeof(struct Cost), 1, fp);

    setCursorPosition(x + 25, y + 9);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("Cost Added Successfully");
    Sleep(2000);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

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
    FILE* fp;
    errno_t err = fopen_s(&fp, "cost.bin", "rb+");;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }

    struct Cost cost;

    int x = 30;
    int y = 5;


    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    printf("        View Cost         ");
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }
    char driverName[30];
    setCursorPosition(x + 22, y + 3);
    printf("Driver's Name:");
    setCursorPosition(x + 37, y + 3);
    scanf(" %[^\n]", driverName);
    fflush(stdin);

    while (fread(&cost, sizeof(struct Cost), 1, fp) == 1) {


        if (strcmp(driverName, cost.driverName) == 0) {


            system("cls");

            setCursorPosition(x + 15, y);
            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 20, y + 1);
            printf("          View Cost             ");
            setCursorPosition(x + 15, y + 2);

            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 22, y + 3);
            printf("Driver Name: %s", cost.driverName);
            setCursorPosition(x + 22, y + 4);
            printf("Car's Brand: %s", cost.brand);
            setCursorPosition(x + 22, y + 5);
            printf("Material: %s", cost.material);
            setCursorPosition(x + 22, y + 6);
            printf("Supplier: %s", cost.supplier);
            setCursorPosition(x + 22, y + 7);
            printf("Price: %d", cost.price);
            setCursorPosition(x + 22, y + 8);
            printf("Date Added: %s", cost.date1);

            strcpy(driverName, "");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            _getch();
        }
    }



    fclose(fp);
    return 1;
}

int costReports() {

    FILE* fp;
    errno_t err = fopen_s(&fp, "cost.bin", "rb+");
    

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }

    struct Cost cost;

    int x = 30;
    int y = 5;

    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    printf("        View Cost         ");
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    time_t currentTime = time(nullptr);
    struct tm* tmStruct = localtime(&currentTime);

    char currentDate[11];
    char newDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", tmStruct);

    rewind(fp);
    while (fread(&cost, sizeof(struct Cost), 1, fp) == 1) {

        strftime(newDate, sizeof(newDate), "%Y-%m-%d", tmStruct);
        if (strcmp(currentDate, newDate) == 0) {
            system("cls");

            setCursorPosition(x + 15, y);
            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 20, y + 1);
            printf("          View Cost             ");
            setCursorPosition(x + 15, y + 2);

            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 22, y + 3);
            printf("Driver Name: %s", cost.driverName);
            setCursorPosition(x + 22, y + 4);
            printf("Car's Brand: %s", cost.brand);
            setCursorPosition(x + 22, y + 5);
            printf("Material: %s", cost.material);
            setCursorPosition(x + 22, y + 6);
            printf("Supplier: %s", cost.supplier);
            setCursorPosition(x + 22, y + 7);
            printf("Price: %d", cost.price);
            setCursorPosition(x + 22, y + 8);
            printf("Date Added: %s", cost.date1);

            
            
            _getch();
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
int addSupplier() {
    FILE* fp;
    errno_t err = fopen_s(&fp, "supplier.bin", "ab");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }

    struct Supplier supplier;

    int x = 30;
    int y = 10;

    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    if (updateSupplierFlag == 0) { printf("          Add Supplier          "); }
    if (updateSupplierFlag == 1) { printf("        Update Supplier         "); }
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 22, y + 3);
    printf("Supplier Name:");
    setCursorPosition(x + 38, y + 3);
    scanf(" %[^\n]", supplier.supplierName);

    setCursorPosition(x + 22, y + 4);
    printf("Contact Number:");
    setCursorPosition(x + 39, y + 4);
    scanf(" %[^\n]", supplier.contactNumber); 

    setCursorPosition(x + 22, y + 5);
    printf("Bussines Type:");
    setCursorPosition(x + 38, y + 5);
    scanf(" %[^\n]", supplier.bussinesType);

    setCursorPosition(x + 22, y + 6);
    printf("Email:");
    setCursorPosition(x + 30, y + 6);
    scanf(" %[^\n]", supplier.email);


    fwrite(&supplier, sizeof(struct Supplier), 1, fp);
    setCursorPosition(x + 25, y + 7);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    if (updateSupplierFlag == 0) { printf("Supplier Added Successfully"); }
    if (updateSupplierFlag == 1) { printf("Supplier Updated Successfully"); }
    Sleep(2000);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

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
    FILE* fp;
    errno_t err = fopen_s(&fp, "supplier.bin", "rb+");;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (err != 0) {
        printf("Exception While File Opening: %d\n", err);
        return -1;
    }

    struct Supplier supplier;

    int x = 30;
    int y = 5;


    system("cls");

    setCursorPosition(x + 15, y);
    for (int i = 0; i <= 43; i++) {
        printf("=");
    }

    setCursorPosition(x + 20, y + 1);
    printf("         View Supplier          ");
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
        printf("=");
    }
    char supplierName[30];
    setCursorPosition(x + 22, y + 3);
    printf("Supplier's Name:");
    setCursorPosition(x + 40, y + 3);
    scanf(" %[^\n]", supplierName);
    fflush(stdin);

    int supplierFound = 0;
    while (fread(&supplier, sizeof(struct Supplier), 1, fp) == 1) {


        if (strcmp(supplierName, supplier.supplierName) == 0) {


            system("cls");

            setCursorPosition(x + 15, y);
            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 20, y + 1);
            printf("         View Supplier          ");
            setCursorPosition(x + 15, y + 2);

            for (int i = 0; i <= 43; i++) {
                printf("=");
            }

            setCursorPosition(x + 22, y + 3);
            printf("Supplier Name: %s", supplier.supplierName);
            setCursorPosition(x + 22, y + 4);
            printf("Supplier Phone: %s", supplier.contactNumber);
            setCursorPosition(x + 22, y + 5);
            printf("Bussines Type: %s", supplier.bussinesType);
            setCursorPosition(x + 22, y + 6);
            printf("Email: %s", supplier.email);
            supplierFound = 1;
            _getch();
        }
    }
    if (supplierFound == 0) { 
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED); 
        setCursorPosition(x + 27, y + 4);
        printf("Supplier Not Found"); 
        Sleep(2000);SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        supplierFound = 0;
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
int deleteSupplier() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "supplier.bin", "rb+");
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


  if (err != 0) {
    // Hata durumunda
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }
  int x = 30;
  int y = 5;


  system("cls");

  setCursorPosition(x + 15, y);
  for (int i = 0; i <= 43; i++) {
      printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  if (updateSupplierFlag == 0) { printf("        Delete Supplier         "); }
  if (updateSupplierFlag == 1) { printf("        Update Supplier         "); }
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
      printf("=");
  }
  char supplierName[30];
  setCursorPosition(x + 22, y + 3);
  printf("Supplier's Name:");
  setCursorPosition(x + 39, y + 3);
  scanf(" %[^\n]", supplierName);
  fflush(stdin);

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
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    setCursorPosition(x + 22, y + 6);
    printf("User with supplier name %s not found.\n", supplierName);
    Sleep(2000); 
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    return -1; // User not found
  }

  // Move the file pointer to the beginning of the user to be deleted
  fseek(fp, currentPosition, SEEK_SET);
  // Overwrite the user with null data
  struct Supplier nullSupplier = { 0 };
  fwrite(&nullSupplier, sizeof(struct Supplier), 1, fp);
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
  setCursorPosition(x + 22, y + 6);
  if (updateSupplierFlag == 0) { printf("Supplier Deleted Successfully"); }
  if (updateSupplierFlag == 1) { printf("Supplier Updated Successfully"); }
  Sleep(2000);
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
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


int guestMode = 0;


int mainMenu() {
  int selectedOption = 0;
  int x = 30;
  int y = 10;

  while (0 == 0) {
    displayMenu(loginMenu, selectedOption, 3, x, y);
    char key = _getch();

    if (key == 72 && selectedOption >= 0) {
      if (selectedOption == 0) {
        selectedOption = 2;
      } else {
        selectedOption--;
      }
    } else if (key == 80 && selectedOption <= 2) {
      if (selectedOption == 2) {
        selectedOption = 0;
      } else {
        selectedOption++;
      }
    } else if (key == 13) {
      if (selectedOption == 0) {
          if (login()) {
              authenticatedMenu();
          }

        
      
      } else if (selectedOption == 1) {
          if (addUser()) {
              printf("User Added Succesfully");
              continue;
          }
      } else if (selectedOption == 2) {
          guestMode = 1;
          guestMenu();
      }     
    }
  }

  return 1;
}


int authenticatedMenu()
{
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
        displayMenu(authenticatedOptions, selectedOption, 6, x, y);
        char key = _getch();

        if (key == 72 && selectedOption >= 0) {
            if (selectedOption == 0) {
                selectedOption = 5;
            }
            else {
                selectedOption--;
            }
        }
        else if (key == 80 && selectedOption <= 5) {
            if (selectedOption == 5) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        else if (key == 13) {
            if (selectedOption == 0) {
                projectMenu();
            }
            else if (selectedOption == 1) {
                taskMenu();
            }
            else if (selectedOption == 2) {
                costMenu();
            }
            else if (selectedOption == 3) {
                supplierMenu();
            }
            else if (selectedOption == 4) {
                setBackgorundColor(5);
            }
            else if (selectedOption == 5) {
                break;
            }
        }
    }

    return 1;
}

int guestMenu()
{
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
        displayMenu(guestOption, selectedOption, 5, x, y);
        char key = _getch();

        if (key == 72 && selectedOption >= 0) {
            if (selectedOption == 0) {
                selectedOption = 4;
            }
            else {
                selectedOption--;
            }
        }
        else if (key == 80 && selectedOption <= 4) {
            if (selectedOption == 4) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        else if (key == 13) {
            if (selectedOption == 0) {
                readProject();
            }
            else if (selectedOption == 1) {
                readTask();
            }
            else if (selectedOption == 2) {
                readCost();
            }
            else if (selectedOption == 3) {
                readSupplier();
            }
            else if (selectedOption == 4) {
                break;
            }
        }
    }

    return 1;


}

int projectMenu()
{
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
        displayMenu(projectOptions, selectedOption, 5, x, y);
        char key = _getch();

        if (key == 72 && selectedOption >= 0) {
            if (selectedOption == 0) {
                selectedOption = 4;
            }
            else {
                selectedOption--;
            }
        }
        else if (key == 80 && selectedOption <= 4) {
            if (selectedOption == 4) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        else if (key == 13) {
            if (selectedOption == 0) {
                addProject();
            }
            else if (selectedOption == 1) {
                readProject();
            }
            else if (selectedOption == 2) {
                updateProjectFlag=1;
                deleteProject();
                addProject();
                updateProjectFlag = 0;
            }
            else if (selectedOption == 3) {
                deleteProject();
            }
            else if (selectedOption == 4) {
                break;
            }
        }
    }

    return 1;
}



int taskMenu()
{
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
        displayMenu(taskOptions, selectedOption, 4, x, y);
        char key = _getch();

        if (key == 72 && selectedOption >= 0) {
            if (selectedOption == 0) {
                selectedOption = 3;
            }
            else {
                selectedOption--;
            }
        }
        else if (key == 80 && selectedOption <= 3) {
            if (selectedOption == 3) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        else if (key == 13) {
            if (selectedOption == 0) {
                addTask();
            }
            else if (selectedOption == 1) {
                readTask();
            }
            else if (selectedOption == 2) {
                updateTaskStatus();
            }
            else if (selectedOption == 3) {
                break;
            }
        }
    }

    return 1;
}


int costMenu()
{
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
        displayMenu(costOptions, selectedOption, 4, x, y);
        char key = _getch();

        if (key == 72 && selectedOption >= 0) {
            if (selectedOption == 0) {
                selectedOption = 3;
            }
            else {
                selectedOption--;
            }
        }
        else if (key == 80 && selectedOption <= 3) {
            if (selectedOption == 3) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        else if (key == 13) {
            if (selectedOption == 0) {
                addCost();
            }
            else if (selectedOption == 1) {
                readCost();
            }
            else if (selectedOption == 2) {
                costReports();
            }
            else if (selectedOption == 3) {
                break;
            }
        }
    }

    return 1;
}

int supplierMenu()
{
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
        displayMenu(supplierOptions, selectedOption, 5, x, y);
        char key = _getch();

        if (key == 72 && selectedOption >= 0) {
            if (selectedOption == 0) {
                selectedOption = 4;
            }
            else {
                selectedOption--;
            }
        }
        else if (key == 80 && selectedOption <= 4) {
            if (selectedOption == 4) {
                selectedOption = 0;
            }
            else {
                selectedOption++;
            }
        }
        else if (key == 13) {
            if (selectedOption == 0) {
                addSupplier();
            }
            else if (selectedOption == 1) {
                updateSupplierFlag = 1;
                deleteSupplier();
                addSupplier();
                updateSupplierFlag = 0;
            }
            else if (selectedOption == 2) {
                deleteSupplier();
            }
            else if (selectedOption == 3) {
                readSupplier();
            }
            else if (selectedOption == 4) {
                break;
            }
        }
    }

    return 1;
}





int displayMenu(const char **menuOptions, int selectedOption, int menuSize, int x, int y) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  system("cls");
  setCursorPosition(x + 15, y);

  for (int i = 0; i <= 43; i++) {
    printf("=");
  }

  setCursorPosition(x + 20, y + 1);
  printf("     Car Maintenance System     ");
  setCursorPosition(x + 15, y + 2);

  for (int i = 0; i <= 43; i++) {
    printf("=");
  }

  for (int i = 0; i < menuSize; i++) {
    setCursorPosition(x + 22, y + 3 + i);

    if (i == selectedOption) {
      setTextColor(10); // 12 numaralý renk kodu kýrmýzý renktir
      printf("> %s <\n", menuOptions[i]);
    } else {
      setTextColor(15); // Varsayýlan renk (beyaz)
      printf(" %s\n", menuOptions[i]);
    }
  }

  setTextColor(15); // Varsayýlan rengine geri dön
  setCursorPosition(x + 15, y + menuSize + 3);

  for (int i = 0; i <= 43; i++) {
    printf("=");
  }

  return 1;
}




int login() 
{
    char enteredUsername[30];
    int enteredPassword;
    setTextColor(15);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    

    int loginAttempts = 0;
    const int maxLoginAttempts = 3;
    setCursorPosition(x + 20, y + 7);
    printf("%.*s\n", 29, "=============================");
    setCursorPosition(x + 20, y + 8);
    printf("=%.*s=\n", 27, "                           ");
    setCursorPosition(x + 20, y + 9);
    printf("%.*s\n", 29, "=============================");
    setCursorPosition(x + 20, y + 10);
    printf("=%.*s=\n", 27, "                           ");
    setCursorPosition(x + 20, y + 11);
    printf("=%.*s=\n", 27, "                           ");
    setCursorPosition(x + 20, y + 12);
    printf("%.*s\n", 29, "=============================");

    while (loginAttempts < maxLoginAttempts) {

        setCursorPosition(x + 26, y + 8);
        printf(" -- LOGIN PAGE -- ");
        setCursorPosition(x + 21, y + 10);
        printf(" User name: ");
        scanf("%s", enteredUsername);
        int userPassword = authenticateUser(enteredUsername);
        if(userPassword==0){
            setCursorPosition(x + 20, y + 13);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("         User Not Found         \n");
            Sleep(1000);
            break;
        }
        setCursorPosition(x + 21, y + 11);
        printf(" Password: ");
        enteredPassword = getPassword(); // getPassword iþlevini çağır

        

        if (userPassword==enteredPassword) {
            setCursorPosition(x + 20, y + 13);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("             Access             \n");
            Sleep(1000);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            return 1; // Successful login
        }
        else {
            loginAttempts++;
            setCursorPosition(x + 20, y + 13);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("Not Access (%d/%d attempts)\n", loginAttempts, maxLoginAttempts);
            Sleep(750);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

            if (loginAttempts < maxLoginAttempts) {
                setCursorPosition(x + 20, y + 7);
                printf("%.*s\n", 29, "=============================");
                setCursorPosition(x + 20, y + 8);
                printf("=%.*s=\n", 27, "                           ");
                setCursorPosition(x + 20, y + 9);
                printf("%.*s\n", 29, "=============================");
                setCursorPosition(x + 20, y + 10);
                printf("=%.*s=\n", 27, "                           ");
                setCursorPosition(x + 20, y + 11);
                printf("=%.*s=\n", 27, "                           ");
                setCursorPosition(x + 20, y + 12);
                printf("%.*s\n", 29, "=============================");
            }
            else {
                setCursorPosition(x + 20, y + 15);
                printf("Max login attempts reached. Exiting...\n");
                Sleep(1500);
                exit(0);
            }
        }
    }

    return false;
}






int getPassword() {
    char ch;
    int index = 0;
    char password[30];

    while (1) {
        ch = _getch();

        if (ch == 13) {
            break;
        }

        password[index++] = ch;

        if (index == 30 - 1) {
            // Parola uzunluğu 30 karakteri geçerse çık
            break;
        }

        printf("*");
    }

    printf("\n");

    password[index] = '\0';

    
    int result = atoi(password);

    return result;
}



int authenticateUser(const char* enteredUsername) {
    // Open the file for reading binary data
    FILE* fp = fopen("login.bin", "rb");

    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    struct User user;

    while (fread(&user, sizeof(struct User), 1, fp) == 1) {
        if (strcmp(enteredUsername, user.username) == 0){
            fclose(fp);
            return user.password; // Return user status (0 or 1)
        }
    }

    fclose(fp);
    return 0; // Authentication failed
}











