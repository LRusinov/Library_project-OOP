
#include"Library.h"


Library::Library() {
    numOfAdmins = 0;
    numOfReader = 0;
    numOfSeries = 0;
    numOfBooks = 0;
    loggedIn = false;
    currentUser = 0;
}

void Library::login() {
    if (loggedIn) {
        std::cout << "You are already logged in!\n";
    } else {
        String username;
        String password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password:";
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
            std::cout << "Invalid username or password!";
        }
    }
}

void Library::logout() {
    currentUser = 0;
    adminRights = false;
    loggedIn = false;
}

void Library::book_all() const {
    for (size_t i = 0; i < numOfBooks; i++) {
        booksList[i].printInfo();
    }

}

void Library::series_all() const {
    for (size_t i = 0; i < numOfSeries; i++) {
        seriesList[i].printInfo();
    }
}

void Library::list_all() const {
    book_all();
    series_all();
}

void Library::list_info(const String &isbn) const {
    bool flag = false;
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
                break;
            }
        }
    }

}

/*
books find <option> <option_string>[sort <key>[asc | desc]]
        > series find <option> <option_string>[sort <key>[asc | desc]]
        > list find <option> <option_string>[sort <key>[asc | desc]]
*/

void
Library::booksFind(const String &option, const String &str, const String &sort, const String &key, const String &asc) {
    Vector<Book> matchesList;
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
    }
    size_t numOfMatches = matchesList.get_size();
    if (sort != "" && key != "") {
        if (asc != "asc") {
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
        } else {
            for (int i = 0; i < numOfMatches - 1; ++i) {
                for (int j = 1; j < numOfMatches; ++j) {
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

        }
    }
    for (int i = 0; i <numOfMatches ; ++i) {
        matchesList[i].printInfo();
    }
}

void Library::user_find(const String &option, const String &str) const {
    if (option == "name") {
        bool flag = false;
        for (int i = 0; i < numOfAdmins; ++i) {
            if (adminsList[i]->get_username() == str) {
                adminsList[i]->print();
                flag = true;
                break;
            }
        }
        for (int i = 0; i < numOfReader; ++i) {
            if (readersList[i]->get_username() == str) {
                readersList[i]->print();
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::cout << "No user Found!";
        }
    } else if (option == "ID") {
        for (int i = 0; i < numOfReader; ++i) {
            size_t userItems = readersList[i]->get_numOfItems();
            for (int j = 0; j < userItems; ++j) {//???????????????????
                if (readersList[i]->get_items()[i].item->get_ID() == atoi(str.toCharArray())) {
                    readersList[i]->print();
                }
            }
        }

    } else if (option == "state") {

    } else {
        std::cout << "Unknown option!";
    }
}

void Library::user_add(const String &username, const String &password, const String &admin) {
    if (admin != "") {
        adminsList.pushBack(new Admin(username, password, "", ""));
        adminsList[numOfAdmins]->setRegistrationDate(currentDate);
        adminsList[numOfAdmins]->setLastSeenDate(currentDate);
        numOfAdmins++;
        //email sector reg date
    } else {
        readersList.pushBack(new Reader(username, password));
        readersList[numOfReader]->setRegistrationDate(currentDate);
        readersList[numOfReader]->setLastSeenDate(currentDate);
        numOfReader++;
    }
}

void Library::user_remove(const String &username) {
    for (size_t i = 0; i < numOfReader; i++) {
        if (readersList[i]->get_username() == username) {
            delete[] readersList[i];
            readersList.erase(i);
            numOfReader--;
            break;
        }
    }
    for (size_t i = 0; i < numOfAdmins; i++) {
        if (adminsList[i]->get_username() == username) {
            delete[] adminsList[i];
            adminsList.erase(i);
            numOfAdmins--;
            break;
        }
    }

}

void Library::user_change(const String &username) {
    String password;
    String confirmPassword;
    if (username == "") {
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
            std::cout << "You have no permissions!";
        }
    }
}

//void Library::take(const size_t id) {
//    if (!loggedIn) {
//        std::cout << "Your are not logged in!";
//    } else {
//        for (size_t i = 0; i < numOfItems; i++) {
//            if (itemsList[i]->get_ID() == id) {
//                itemsList[i]->set_ifTaken(true);
//            }
//        }
//    }
//}

Library::~Library() {
    for (int i = 0; i < numOfReader; ++i) {
        delete[] readersList[i];
    }
    for (int i = 0; i < numOfAdmins; ++i) {
        delete[] adminsList[i];
    }
}
