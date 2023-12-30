#include <iostream>
#include <fstream>
#include <string>
#include <CarMaintenance.h>
using namespace HufmanAlgorithm;

int main() {
  char fileName[] = "test.bin";
  char encryptedFileName[] = "encrypted.bin";
  char decryptedFileName[] = "decrypted.bin";
  char name1[50], password1[50], name2[50], password2[50];
  printf("1. Isim: ");
  scanf("%s", name1);
  printf("1. Sifre: ");
  scanf("%s", password1);
  printf("2. Isim: ");
  scanf("%s", name2);
  printf("2. Sifre: ");
  scanf("%s", password2);
  int result = createBinaryFile(fileName, name1, password1, name2, password2);

  if (result != 0) {
    fprintf(stderr, "Binary dosya olusturma hatasi!\n");
    return -1;
  }

  result = encryptFile(fileName, encryptedFileName);

  if (result != 0) {
    fprintf(stderr, "Dosya sifreleme hatasi!\n");
    return -1;
  }

  result = decryptFile(encryptedFileName, decryptedFileName);

  if (result != 0) {
    fprintf(stderr, "Dosya sifre cozme hatasi!\n");
    return -1;
  }

  return 0;
}
