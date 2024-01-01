#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <CarMaintenance.h>
#include <MainMenu.h>

int main() {
  time_t currentTime = time(nullptr);
  struct tm *tmStruct = localtime(&currentTime);
  char date[40];  // Yeterli boyutta bir karakter dizisi seçin
  strftime(date, sizeof(date), "%Y-%m-%d %H:%M", tmStruct);
  printf("%s", date);
  #pragma region Variables
  int screenWidth = 80;
  int screenHeight = 24;
  int x = (screenWidth - 32) / 2;
  int y = (screenHeight - 11) / 2;
  char username[] = "admin";
  char password[] = "123";
  const char *loginMenu[] = {
    "             Login             ",
    "            Register           ",
    "           Guest Mod           "
  };
  const char *authenticetedOptions[] = {
    "   Project and Budget Planning  ",
    "  Task Assignment and Tracking  ",
    "   Cost Analysis and Reporting  ",
    "Supplier and Contractor Database",
    "         Integrations           ",
    "             Exit               "
  };
  const char *projectOptions[] = {
    "         Create Project         ",
    "          View Project          ",
    "          Edit Project          ",
    "         Delete Project         ",
    "       Return to Main Menu      "
  };
  const char *taskOptions[] = {
    "           Assign Task          ",
    "            View Tasks          ",
    "       Update Task Status       ",
    "       Return to Main Menu      "
  };
  const char *costOptions[] = {
    "           Add Expense          ",
    "          View Expenses         ",
    "         Generate Reports       ",
    "       Return to Main Menu      "
  };
  const char *supplierOptions[] = {
    "           Add Supplier         ",
    "          Edit Supplier         ",
    "         Delete Supplier        ",
    "       Return to Main Menu      "
  };
  #pragma endregion
  /*
  #pragma region MainMenu
  int() {
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
      Display::displayMenu(menuOptions, selectedOption, 6, x, y);
      char key = _getch();

      if (key == 72 && selectedOption >= 0) {
        if (selectedOption == 0) {
          selectedOption = 5;
        }
        else {
          selectedOption--;
        }
      }
      else if (key == 80 && selectedOption <= 5) {
        if (selectedOption == 5) {
          selectedOption = 0;
        }
        else {
          selectedOption++;
        }
      }
      else if (key == 13) {
        if (selectedOption == 0) {
          if (
            Display::login()) {
            Display::materialManagementMenu();
          }
        }
        else if (selectedOption == 5) {
          break;
        }
        else if (selectedOption == 1) {
          Display::stockControlMenu();
        }
        else if (selectedOption == 2) {
          Display::warehouseOptimizationMenu();
        }
        else if (selectedOption == 3) {
          Display::reportingMenu();
        }
        else if (selectedOption == 4) {
          Display::integrationMenu();
        }
      }
    }
  }
  #pragma endregion

  #pragma region MaterialManagement
  void Display::materialManagementMenu() {
    HashTableWarehouse hash_table;
    MaterialManagement list;
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
      Display::displayMenu(adminMenuOptions, selectedOption, 7, x, y);
      char key = _getch();

      if (key == 72 && selectedOption >= 0) {
        if (selectedOption == 0) {
          selectedOption = 6;
        }
        else {
          selectedOption--;
        }
      }
      else if (key == 80 && selectedOption <= 6) {
        if (selectedOption == 6) {
          selectedOption = 0;
        }
        else {
          selectedOption++;
        }
      }
      else if (key == 13) {
        if (selectedOption == 0) {
          system("cls");
          Display::addSupplierMaterial("../Warehousedata.txt");
        }
        else if (selectedOption == 1) {
          system("cls");
          list.updateMaterialInteractive();
        }
        else if (selectedOption == 2) {
          system("cls");
          hash_table.deleteMaterialsorCategory("../Warehousedata.txt");
        }
        else if (selectedOption == 3) {
          system("cls");
          Display::searchSupplierMaterial("../Warehousedata.txt");
        }
        else if (selectedOption == 4) {
          system("cls");
          Display::categorizeMaterial();
        }
        else if (selectedOption == 5) {
          system("cls");
          hash_table.loadDataFromFile("../Warehousedata.txt");
          hash_table.listAllData();
          _getch();
        }
        else if (selectedOption == 6) {
          break;
        }
      }
    }
  }
  #pragma endregion

  #pragma region StockControlMenu
  void Display::stockControlMenu() {
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
      Display::displayMenu(stockControlMenuOptions, selectedOption, 4, x, y);
      char key = _getch();

      if (key == 72 && selectedOption >= 0) {
        if (selectedOption == 0) {
          selectedOption = 3;
        }
        else {
          selectedOption--;
        }
      }
      else if (key == 80 && selectedOption <= 3) {
        if (selectedOption == 4) {
          selectedOption = 0;
        }
        else {
          selectedOption++;
        }
      }
      else if (key == 13) {
        if (selectedOption == 0) {
          HashTableWarehouse hash_table;
          system("cls");
          hash_table.loadDataFromFile("../Order.txt");
          hash_table.listAllData();
          _getch();
        }
        else if (selectedOption == 1) {
          Display::reorderPoints();
        }
        else if (selectedOption == 2) {
          Display::productExpirationTracking();
        }
        else if (selectedOption == 3) {
          break;
        }
      }
    }
  }
  #pragma endregion

  #pragma region WareHouseOptimizationMenu
  void Display::warehouseOptimizationMenu() {
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
      Display::displayMenu(warehouseOptimizationMenuOptions, selectedOption, 4, x, y);
      char key = _getch();

      if (key == 72 && selectedOption >= 0) {
        if (selectedOption == 0) {
          selectedOption = 3;
        }
        else {
          selectedOption--;
        }
      }
      else if (key == 80 && selectedOption <= 3) {
        if (selectedOption == 3) {
          selectedOption = 0;
        }
        else {
          selectedOption++;
        }
      }
      else if (key == 13) {
        if (selectedOption == 0) {
          Display::safetyProtocols();
        }
        else if (selectedOption == 1) {
          Display::temperatureMonitoring();
          _getch();
        }
        else if (selectedOption == 2) {
          Display::humidityMonitoring();
          _getch();
        }
        else if (selectedOption == 3) {
          break;
        }
      }
    }
  }
  #pragma endregion

  #pragma region ReportingMenu
  void Display::reportingMenu() {
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
      Display::displayMenu(reportingMenuOptions, selectedOption, 4, x, y);
      char key = _getch();

      if (key == 72 && selectedOption >= 0) {
        if (selectedOption == 0) {
          selectedOption = 3;
        }
        else {
          selectedOption--;
        }
      }
      else if (key == 80 && selectedOption <= 3) {
        if (selectedOption == 3) {
          selectedOption = 0;
        }
        else {
          selectedOption++;
        }
      }
      else if (key == 13) {
        if (selectedOption == 0) {
          Display::mostAccessedItems();
        }
        else if (selectedOption == 1) {
          Display::monthlyStockTurnOver();
        }
        else if (selectedOption == 2) {
          Display::damagedGoodsReports();
        }
        else if (selectedOption == 3) {
          break;
        }
      }
    }
  }
  #pragma endregion

  #pragma region IntegrationMenu
  void Display::integrationMenu() {
    int selectedOption = 0;
    int x = 30;
    int y = 10;

    while (0 == 0) {
      Display::displayMenu(integrationsMenuOptions, selectedOption, 3, x, y);
      char key = _getch();

      if (key == 72 && selectedOption >= 0) {
        if (selectedOption == 0) {
          selectedOption = 2;
        }
        else {
          selectedOption--;
        }
      }
      else if (key == 80 && selectedOption <= 2) {
        if (selectedOption == 2) {
          selectedOption = 0;
        }
        else {
          selectedOption++;
        }
      }
      else if (key == 13) {
        if (selectedOption == 0) {
          Display::supplyChainManagement();
        }
        else if (selectedOption == 1) {
          Display::transportationScheduling();
        }
        else if (selectedOption == 2) {
          break;
        }
      }
    }
  }
  #pragma endregion

  #pragma region ColorFunctions
  void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
  }
  void setBackgorundColor(int backgroundColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor << 4);
  }

  void resetTextColor() {
    setTextColor(15); // Varsayýlan renge geri dön (beyaz renk)
  }
  #pragma endregion

  #pragma region DisplayMenu
  void Display::displayMenu(string options[], int selectedOption, int optionCount, int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    setCursorPosition(x + 15, y);

    for (int i = 0; i <= 43; i++) {
      cout << '=';
    }

    setCursorPosition(x + 20, y + 1);
    cout << "Warehouse Management System Menu" << endl;
    setCursorPosition(x + 15, y + 2);

    for (int i = 0; i <= 43; i++) {
      cout << '=';
    }

    for (int i = 0; i < optionCount; i++) {
      setCursorPosition(x + 22, y + 3 + i);

      if (i == selectedOption) {
        setTextColor(10); // 12 numaralý renk kodu kýrmýzý renktir
        cout << ">" << options[i] << "<" << endl;
      }
      else {
        setTextColor(15); // Varsayýlan renk (beyaz)
        cout << " " << options[i] << endl;
      }
    }

    resetTextColor(); // Varsayýlan rengine geri dön
    setCursorPosition(x + 15, y + optionCount + 3);

    for (int i = 0; i <= 43; i++) {
      cout << '=';
    }
  }
  #pragma endregion

  #pragma region GetPassword
  string Display::getPassword() {
    string password;
    char ch;

    while (true) {
      ch = _getch(); // Kullanýcýnýn tuþa basmasýný bekler, basýlan tuþu okur

      if (ch == 13) { // Enter tuþuna basýldýðýnda döngüyü sonlandýr
        break;
      }

      password.push_back(ch); // Parolayý sakla
      cout << '*'; // Yýldýz karakteri göster
    }

    cout << endl; // Enter tuþuna basýldýðýnda yeni satýr
    return password;
  }
  #pragma endregion
  string enteredUsername, enteredPassword = "";

  int Display::setUsername(const std::string & newUsername) {
    enteredUsername = newUsername;
    return 0;
  }
  int Display::setPassword(const std::string & newPassword) {
    enteredPassword = newPassword;
    return 0;
  }

  #pragma region Login 
  bool Display::login() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    if (enteredUsername == "admin" && enteredPassword == "123") {
      return true;
    }

    int loginAttempts = 0;
    const int maxLoginAttempts = 3;
    setCursorPosition(x + 20, y + 7);
    cout << string(29, '=') << endl;
    setCursorPosition(x + 20, y + 8);
    cout << "=" << string(27, ' ') << "=" << endl;
    setCursorPosition(x + 20, y + 9);
    cout << string(29, '=') << endl;
    setCursorPosition(x + 20, y + 10);
    cout << "=" << string(27, ' ') << "=" << endl;
    setCursorPosition(x + 20, y + 11);
    cout << "=" << string(27, ' ') << "=" << endl;
    setCursorPosition(x + 20, y + 12);
    cout << string(29, '=') << endl;

    while (loginAttempts < maxLoginAttempts) {
      setCursorPosition(x + 26, y + 8);
      cout << " -- LOGIN PAGE -- ";
      setCursorPosition(x + 21, y + 10);
      cout << " User name: ";
      cin >> enteredUsername;
      setCursorPosition(x + 21, y + 11);
      cout << " Password: ";
      enteredPassword = getPassword(); // getPassword iþlevini çaðýr

      if (enteredUsername == "admin" && enteredPassword == "123") {
        setCursorPosition(x + 20, y + 13);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "             Access             " << endl;
        Sleep(1000);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        return true;
      }
      else {
        loginAttempts++;
        setCursorPosition(x + 20, y + 13);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Not Access (" << loginAttempts << "/" << maxLoginAttempts << " attempts)" << endl;
        Sleep(750);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

        if (loginAttempts < maxLoginAttempts) {
          setCursorPosition(x + 20, y + 7);
          cout << string(29, '=') << endl;
          setCursorPosition(x + 20, y + 8);
          cout << "=" << string(27, ' ') << "=" << endl;
          setCursorPosition(x + 20, y + 9);
          cout << string(29, '=') << endl;
          setCursorPosition(x + 20, y + 10);
          cout << "=" << string(27, ' ') << "=" << endl;
          setCursorPosition(x + 20, y + 11);
          cout << "=" << string(27, ' ') << "=" << endl;
          setCursorPosition(x + 20, y + 12);
          cout << string(29, '=') << endl;
          break;
        }

        /*
        else
        {
          setCursorPosition(x + 20, y + 15);
          cout << "Max login attempts reached. Exiting..." << endl;
          Sleep(1500);
          exit(0);

        }*/
  /*
  return false;
  }*/
  /*
  }

  return false;
  }
  #pragma endregion


  */
  /*

    struct User user[] = {
      { "john_doe", 1234, true },
      { "alice_smith", 5678, true },
      { "bob_jones", 9876, true }
    };

    // Add users
    if (addUser(user, 3) == 0) {
      printf("User added successfully!\n");
    }
    else {
      printf("Failed to add user.\n");
    }

    // Read users
    printf("\nReading users:\n");

    if (readUser() == 0) {
      printf("User reading successful!\n");
    }
    else {
      printf("Failed to read users.\n");
    }

    // Delete a user
    const char* usernameToDelete = "alice_smith";
    printf("\nDeleting user with username '%s':\n", usernameToDelete);
    int deleteResult = deleteUser(usernameToDelete);

    if (deleteResult == 1) {
      printf("User deleted successfully!\n");
    }
    else if (deleteResult == -1) {
      printf("User not found for deletion.\n");
    }
    else {
      printf("Failed to delete user.\n");
    }

    // Read users after deletion
    printf("\nReading users after deletion:\n");
    readUser();
    struct Project project[] = {
      {"BMW", 2015, "Silecek suyu icin motor inecek", "alimemedaltiner", 693131, 150000, true, ""},
      {"TOYOTA", 2013, "kontrol edilecek", "erayburakcakir", 88888, 9999, true, ""}
    };
    strcpy(project[0].date1, date);
    strcpy(project[1].date1, date);
    addProject(project, 2);
    readProject();
    deleteProject("alimemedaltiner");
    printf("After deleted PROJECT\n");
    readProject();
    struct Task task[] = {
      {"BMW", "ebcakiir", "motor patladi", "karassamet", 1, ""},
      {"Reault", "mert", "motor yandi", "memedali", 3, ""}
    };
    strcpy(task[0].date1, date);
    strcpy(task[1].date1, date);
    addTask(task, 2);
    readTask();
    updateTaskStatus(task, "ebcakiir", 2);
    printf("Task status Updated\n");
    readTask();
    struct Cost cost[] = {
      {"Mercedes","ebc","","samet",350,"tires"},
      {"Scania","mert","","memed",600,"oil"}
    };
    strcpy(cost[0].date1, date);
    strcpy(cost[1].date1, date);
    addCost(cost, 2);
    readCost();
    struct Supplier supplier[] = {
      {"Hankook","05369705268","almalimert@gmail","Tire"},
      {"Elf","05423563435","ebcakir@gmail.com","Oil"}
    };
    addSupplier(supplier, 2);
    readSupplier();
    deleteSupplier("Elf");
    readSupplier();
    */
  mainMenu();
  return 0;
}

int mainMenu();
