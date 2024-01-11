#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <MainMenu.h>

class UserInput {
public:
    enum InputType {
        STRING,
        INTEGER,
        PAGE_DOWN,
        PAGE_UP,
        ENTER
    };

    UserInput(InputType type, const std::string& strData, int intData)
        : type(type), strData(strData), intData(intData) {}

    UserInput(InputType type)
        : type(type), strData(""), intData(0) {}

    InputType getType() const {
        return type;
    }

    const std::string& getStringData() const {
        return strData;
    }

    int getIntegerData() const {
        return intData;
    }
    std::string getString() const {
        std::ostringstream oss;

        switch (type) {
        case STRING:
            oss << "STRING: " << strData;
            break;

        case INTEGER:
            oss << "INTEGER: " << intData;
            break;

        case PAGE_DOWN:
            oss << "PAGE_DOWN";
            break;

        case PAGE_UP:
            oss << "PAGE_UP";
            break;

        case ENTER:
            oss << "ENTER";
            break;
        }

        return oss.str();
    }

private:
    InputType type;
    std::string strData;
    int intData;
};

void simulateUserInput(const std::vector<UserInput>& inputs) {
    std::this_thread::sleep_for(std::chrono::seconds(7));

    for (const auto& input : inputs) {
        switch (input.getType()) {
        case UserInput::STRING:
            for (char c : input.getStringData()) {
                keybd_event(c, 0, 0, 0);
                keybd_event(c, 0, KEYEVENTF_KEYUP, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Karakter arasýnda küçük bir bekleme
            }
            break;

        case UserInput::INTEGER:
            for (char c : std::to_string(input.getIntegerData())) {
                keybd_event(c, 0, 0, 0);
                keybd_event(c, 0, KEYEVENTF_KEYUP, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Karakter arasýnda küçük bir bekleme
            }
            break;

        case UserInput::PAGE_DOWN:
            keybd_event(VK_DOWN, 0, 0, 0);
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            break;

        case UserInput::PAGE_UP:
            keybd_event(VK_UP, 0, 0, 0);
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
            break;

        case UserInput::ENTER:
            keybd_event(VK_RETURN, 0, 0, 0);
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void runMenu() {
    mainMenu(std::cin, std::cout);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

TEST(MyTest, MenuTest) 
{
    std::ostringstream consoleOutput;
    std::vector<UserInput> userInputSequence = {
        UserInput(UserInput::PAGE_DOWN),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "ADMIN", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::INTEGER, "", 1234),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::PAGE_UP),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "ADMIN", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::INTEGER, "", 1234),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTBRAND", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::INTEGER, "", 2024),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTREPAIR", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTDRIVER", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "11111111111", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::INTEGER, "", 222222),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::PAGE_DOWN),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTDRIVER", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::PAGE_DOWN),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTDRIVER", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTBRANDNEW", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::INTEGER, "", 2024),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTREPAIRNEW", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTDRIVERNEW", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "22222222222", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::INTEGER, "", 333333),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::PAGE_UP),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTDRIVERNEW", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::PAGE_DOWN),
        UserInput(UserInput::PAGE_DOWN),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::STRING, "TESTDRIVERNEW", 0),
        UserInput(UserInput::ENTER),
        UserInput(UserInput::PAGE_DOWN),
        UserInput(UserInput::ENTER),

    };

    std::thread menuThread(runMenu);
    std::thread userInputThread(simulateUserInput, std::ref(userInputSequence));

    menuThread.join();
    userInputThread.join();


    std::string actualOutput = consoleOutput.str();
    std::string expectedOutput =
        "PAGE_DOWN\nENTER\nSTRING: ADMIN\nENTER\nINTEGER: 1234\nENTER\n"
        "PAGE_UP\nENTER\nSTRING: ADMIN\nENTER\nINTEGER: 1234\nENTER\nENTER\n"
        "STRING: TESTBRAND\nENTER\nINTEGER: 2024\nENTER\nSTRING: TESTREPAIR\nENTER\n"
        "STRING: TESTDRIVER\nENTER\nSTRING: 11111111111\nENTER\nINTEGER: 222222\nENTER\nENTER\n"
        "PAGE_DOWN\nENTER\nSTRING: TESTDRIVER\nENTER\nENTER\nPAGE_DOWN\nENTER\n"
        "STRING: TESTDRIVER\nENTER\nSTRING: TESTBRANDNEW\nENTER\nINTEGER: 2024\nENTER\n"
        "STRING: TESTREPAIRNEW\nENTER\nSTRING: TESTDRIVERNEW\nENTER\nSTRING: 22222222222\nENTER\nINTEGER: 333333\nENTER\nENTER\n"
        "PAGE_UP\nENTER\nSTRING: TESTDRIVERNEW\nENTER\nENTER\nPAGE_DOWN\nPAGE_DOWN\nENTER\n"
        "STRING: TESTDRIVERNEW\nENTER\nPAGE_DOWN\nENTER";

    ASSERT_EQ(actualOutput, expectedOutput);
    
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
