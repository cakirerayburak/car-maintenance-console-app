#include "../header/CarMaintenance.h"
#include <gtest/gtest.h>

/*
// Test addUser, readUser, and deleteUser functions
TEST(CarMaintenanceTest, AddReadAndDeleteUser) {
  // Create a test user
  struct User testUser = { "testuser", 1234, true };
  // Add the user to the file
  // ASSERT_EQ(addUser(&testUser), 0);
  // Read the user from the file and check if it's added correctly
  testing::internal::CaptureStdout();  // Capture standard output to check the printed messages
  ASSERT_EQ(readUser(), 0);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_TRUE(output.find("Username: testuser, Passsword: 1234, Status: 1") != std::string::npos);
  // Delete the user
  ASSERT_EQ(deleteUser("testuser"), 0);
  // Read the user again and check if it's deleted
  testing::internal::CaptureStdout();
  ASSERT_EQ(readUser(), 0);
  output = testing::internal::GetCapturedStdout();
  ASSERT_TRUE(output.find("User with username testuser not found.") != std::string::npos);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/
