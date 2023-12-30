#ifndef CARMAINTENANCE_H
#define CARMAINTENANCE_H


struct User {
  char username[50];
  int password;
};

int addUser(struct User users[]);
int readUser();
int deletUuser();
int updateUser();
int addProject();
int deleteProject();
int updateProject();
int addTask();
int deleteTask();
int updateTaskStatus();

#endif
