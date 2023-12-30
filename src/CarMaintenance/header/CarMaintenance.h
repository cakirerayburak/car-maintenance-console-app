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
  char description[100]; /**< Description of the task. */
  char assignee[50]; /**< Assignee of the task. */
  char date[20]; /**< Date information related to the task. */
  bool status; /**< Status of the task. */
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

int addUser(struct User users[],size_t userNumber);
int readUser();
int deletUser(const char *username);
int updateUser();
int addProject(struct Project project[]);
int deleteProject();
int updateProject();
int addTask();
int deleteTask();
int updateTaskStatus();
#endif
