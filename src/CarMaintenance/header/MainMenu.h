/**
 * @file console.h
 * @brief Definitions for console manipulation functions.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

/**
 * @brief Enumeration representing console text colors.
 */
enum ConsoleColor {
  BLACK = 0,            /**< Black color. */
  BLUE = 1,             /**< Blue color. */
  GREEN = 2,            /**< Green color. */
  CYAN = 3,             /**< Cyan color. */
  RED = 4,              /**< Red color. */
  MAGENTA = 5,          /**< Magenta color. */
  YELLOW = 6,           /**< Yellow color. */
  WHITE = 7,            /**< White color. */
  GRAY = 8,             /**< Gray color. */
  LIGHT_BLUE = 9,       /**< Light blue color. */
  LIGHT_GREEN = 10,     /**< Light green color. */
  LIGHT_CYAN = 11,      /**< Light cyan color. */
  LIGHT_RED = 12,       /**< Light red color. */
  LIGHT_MAGENTA = 13,   /**< Light magenta color. */
  LIGHT_YELLOW = 14,    /**< Light yellow color. */
  BRIGHT_WHITE = 15     /**< Bright white color. */
};


int mainMenu();
int displayMenu(const char **menuOptions, int selectedOption, int menuSize, int x, int y);
int setCursorPosition(int x, int y);

/**
 * @brief Sets the console text color.
 * @param color The desired text color.
 */
int setTextColor(enum ConsoleColor color);

/**
 * @brief Sets the console background color.
 * @param backgroundColor The desired background color.
 */
int setBackgroundColor(enum ConsoleColor backgroundColor);

int authenticateUser(const char* enteredUsername);
int getPassword();
int login();
int authenticatedMenu();
int guestMenu();
int projectMenu();
int taskMenu();
int costMenu();
int supplierMenu();







#endif
