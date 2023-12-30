#include <stdio.h>
#include <stdlib.h>
#include "CarMaintenance.h"
#include <string.h>

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
int deletUser(const char *username) {
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
  errno_t err = fopen_s(&fp, "project.bin", "rb");;

  if (err != 0) {
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
    printf("User with Driver Name: %s not found.\n", driverName);
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
             project.kilometer, project.date,project.status);
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

int updateTaskStatus(Task task[],const char *driverName,int status) {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "rb");;

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Task currentTask;

  long int currentPosition = ftell(fp);
  int taskFound = 0;

  // Find and delete the user with the specified username
  while (fread(&currentTask, sizeof(struct Task), 1, fp) == 1) {
    if (strcmp(currentTask.driverName, driverName) == 0) {
      taskFound = 1;
      break;
    }

    currentPosition = ftell(fp);
  }

  if (!taskFound) {
    fclose(fp);
    printf("User with Driver Name: %s not found.\n", driverName);
    return -1; // User not found
  }

  struct Task tempTask[] = {
    {*currentTask.brand, *currentTask.driverName, *currentTask.description, *currentTask.assignee, *currentTask.date, status}
  };

  // Move the file pointer to the beginning of the user to be deleted
  fseek(fp, currentPosition, SEEK_SET);

  // Overwrite the user with null data
  struct Project nullProject = { 0 };

  fwrite(&nullProject, sizeof(struct Project), 1, fp);

  fclose(fp);

  addTask(tempTask, 1);

  return 1;
}
int readTask() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "task.bin", "rb");;

  if (err != 0) {
    printf("Exception While File Opening: %d\n", err);
    return -1;
  }

  struct Task task;

  while (fread(&task, sizeof(struct Task), 1, fp) == 1) {
    if (task.driverName != "") {
      printf("Brand: %s, Driver Name: %s, Description: %s, Assigne %s, Date: %s,Status: %d\n",task.brand,task.driverName,task.description,task.assignee,task.date,task.status);
    }
  }

  fclose(fp);
  return 1;
}
