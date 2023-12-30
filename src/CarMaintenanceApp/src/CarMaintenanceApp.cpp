#include <iostream>
#include <fstream>
#include <string>
#include <CarMaintenance.h>

int main() {
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

  if (deleteResult == 0) {
    printf("User deleted successfully!\n");
  } else if (deleteResult == 1) {
    printf("User not found for deletion.\n");
  } else {
    printf("Failed to delete user.\n");
  }

  // Read users after deletion
  printf("\nReading users after deletion:\n");

  if (readUser() == 0) {
    printf("User reading successful!\n");
  } else {
    printf("Failed to read users.\n");
  }

  return 0;
}
