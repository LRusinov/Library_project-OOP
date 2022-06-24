
#include <fstream>
#include"Library.h"


Library::Library() {
    numOfAdmins = 0;
    numOfReader = 0;
    numOfSeries = 0;
    numOfBooks = 0;
    loggedIn = false;
    currentUser = 0;
}

Library::~Library() {
    for (int i = 0; i < numOfReader; ++i) {
        delete readersList[i];
    }
    for (int i = 0; i < numOfAdmins; ++i) {
        delete adminsList[i];
    }
}

void Library::login() {
    if (loggedIn) {
        std::cout << "You are already logged in!\n";
    } else {
        String username;
        String password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
        for (int i = 0; i < numOfReader; i++) {
            if (readersList[i]->get_username() == username && readersList[i]->get_password() == password) {
                std::cout << "Welcome " << username << "!\n";
                readersList[i]->setLastSeenDate(currentDate);
                loggedIn = true;
                currentUser = i;
                adminRights = false;
                break;
            }
        }
        if (!loggedIn) {
            for (int i = 0; i < numOfAdmins; i++) {
                if (adminsList[i]->get_username() == username && adminsList[i]->get_password() == password) {
                    std::cout << "Welcome " << username << "!\n";
                    adminsList[i]->setLastSeenDate(currentDate);
                    loggedIn = true;
                    currentUser = i;
                    adminRights = true;
                    break;
                }
            }
        }
        if (!loggedIn) {
            std::cout << "Invalid username or password!\n";
        }
    }
}

void Library::logout() {
    if (loginCheck()) {
        currentUser = 0;
        adminRights = false;
        loggedIn = false;
        std::cout << "Logged out successfully!\n";
    }
}

void Library::bookAdd(const Book &book) {
    std::ofstream myFile;
    myFile.open("Books.txt", std::ios::app);//довавя книгите във файл
    if (myFile.is_open()) {
        myFile << book.get_title() << " " << book.get_author() << " " << book.get_ID() << std::endl;
        myFile.close();
    }
    booksList.pushBack(book);
    numOfBooks++;
}

void Library::seriesAdd(const Series &series) {
    std::ofstream myFile;
    myFile.open("Series.txt", std::ios::app);//довавя печатните издания във файл
    if (myFile.is_open()) {
        myFile << series.get_title() << " " << series.get_author() << " " << series.get_ID() << std::endl;
        myFile.close();
    }
    seriesList.pushBack(series);
    numOfSeries++;
}

void Library::book_all() const {
    if (loginCheck()) {
        if (numOfBooks == 0) { //проверява дали има добавени книги в списъка
            std::cout << "There is no books to be listed!";
        } else {
            for (size_t i = 0; i < numOfBooks; i++) {
                booksList[i].printInfo();
            }
        }
    }

}

void Library::series_all() const {
    if (loginCheck()) {
        if (numOfSeries == 0) { //проверява дали има добавени печатни издания
            std::cout << "There is no books to be listed!";
        } else {
            for (size_t i = 0; i < numOfSeries; i++) {
                seriesList[i].printInfo();
            }
        }
    }
}

void Library::list_all() const {
    if (loginCheck()) {
        std::cout << "BOOKS\n";
        std::cout << "============\n";
        book_all();
        std::cout << "\nSERIES\n";
        std::cout << "============\n";

        series_all();
    }
}

void Library::list_info(const String &isbn) const { //първо проверява списъка с книги след това с печатни издания
    if (loginCheck()) {
        bool flag = false;     //следи дали има съвпадение на isbn
        for (size_t i = 0; i < numOfBooks; i++) {
            if (booksList[i].get_isbn() == isbn) {
                booksList[i].fullInfo();
                flag = true;
                break;
            }
        }
        if (!flag) {
            for (size_t i = 0; i < numOfSeries; i++) {
                if (seriesList[i].get_isbn() == isbn) {
                    seriesList[i].fullInfo();
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) {
            std::cout << "There is no item with this ISBN!";
        }

    }
}

void
Library::booksFind(const String &option, const String &str, const String &sort, const String &key, const String &asc) {
    if (loginCheck()) {
        Vector<Book> matchesList;
        //проверяваме каква опция е подадена на функцията
        if (option == "title") {
            for (size_t i = 0; i < numOfBooks; i++) {
                if (booksList[i].get_title() == str) {
                    matchesList.pushBack(booksList[i]);
                }
            }
        } else if (option == "author") {
            for (size_t i = 0; i < numOfBooks; i++) {
                if (booksList[i].get_author() == str) {
                    matchesList.pushBack(booksList[i]);
                }
            }
        } else if (option == "tag") {
            for (size_t i = 0; i < numOfBooks; i++) {
                size_t numOfKeyWords = booksList[i].get_keyWords().get_size();
                for (size_t j = 0; j < numOfKeyWords; j++) {
                    if (booksList[i].get_keyWords()[j] == str) {
                        matchesList.pushBack(booksList[i]);
                    }
                }
            }
        } else {
            std::cout << "Unknown option!";
            return;
        }
        size_t numOfMatches = matchesList.get_size();

        if (sort != "" && key != "") {
            if (asc != "asc") {
                for (int i = 0; i < numOfMatches - 1; ++i) {
                    for (int j = 1; j < numOfMatches; ++j) {//сортиране с метода на мехурчето
                        if (key == "title") {
                            if (matchesList[j].get_title() > matchesList[i].get_title()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        } else if (key == "author") {
                            if (matchesList[j].get_author() > matchesList[i].get_author()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        } else if (key == "id") {
                            if (matchesList[j].get_ID() > matchesList[i].get_ID()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        } else if (key == "year") {
                            if (matchesList[j].getYear() > matchesList[i].getYear()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        }
                    }
                }
            } else {
                for (int i = 0; i < numOfMatches - 1; ++i) {
                    for (int j = 1; j < numOfMatches; ++j) {
                        if (key == "title") {
                            if (matchesList[j].get_title() < matchesList[i].get_title()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        } else if (key == "author") {
                            if (matchesList[j].get_author() < matchesList[i].get_author()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        } else if (key == "id") {
                            if (matchesList[j].get_ID() < matchesList[i].get_ID()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        } else if (key == "year") {
                            if (matchesList[j].getYear() < matchesList[i].getYear()) {
                                Book temp = matchesList[j];
                                matchesList[j] = matchesList[i];
                                matchesList[i] = temp;
                            }
                        }
                    }
                }

            }
        }
        if (numOfMatches == 0) {
            std::cout << "No matches found!";
            return;
        }
        for (int i = 0; i < numOfMatches; ++i) {
            matchesList[i].printInfo();
        }
    }
}


void Library::user_add(const String &username, const String &password, const String &admin) {
    std::ofstream myFile;
    myFile.open("Users.txt", std::ios::app);//довавя потребителите във файл
    if (myFile.is_open()) {
        myFile << username << " " << password << " " << admin << std::endl;
        myFile.close();
    }
    if (admin != "") {
        adminsList.pushBack(new Admin(username, password, "", ""));
        adminsList[numOfAdmins]->setRegistrationDate(currentDate);
        adminsList[numOfAdmins]->setLastSeenDate(currentDate);
        numOfAdmins++;
    } else {
        readersList.pushBack(new Reader(username, password));
        readersList[numOfReader]->setRegistrationDate(currentDate);
        readersList[numOfReader]->setLastSeenDate(currentDate);
        numOfReader++;
    }
}

void Library::user_remove(const String &username) {
    //първо се проверява дали търсения потребител е в списъка с читатели и след това в списъка с администратори
    if (loginCheck()) {
        bool flag = false;
        for (size_t i = 0; i < numOfReader; i++) {
            if (readersList[i]->get_username() == username) {
                delete readersList[i];
                readersList.erase(i);
                numOfReader--;
                flag = true;
                break;
            }
        }
        if (!flag) {
            for (size_t i = 0; i < numOfAdmins; i++) {
                if (adminsList[i]->get_username() == username) {
                    delete adminsList[i];
                    adminsList.erase(i);
                    numOfAdmins--;
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) {
            std::cout << "User not found!";
        }

    }
}

void Library::user_change(const String &username) {
    if (loggedIn) {
        String password;
        String confirmPassword;
        if (username == "") {
            //за да бъде променена паролата се изисква правилно въвеждане на старата парола
            if (!adminRights) {
                do {
                    std::cout << "Enter your password: ";
                    std::cin >> password;

                    if (readersList[currentUser]->get_password() != password) {
                        std::cout << "Incorrect password!\n";
                    }
                } while (readersList[currentUser]->get_password() != password);
                do {
                    std::cout << "Enter new password: ";
                    std::cin >> password;
                    std::cout << "Confirm password: ";
                    std::cin >> confirmPassword;
                    if (confirmPassword != password) {
                        std::cout << "Passwords don't match!\n";
                    }
                } while (confirmPassword != password);
                readersList[currentUser]->set_password(confirmPassword);
                std::cout << "Password changes successfully!\n";
            } else {
                do {
                    std::cout << "Enter your password: ";
                    std::cin >> password;

                    if (adminsList[currentUser]->get_password() != password) {
                        std::cout << "Incorrect password!\n";
                    }
                } while (adminsList[currentUser]->get_password() != password);
                do {
                    std::cout << "Enter new password: ";
                    std::cin >> password;
                    std::cout << "Confirm password: ";
                    std::cin >> confirmPassword;
                    if (confirmPassword != password) {
                        std::cout << "Passwords don't match!\n";
                    }
                } while (confirmPassword != password);
                adminsList[currentUser]->set_password(confirmPassword);
                std::cout << "Password changes successfully!\n";
            }
        } else {
            if (adminRights) {
                for (size_t i = 0; i < numOfReader; i++) {
                    if (readersList[i]->get_username() == username) {
                        do {
                            std::cout << "Enter your password: ";
                            std::cin >> password;
                            if (readersList[currentUser]->get_password() != password) {
                                std::cout << "Incorrect password!\n";
                            }
                        } while (readersList[currentUser]->get_password() != password);
                        do {
                            std::cout << "Enter new password: ";
                            std::cin >> password;
                            std::cout << "Confirm password: ";
                            std::cin >> confirmPassword;
                            if (confirmPassword != password) {
                                std::cout << "Passwords don't match!\n";
                            }
                        } while (confirmPassword != password);
                        readersList[i]->set_password(confirmPassword);
                        std::cout << "Password changes successfully!\n";
                        break;
                    }
                }
            } else {
                std::cout << "You have no permissions!\n";
            }
        }
    } else {
        std::cout << "You are not logged in!\n";
    }
}

void Library::take(const size_t id) {
    if (!loggedIn) {
        std::cout << "Your are not logged in!\n";
    } else {
        for (size_t i = 0; i < numOfBooks; i++) {
            if (booksList[i].get_ID() == id) {
                if (booksList[i].getIfTaken()) { //проверява дали книгата е свободна
                    std::cout << "Book is already taken!\n";
                    return;
                }
                booksList[i].set_ifTaken(true);
                readersList[currentUser]->takingItem(&booksList[i]);
                readersList[currentUser]->get_items()[readersList[currentUser]->
                        get_numOfItems() - 1].takingDate = currentDate;
                readersList[currentUser]->get_items()[readersList[currentUser]->
                        get_numOfItems() - 1].returnDate = currentDate.nextMonth();
                return;
            }
        }
        for (size_t i = 0; i < numOfSeries; i++) {
            if (seriesList[i].get_ID() == id) {
                if (booksList[i].getIfTaken()) {
                    std::cout << "Series is already taken!\n";
                    return;
                }
                seriesList[i].set_ifTaken(true);
                readersList[currentUser]->takingItem(&seriesList[i]);
                readersList[currentUser]->get_items()[readersList[currentUser]->get_numOfItems() -
                                                      1].takingDate = currentDate;
                readersList[currentUser]->get_items()[readersList[currentUser]->get_numOfItems() -
                                                      1].returnDate = currentDate.nextMonth();
                return;
            }
        }
    }
    std::cout << "No matches found!\n";
}

void Library::returnItem(size_t id) {
    if (!loggedIn) {
        std::cout << "Your are not logged in!";
    } else {
        for (size_t i = 0; i < numOfBooks; i++) {
            if (booksList[i].get_ID() == id) {
                booksList[i].set_ifTaken(false);
                return;
            }
        }
        for (size_t i = 0; i < numOfSeries; i++) {
            if (seriesList[i].get_ID() == id) {
                seriesList[i].set_ifTaken(false);
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
                booksFind("title", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(17, sortPos - 18);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    booksFind("title", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    booksFind("title", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    booksFind("title", str.data(), "sort", key.data());
                }

            }

        } else if (input.find("author") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(18);
                booksFind("author", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(18, sortPos - 19);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    booksFind("author", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    booksFind("author", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    booksFind("author", str.data(), "sort", key.data());
                }

            }
        } else if (input.find("tag") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(14);
                booksFind("tag", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(14, sortPos - 15);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    booksFind("tag", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 5);
                    booksFind("tag", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    booksFind("tag", str.data(), "sort", key.data());
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
        book_all();
    } else if (input.find("series all") == 0) {
        series_all();
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
    if (loggedIn) {
        return true;
    } else {
        std::cout << "You are not logged in!\n";
        return false;
    }
}
