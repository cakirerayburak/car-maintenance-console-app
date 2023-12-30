#include <stdio.h>
#include <stdlib.h>
#include "CarMaintenance.h"

int addUser(struct User users[]) {
  FILE *fp = fopen("login.bin", "ab"); // Use "ab" for appending to an existing binary file

  if (fp == NULL) {
    perror("File Open Error");
    return -1; // Return an error code
  }

  fwrite(users, sizeof(struct User), 1, fp);
  fclose(fp);
  return 0; // Return success
}

int readUser() {
  FILE *fp = fopen("login.bin", "rb");

  if (fp == NULL) {
    perror("Exception While File Opening");
    return 1;
  }

  struct User users;

  while (fread(&users, sizeof(struct User), 1, fp) == 1) {
    printf("Username: %s, Passsword: %d\n", users.username,users.password);
  }

  fclose(fp);
  return 0;
}
