#include <iostream>
#include <fstream>
#include <string>
#include <CarMaintenance.h>

int main() {
  time_t t;
  struct tm *zaman;
  char zamanString[100];
  time(&t);
  zaman = localtime(&t);
  // Tarih ve saat bilgisini string olarak al
  strftime(zamanString, sizeof(zamanString), "%Y-%m-%d %H:%M:%S", zaman);
  struct User user [] = {
    { "john_doe", 1234, true },
    { "alice_smith", 5678, true },
    { "bob_jones", 9876, true }
  };

  // Add users
  if (addUser(user,3) == 0) {
    printf("User added successfully!\n");
  } else {
    printf("Failed to add user.\n");
  }

  // Read users
  printf("\nReading users:\n");

  if (readUser() == 0) {
    printf("User reading successful!\n");
  } else {
    printf("Failed to read users.\n");
  }

  // Delete a user
  const char *usernameToDelete = "alice_smith";
  printf("\nDeleting user with username '%s':\n", usernameToDelete);
  int deleteResult = deletUser(usernameToDelete);

  if (deleteResult == 1) {
    printf("User deleted successfully!\n");
  } else if (deleteResult == -1) {
    printf("User not found for deletion.\n");
  } else {
    printf("Failed to delete user.\n");
  }

  // Read users after deletion
  printf("\nReading users after deletion:\n");
  readUser();
  struct Project project[] = {
    {"BMW",2015,"Silecek suyu icin motor inecek","alimemedaltiner",693131,150000, *zamanString,true},
    {"TOYOTA",2013,"kontrol edilecek","erayburakcakir",88888,9999, *zamanString,true }
  };
  addProject(project, 2);
  readProject();
  deleteProject("alimemedaltiner");
  printf("After deleted PROJECT");
  readProject();
  struct Task task[] = {
    {"BMW","ebcakiir","motor patladi","karassamet",1,*zamanString},
    {"Reault","mert","motor yandi","memedali", 3 ,*zamanString}
  };
  addTask(task,2);
  readTask();
  updateTaskStatus(task, "ebcakiir", 2);
  printf("Task status Updated\n");
  readTask();
  return 0;
}
