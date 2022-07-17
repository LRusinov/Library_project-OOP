
#include <fstream>
#include"Library.h"


Library::Library() :
        numOfUsers(0),
        numOfLibItems(0),
        currentUser(0),
        adminRights(true) {}

Library::~Library() {
    for (int i = 0; i < numOfLibItems; ++i) {
        delete listOfLibItems[i];
    }
    for (int i = 0; i < numOfUsers; ++i) {
        delete listOfUsers[i];
    }
}

void Library::login() {
    if (currentUser != -1) {
        std::cout << "You are already logged in!\n";
        return;
    }
    std::string username;
    std::string password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    for (int i = 0; i < numOfUsers; i++) {
        if (listOfUsers[i]->get_username() == username && listOfUsers[i]->get_password() == password) {
            std::cout << "Welcome " << username << "!\n";
            listOfUsers[i]->setLastSeenDate(currentDate);
            currentUser = i;
            adminRights = listOfUsers[i]->getAdminRights();
            break;
        }
    }

    if (currentUser == -1) {
        std::cout << "Invalid username or password!\n";
    }

}

void Library::logout() {
    if (loginCheck()) {
        currentUser = -1;
        adminRights = false;
        std::cout << "Logged out successfully!\n";
    }
}

void Library::itemAdd(LibraryItem *libItem) {
    listOfLibItems.push_back(libItem);
    numOfLibItems++;
}

void Library::bookAdd(Book &book) {
    if (loginCheck()) {
        itemAdd(&book);
        std::ofstream myFile;
        myFile.open("Books.txt", std::ios::app);//довавя книгите във файл
        if (myFile.is_open()) {
            myFile << book.get_title() << "||" << book.get_author() << "||" << book.get_ID() << std::endl;
            myFile.close();
        }
    }
}

void Library::seriesAdd(Series &series) {
    if (loginCheck()) {
        itemAdd(&series);
        std::ofstream myFile;
        myFile.open("Series.txt", std::ios::app);//довавя печатните издания във файл
        if (myFile.is_open()) {
            myFile << series.get_title() << " " << series.get_author() << " " << series.get_ID() << std::endl;
            myFile.close();
        }
    }
}

template<typename T>
void Library::item_all() const {
    if (loginCheck()) {
        int counter = 0;
        for (size_t i = 0; i < numOfLibItems; i++) {
            if (listOfLibItems[i]->type() == typeid(T).name()) {
                listOfLibItems[i]->printInfo();
                counter++;
            }
        }
        if (counter == 0) {
            std::cout << "There is no items to be listed!\n";
        }
    }
}

void Library::list_all() const {
    if (loginCheck()) {
        std::cout << "BOOKS\n";
        std::cout << "============\n";
        item_all<Book>();
        std::cout << "\nSERIES\n";
        std::cout << "============\n";
        item_all<Series>();
    }
}

void Library::list_info(const std::string &isbn) const { //първо проверява списъка с книги след това с печатни издания
    if (loginCheck()) {
        for (int i = 0; i < numOfLibItems; ++i) {
            if (listOfLibItems[i]->get_isbn() == isbn) {
                listOfLibItems[i]->fullInfo();
            }
        }
    }
}

template<typename T>
void
Library::find(const std::string &option, const std::string &str, bool sort, const std::string &key, bool asc) {
    if (loginCheck()) {
        std::vector<LibraryItem *> matchesList;
        //проверяваме каква опция е подадена на функцията

        for (size_t i = 0; i < numOfLibItems; i++) {
            if (typeid(listOfLibItems[i]) == typeid(T)) {
                if (option == "title") {
                    if (listOfLibItems[i]->get_title() == str) {
                        matchesList.push_back(listOfLibItems[i]);
                    }
                } else if (option == "author") {

                    if (listOfLibItems[i]->get_author() == str) {
                        matchesList.push_back(listOfLibItems[i]);
                    }

                } else if (option == "tag") {

                    size_t numOfKeyWords = listOfLibItems[i]->get_keyWords().size();
                    for (size_t j = 0; j < numOfKeyWords; j++) {
                        if (listOfLibItems[i]->get_keyWords()[j] == str) {
                            matchesList.push_back(listOfLibItems[i]);
                        }

                    }
                } else {
                    std::cout << "Unknown option!";
                    return;
                }
            }
        }
        size_t numOfMatches = matchesList.size();

        if (numOfMatches == 0) {
            std::cout << "No matches found!";
            return;
        }

        if (!sort) {
            for (int i = 0; i < numOfMatches; ++i) {
                matchesList[i]->printInfo();
            }
        } else {
            for (int i = 0; i < numOfMatches - 1; ++i) {
                for (int j = 1; j < numOfMatches; ++j) {
                    if (asc) {
                        if (matchesList[i]->cmp(key, matchesList[j])) {
                            LibraryItem::swap(matchesList[i], matchesList[j]);
                        }

                    } else {
                        if (!matchesList[i]->cmp(key, matchesList[j])) {
                            LibraryItem::swap(matchesList[i], matchesList[j]);
                        }

                    }
                }
            }
        }
    }
}

/*    std::ofstream myFile;
    myFile.open("Users.txt", std::ios::app);//довавя потребителите във файл
    if (myFile.is_open()) {
        myFile << username << "||" << password << "||" << admin << std::endl;
        myFile.close();
    }*/
void Library::user_add(const std::string &username, const std::string &password, bool admin,
                       const std::string &email, const std::string &sector) {

    for (int i = 0; i < numOfUsers; ++i) {
        if (listOfUsers[i]->get_username() == username) {
            std::cout << "This username is already registered!\n";
            return;
        }
    }
    if (loginCheck() && rightsCheck()) {
        if (admin) {
            listOfUsers.push_back(new Admin(username, password, currentDate, email, sector));
        } else {
            listOfUsers.push_back(new Reader(username, password, currentDate));

        }
        listOfUsers[numOfUsers]->setLastSeenDate(currentDate);
        numOfUsers++;
    }
}

void Library::user_remove(const std::string &username) {

    if (loginCheck() && rightsCheck()) {
        for (size_t i = 0; i < numOfUsers; i++) {
            if (listOfUsers[i]->get_username() == username) {
                delete listOfUsers[i];
                listOfUsers.erase(listOfUsers.begin() + i);
                numOfUsers--;
                return;
            }
        }

        std::cout << "User not found!";


    }
}

void Library::user_change(const std::string &username) {
    if (loginCheck()) {
        if (username.empty()) {
            passwordCheck();
            listOfUsers[currentUser]->set_password(passwordChange());
            std::cout << "Password changed successfully!\n";
            if (adminRights) {
                for (size_t i = 0; i < numOfUsers; i++) {
                    if (listOfUsers[i]->get_username() == username) {
                        passwordCheck();

                        listOfUsers[i]->set_password(passwordChange());
                        std::cout << "Password changes successfully!\n";
                        return;
                    }
                }
            } else {
                std::cout << "You have no permissions!\n";
            }
        }
    }
}

void Library::take(const size_t id) {
    if (adminRights) {
        std::cout << "Administrator accounts can not take items!\n";
        return;
    }
    if (loginCheck()) {
        for (size_t i = 0; i < numOfLibItems; i++) {
            if (listOfLibItems[i]->get_ID() == id) {
                if (listOfLibItems[i]->getIfTaken()) {
                    std::cout << "The item is already taken!\n";
                    return;
                }
                listOfLibItems[i]->set_ifTaken(true);
                listOfLibItems[i]->setTakingDate(currentDate);
                listOfLibItems[i]->setReturnDate(currentDate.nextMonth());
                listOfUsers[currentUser]->takingItem(listOfLibItems[i]);
                return;
            }
        }
        std::cout << "No matches found!\n";
    }

}

void Library::returnItem(size_t id) {
    if (loginCheck()) {
        for (size_t i = 0; i < numOfLibItems; i++) {
            if (listOfLibItems[i]->get_ID() == id) {
                listOfLibItems[i]->set_ifTaken(false);
                return;
            }
        }
        std::cout << "No matches found!\n";
    }
}

void Library::menu() {
    std::string input;
    std::cout << "Enter command:\n";
    std::getline(std::cin, input);
    std::string firstWord = input.substr(0, input.find(' '));
    size_t len = input.length();

    if (firstWord == "help") {
        help();
    } else if (firstWord == "login") {
        login();
    } else if (firstWord == "logout") {
        logout();
    } else if (firstWord == "exit") {
        return;
    } else if (input.find("books find") == 0 && len > 10) {
        std::string str;
        if (input.find("title") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(17);
                find<Book>("title", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(17, sortPos - 18);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    find<Book>("title", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    find<Book>("title", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    find<Book>("title", str.data(), "sort", key.data());
                }

            }

        } else if (input.find("author") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(18);
                find<Book>("author", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(18, sortPos - 19);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    find<Book>("author", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    find<Book>("author", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    find<Book>("author", str.data(), "sort", key.data());
                }

            }
        } else if (input.find("tag") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(14);
                find<Book>("tag", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(14, sortPos - 15);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    find<Book>("tag", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    find<Book>("tag", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    find<Book>("tag", str.data(), "sort", key.data());
                }

            }
        } else {
            std::cout << "Invalid key!\n";
        }
    } else if (input.find("books remove") == 0 && len > 12) {
        input.substr(13);
    } else if (firstWord == "take" && len > 4) {
        take(stoi(input.substr(5)));
    } else if (firstWord == "return" && len > 6) {
        returnItem(stoi(input.substr(7)));
    } else if (input.find("user add") == 0 && len > 8) {

        std::string password;
        if (input.find("admin") != std::string::npos) {
            firstWord = input.substr(9, input.length() - input.find(' ', 10) - 7);
            std::cout << firstWord;
            password = input.substr(input.find(' ', 10) + 1, input.length() - input.find("admin", 10) - 1);
            user_add(firstWord.data(), password.data(), "admin");
        } else {
            firstWord = input.substr(9, input.length() - input.find(' ', 10) - 1);
            password = input.substr(input.find(' ', 10) + 1);
            user_add(firstWord.data(), password.data());
        }
    } else if (input.find("user remove") == 0 && len > 11) {
        user_remove(input.substr(12).data());
    } else if (input.find("user change") == 0 && len > 11) {
        if (input.length() != 11) {
            firstWord = input.substr(12);
            user_change(firstWord.data());
        } else {
            user_change();
        }
    } else if (input.find("list all") == 0) {
        list_all();
    } else if (input.find("list info") == 0 && len > 9) {
        list_info(input.substr(10).data());

    } else if (input.find("book all") == 0) {
        item_all<Book>();
    } else if (input.find("series all") == 0) {
        item_all<Series>();
    } else {
        std::cout << "Wrong command!\n";
    }
    menu();
}

void Library::help() {
    std::cout << "Command list:\n";
    std::cout << "help\n";
    std::cout << "login\n";
    std::cout << "logout\n";
    std::cout << "exit\n";
    std::cout << "book all\n";
    std::cout << "series all\n";
    std::cout << "list all\n";
    std::cout << "list info\n";
    std::cout << "books find\n";
    std::cout << "books view\n";
    std::cout << "take\n";
    std::cout << "return\n";
    std::cout << "user change\n";
    std::cout << "user add\n";
    std::cout << "user remove\n";
}

bool Library::loginCheck() const {
    if (currentUser != -1) {
        return true;
    } else {
        std::cout << "You are not logged in!\n";
        return false;
    }
}

bool Library::rightsCheck() const {
    if (!adminRights) {
        std::cout << "You have have no permissions!\n";
        return false;
    } else {
        return true;
    }
}

std::string Library::passwordChange() {
    std::string password;
    std::string confirmPassword;
    do {
        std::cout << "Enter new password: ";
        std::cin >> password;
        std::cout << "Confirm password: ";
        std::cin >> confirmPassword;
        if (confirmPassword != password) {
            std::cout << "Passwords don't match!\n";
        }
    } while (confirmPassword != password);
    return confirmPassword;
}

void Library::passwordCheck() {
    std::string password;
    do {
        std::cout << "Enter your password: ";
        std::cin >> password;
        if (listOfUsers[currentUser]->get_password() != password) {
            std::cout << "Incorrect password!\n";
        }
    } while (listOfUsers[currentUser]->get_password() != password);
}




