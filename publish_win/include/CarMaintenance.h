/**
 * @file CarMaintenance.h
 * @brief Header file for Car Maintenance application.
 *
 * This file contains the declarations for functions and data structures
 * used in the Car Maintenance application.
 */

#ifndef CAR_MAINTENANCE_H
#define CAR_MAINTENANCE_H

/**
 * @struct Task
 * @brief Represents a task in the Car Maintenance application.
 */

/**
 * @brief Represents a user in the system.
 */
struct User {
  char username[50]; /**< Username of the user. */
  int password; /**< Password of the user. */
  int status; /**< Status of the user. */
};

/**
 * @brief Represents a project with detailed information.
 */
struct Project {
  char brand[30]; /**< Brand of the project. */
  int year; /**< Year of the project. */
  char action[100]; /**< Action or description of the project. */
  char driverName[50]; /**< Name of the driver associated with the project. */
  char driverPhone[15]; /**< Phone number of the driver. */
  int kilometer; /**< Kilometer information of the project. */
  int status; /**< Status of the project. */
  char date1[40]; /**< Date information related to the project. */
};

/**
 * @brief Represents a task with details.
 */
struct Task {
  char brand[30]; /**<Car Name*/
  char driverName[50]; /**<Driver Name*/
  char description[100]; /**< Description of the task. */
  char assignee[50]; /**< Assignee of the task. */
  int status; /**< Status of the task. */
  char date1[40]; /**< Date information related to the task. */

};

/**
 * @struct Cost
 * @brief Represents a cost in the Car Maintenance application.
 */
struct Cost {
  char brand[30]; /**< Brand associated with the cost. */
  char driverName[50]; /**< Driver name associated with the cost. */
  char date1[40]; /**< Date information related to the cost. */
  char supplier[50]; /**< Supplier of the material or service. */
  int price; /**< Price of the material or service. */
  char material[100]; /**< Material or service description. */

};

/**
 * @brief Represents a supplier in the system.
 */
struct Supplier {
  char supplierName[50]; /**< Name of the supplier. */
  char contactNumber[15]; /**< Contact number of the supplier. */
  char email[50]; /**< Email address of the supplier. */
  char bussinesType[50]; /**< Business type of the supplier. */
};

struct DoubleHash {
    DoubleHash(int size);
    int insert(const char* key, const Project& project);
    int search(const char* key, Project& project);

private:
    int hash1(const char* key);
    int hash2(const char* key);
    int getNextIndex(int index, int attempt);

    int size;
    Project* projects;
    bool* isOccupied;
};
struct BPlusNode {
    int count;
    int isLeaf;
    struct Supplier data[4];
    struct BPlusNode* children[5];
};

struct BPlusTree {
    struct BPlusNode* root;
};

struct BPlusTree* createBPlusTree();
struct BPlusNode* createNode();
int insertSupplier(struct BPlusTree* bPlusTree, const struct Supplier* supplier);
int insertNonFull(struct BPlusNode* node, const struct Supplier* supplier);
void splitChild(struct BPlusNode* parentNode, int index);

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
int addUser();

int kmpSearch(const char* pat, const char* txt);

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
int readUser(const char* username, int password);

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
int deleteUser(const char *username);


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
int addProject();

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
int deleteProject();

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

/**
 * @brief Adds a task to the task array.
 *
 * This function adds a task to the provided task array.
 *
 * @param task An array of Task structures.
 * @param taskNumber The number of tasks in the array.
 * @return Returns 0 on success, -1 on failure.
 */
int addTask();

/**
 * @brief Reads a task.
 *
 * This function reads a task.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int readTask();
int readTaskControl(const char *driverName);

/**
 * @brief Updates the status of a task based on the driver's name.
 *
 * This function updates the status of a task in the provided task array
 * based on the driver's name.
 *
 * @param task An array of Task structures.
 * @param driverName The name of the driver.
 * @param statusNew The new status to be set.
 * @return Returns 0 on success, -1 on failure.
 */
int updateTaskStatus(struct Task task[], const char *driverName, int statusNew);

/**
 * @brief Adds a cost to the cost array.
 *
 * This function adds a cost to the provided cost array.
 *
 * @param cost An array of Cost structures.
 * @param costNumber The number of costs in the array.
 * @return Returns 0 on success, -1 on failure.
 */
int addCost();

/**
 * @brief Reads a cost.
 *
 * This function reads a cost.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int readCost();

/**
 * @brief Adds a supplier to the supplier array.
 *
 * This function adds a supplier to the provided supplier array.
 *
 * @param supplier An array of Supplier structures.
 * @param supplierNumber The number of suppliers in the array.
 * @return Returns 0 on success, -1 on failure.
 */
int addSupplier(struct BPlusTree* bPlusTree);

/**
 * @brief Reads a supplier.
 *
 * This function reads a supplier.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int readSupplier();

/**
 * @brief Deletes a supplier based on the supplier's name.
 *
 * This function deletes a supplier from the provided supplier array
 * based on the supplier's name.
 *
 * @param supplierName The name of the supplier to be deleted.
 * @return Returns 0 on success, -1 on failure.
 */
int deleteSupplier();
int costReports();
#endif
