#ifndef CARMAINTENANCE_H
#define CARMAINTENANCE_H


/**
 * @brief Represents a user in the system.
 */
struct User {
  char username[50]; /**< Username of the user. */
  int password; /**< Password of the user. */
  bool status; /**< Status of the user. */
};

/**
 * @brief Represents a project with detailed information.
 */
struct Project {
  char brand[30]; /**< Brand of the project. */
  int year; /**< Year of the project. */
  char action[100]; /**< Action or description of the project. */
  char driverName[50]; /**< Name of the driver associated with the project. */
  int driverPhone; /**< Phone number of the driver. */
  int kilometer; /**< Kilometer information of the project. */
  char date[20]; /**< Date information related to the project. */
  bool status; /**< Status of the project. */
};

/**
 * @brief Represents a task with details.
 */
struct Task {
  char brand[30]; /**<Car Name*/
  char driverName[50]; /**<Driver Name*/
  char description[100]; /**< Description of the task. */
  char assignee[50]; /**< Assignee of the task. */
  char date[20]; /**< Date information related to the task. */
  int status; /**< Status of the task. */
};

/**
 * @brief Represents a cost associated with a project.
 */
struct Cost {
  char brand[30]; /**< Brand associated with the cost. */
  char driverName[50]; /**< Driver name associated with the cost. */
  char date[20]; /**< Date information related to the cost. */
  char supplier[52]; /**< Supplier of the material or service. */
  char material[100]; /**< Material or service description. */
  float price; /**< Price of the material or service. */
};

/**
 * @brief Represents a supplier in the system.
 */
struct Supplier {
  char supplierName[50]; /**< Name of the supplier. */
  char contactNumber[10]; /**< Contact number of the supplier. */
  char email[30]; /**< Email address of the supplier. */
  char bussinesType[25]; /**< Business type of the supplier. */
};

/**
 * @brief Adds users to the system.
 *
 * This function adds the specified users to the system. If the system file does not exist,
 * it is created. Each added user is appended to the end of the file.
 *
 * @param users An array containing the users.
 * @param userNumber The number of users to add.
 * @return A value representing the success status. 0 indicates success, -1 indicates an error.
 *
 * @note The file name and user information should follow a specific structure.
 * @warning If there is an error opening the file, an error message is printed.
 */
int addUser(struct User users[],size_t userNumber);

/**
 * @brief Reads users from the system and prints their information.
 *
 * This function opens the system file and reads user information from it.
 * It prints the username, password, and status of each user to the console.
 *
 * @return A value representing the success status. 0 indicates success, 1 indicates an error.
 *
 * @note The system file should exist, and the user structure in the file should follow a specific format.
 * @warning If there is an error opening the file, an error message is printed.
 */
int readUser();

/**
 * @brief Deletes a user from the system.
 *
 * This function deletes the user with the specified username from the system file.
 *
 * @param username The username of the user to be deleted.
 * @return A value representing the success status. 0 indicates success, -1 indicates an error, 1 indicates user not found.
 *
 * @note The system file should exist, and the user structure in the file should follow a specific format.
 * @warning If there is an error opening the file or the specified user is not found, an error message is printed.
 */
int deletUser(const char *username);


int updateUser();// kalsin

/**
 * @brief Adds projects to the system.
 *
 * This function adds the specified projects to the system. If the system file does not exist,
 * it is created. Each added project is appended to the end of the file.
 *
 * @param project An array containing the projects.
 * @param projectNumber The number of projects to add.
 * @return A value representing the success status. 0 indicates success, -1 indicates an error.
 *
 * @note The file name and project information should follow a specific structure.
 * @warning If there is an error opening the file, an error message is printed.
 */
int addProject(struct Project project[],size_t projectNumber);

/**
 * @brief Reads projects from the system and prints their information.
 *
 * This function opens the system file and reads project information from it.
 * It prints the brand, year, action, driver name, driver phone, kilometer, date, status, and other details
 * of each project to the console.
 *
 * @return A value representing the success status. 1 indicates success, 0 indicates an error.
 *
 * @note The system file should exist, and the project structure in the file should follow a specific format.
 * @warning If there is an error opening the file, an error message is printed.
 */
int readProject();

/**
 * @brief Updates a project's information in the system.
 *
 * This function updates the information of the project with the specified driver name in the system file.
 *
 * @return A value representing the success status. 0 indicates success, -1 indicates an error.
 *
 * @note The system file should exist, and the project structure in the file should follow a specific format.
 * @warning If there is an error opening the file or the specified project is not found, an error message is printed.
 */
int deleteProject(const char *driverName);

/**
 * @brief Updates a project's information in the system.
 *
 * This function updates the information of the project with the specified driver name in the system file.
 *
 * @return A value representing the success status. 0 indicates success, -1 indicates an error.
 *
 * @note The system file should exist, and the project structure in the file should follow a specific format.
 * @warning If there is an error opening the file or the specified project is not found, an error message is printed.
 */
int updateProject();

int addTask(struct Task task[],size_t taskNumber);
int readTask();
int updateTaskStatus(struct Task task[], const char *driverName, int status);
#endif
