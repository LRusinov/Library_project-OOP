
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
            std::cout << "Invalid username or password!";
        }
    }
}

void Library::logout() {
    currentUser = 0;
    adminRights = false;
    loggedIn = false;
    std::cout<<"Logged out successfully!\n";
}

void Library::book_all() const {
    if (numOfBooks == 0) {
        std::cout << "There is no books to be listed!";
    } else {
        for (size_t i = 0; i < numOfBooks; i++) {
            booksList[i].printInfo();
        }
    }
}

void Library::series_all() const {
    if (numOfSeries == 0) {
        std::cout << "There is no books to be listed!";
    } else {
        for (size_t i = 0; i < numOfSeries; i++) {
            seriesList[i].printInfo();
        }
    }
}

void Library::list_all() const {

    std::cout<<"BOOKS\n";
    std::cout<<"============\n";
    book_all();
    std::cout<<"\nSERIES\n";
    std::cout<<"============\n";

    series_all();
}

void Library::list_info(const String &isbn) const {
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

/*
        > series find <option> <option_string>[sort <key>[asc | desc]]
        > list find <option> <option_string>[sort <key>[asc | desc]]
*/

void
Library::booksFind(const String &option, const String &str, const String &sort, const String &key, const String &asc) {
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

void Library::user_find(const String &option, const String &str) const {
    //проверяване на подадената опция
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

    } else if (option == "state") {// trqbva da se dobavqt danni v reader

    } else {
        std::cout << "Unknown option!";
    }
}

void Library::user_add(const String &username, const String &password, const String &admin) {
    if (admin != "") {//failove
        adminsList.pushBack(new Admin(username, password, "", ""));
        adminsList[numOfAdmins]->setRegistrationDate(currentDate);
        adminsList[numOfAdmins]->setLastSeenDate(currentDate);
        numOfAdmins++;
        //email sector
    } else {
        readersList.pushBack(new Reader(username, password));
        readersList[numOfReader]->setRegistrationDate(currentDate);
        readersList[numOfReader]->setLastSeenDate(currentDate);
        numOfReader++;
    }
}

void Library::user_remove(const String &username) {
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

void Library::user_change(const String &username) {
    if(loggedIn){
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
    }else{
        std::cout<<"You are not logged in!\n";
    }
}

void Library::take(const size_t id) {
    if (!loggedIn) {
        std::cout << "Your are not logged in!\n";
    } else {
        for (size_t i = 0; i < numOfBooks; i++) {
            if (booksList[i].get_ID() == id) {
                if (booksList[i].getIfTaken()) {
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
    help();
    std::string input;
    std::cout << "Enter command:\n";
    std::cin >> input;
    std::string firstWord = input.substr(0, input.find(' '));


    if (firstWord == "help") {
        help();
    } else if (firstWord == "login") {
        login();
    } else if (firstWord == "logout") {
        logout();
    } else if (firstWord == "exit") {
        exit();
    } else if (input.find("books find") == 0) {
        std::string str;
        if (input.find("title") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(17);
                booksFind("title", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(17, input.length() - sortPos - 17);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - sortPos + 2);
                    booksFind("title", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - sortPos + 2);
                    booksFind("title", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    booksFind("title", str.data(), "sort", key.data());
                }

            }

        } else if (input.find("author") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(17);
                booksFind("author", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(17, input.length() - sortPos - 17);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - sortPos + 2);
                    booksFind("author", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - sortPos + 2);
                    booksFind("author", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    booksFind("author", str.data(), "sort", key.data());
                }

            }
        } else if (input.find("tag") != std::string::npos) {
            if (input.find("sort") == std::string::npos) {
                str = input.substr(17);
                booksFind("tag", str.data());
            } else {
                std::string key;
                size_t sortPos = input.find("sort");
                str = input.substr(17, input.length() - sortPos - 17);

                if (input.find("dsc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - sortPos + 2);
                    booksFind("tag", str.data(), "sort", key.data(), "dsc");
                } else if (input.find("asc") != std::string::npos) {
                    key = input.substr(sortPos + 5, input.length() - sortPos + 2);
                    booksFind("tag", str.data(), "sort", key.data(), "asc");
                } else {
                    key = input.substr(sortPos + 5);
                    booksFind("tag", str.data(), "sort", key.data());
                }

            }
        }
    } else if (input.find("books remove") == 0) {
        input.substr(13);
    } else if (firstWord == "take") {
        take(stoi(input.substr(5)));
    } else if (firstWord == "return") {
        returnItem(stoi(input.substr(7)));
    } else if (input.find("user add") == 0) {
        //user_add()
    } else if (input.find("user remove") == 0) {
        user_remove(input.substr(7).data());
    } else if (input.find("user change") == 0) {
        if (input.length() != 11) {
            firstWord = input.substr(12);
            user_change(firstWord.data());
        } else {
            user_change();
        }
    }
//     else if (input.find("user find") == 0) {
////////
//}
    else if (input.find("list all") == 0) {
        list_all();
    } else if (input.find("list info") == 0) {
        list_info(input.substr(10).data());

    } else if (input.find("book all") == 0) {
        book_all();
    } else if (input.find("series all") == 0) {
        series_all();
    }
}

int Library::exit() {
    return 0;
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
    std::cout << "books add\n";
    std::cout << "books remove\n";
    std::cout << "take\n";
    std::cout << "return\n";
    std::cout << "user change\n";
    std::cout << "user add\n";
    std::cout << "user remove\n";
    std::cout << "user find\n";
}

void Library::bookAdd(const Book &book) {
    booksList.pushBack(book);
    numOfBooks++;
}

void Library::seriesAdd(const Series &series) {
seriesList.pushBack(series);
numOfSeries++;
}
