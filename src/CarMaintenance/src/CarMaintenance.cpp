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
  FILE *fp = fopen("login.bin", "ab+");

  if (fp == NULL) {
    perror("File Open Error");
    return -1;
  }

  for(size_t i = 0; i < userNumber; ++i) {
    fwrite(&users[i], sizeof(struct User), 1, fp);
  }

  fclose(fp);
  //fwrite(users, sizeof(struct User), 1, fp);
  //fclose(fp);
  return 0;
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
  FILE *fp = fopen("login.bin", "rb");

  if (fp == NULL) {
    perror("Exception While File Opening");
    return 1;
  }

  struct User users;

  while (fread(&users, sizeof(struct User), 1, fp) == 1) {
    if(users.password!=0) {
      printf("Username: %s, Passsword: %d, Status: %d\n", users.username,users.password,users.status);
    }
  }

  fclose(fp);
  return 0;
}

/**
 * @brief Deletes a user from the file.
 *
 * This function deletes the user with the specified username from the "login.bin" file.
 *
 * @param username The username of the user to be deleted.
 * @return A value representing the success status. 0 indicates success, -1 indicates an error, 1 indicates user not found.
 *
 * @note The file "login.bin" should exist, and the user structure in the file should follow a specific format.
 * @warning If there is an error opening the file or the specified user is not found, an error message is printed.
 */

int deletUser(const char *username) {
  FILE *fp = fopen("login.bin", "rb+");

  if (fp == NULL) {
    perror("Exception While File Opening");
    return -1; // File opening error
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
    return 1; // User not found
  }

  // Move the file pointer to the beginning of the user to be deleted
  fseek(fp, currentPosition, SEEK_SET);
  // Overwrite the user with null data
  struct User nullUser = { 0 };
  fwrite(&nullUser, sizeof(struct User), 1, fp);
  fclose(fp);
  return 0;
}

int updateUser() {
  return 0;
}

int addProject(Project project[]) {
  return 0;
}

int deleteProject() {
  return 0;
}

int updateProject() {
  return 0;
}

int addTask() {
  return 0;
}

int deleteTask() {
  return 0;
}

int updateTaskStatus() {
  return 0;
}
