#include <iostream>
#include <fstream>
#include <string>
#include <CarMaintenance.h>

int main() {
  struct User users[1] = {
    {"mamudo ", 1234}
  };

  if (addUser(users) == 0) {
    printf("User added successfully!\n");
  } else {
    printf("Failed to add user.\n");
  }

  readUser();
  return 0;
}
