#include <fstream>
#include"Library.h"

Library::Library() :
        numOfUsers(0),
        numOfLibItems(0),
        currentUser(0),
        adminRights(true) {
    time_t now = time(nullptr);
    struct tm *tm = localtime(&now);
    currentDate.set_day(tm->tm_mday);
    currentDate.set_month(tm->tm_mon + 1);
    currentDate.set_year(tm->tm_year + 1900);
}

Library::~Library() {
    for (int i = 0; i < numOfLibItems; ++i) {
        delete listOfLibItems[i];
    }
    for (int i = 0; i < numOfUsers; ++i) {
        delete listOfUsers[i];
    }
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
    std::cin.ignore();
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
    std::cin.ignore();
}

template<typename T>
void Library::swap(T &obj1, T &obj2) {
    T temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}

std::vector<std::string> Library::keyWordsHelper(const std::string &str) {
    std::string buff;
    std::vector<std::string> vec;
    size_t len = str.length();
    int counter = 0;
    for (size_t i = 0; i < len; ++i) {
        if (i + 1 == len) {
            buff.push_back(str[i]);
            vec.push_back(buff);
            break;
        } else if (str[i] == ',') {
            i++;
            vec.push_back(buff);
            buff.clear();
            counter = 0;
        }
        buff.push_back(str[i]);
        counter++;
    }
    return vec;
}

Date Library::stringToDate(const std::string &str) {
    size_t len = str.length();
    if (len == 7 || len == 6) {
        char *year = new char[4];
        char *month = new char[2];
        str.copy(year, 4, 0);
        str.copy(month, 2, 5);
        Date res;
        try {
            res.set_month(atoi(month));
            res.set_year(atoi(year));
        }
        catch (...) {
            std::cout << "Invalid date string\n";
        }
        delete[] month;
        delete[] year;
        return res;
    }
    return {};
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
    std::cin.ignore();
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

template<typename T>
void Library::item_all() const {
    if (loginCheck()) {
        int counter = 0;
        for (int i = 0; i < numOfLibItems; i++) {
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

void Library::list_info(const std::string &isbn) const {
    if (loginCheck()) {
        for (int i = 0; i < numOfLibItems; ++i) {
            if (listOfLibItems[i]->get_isbn() == isbn) {
                listOfLibItems[i]->fullInfo();
                return;
            }
        }
        std::cout << "There is no item with this isbn!\n";
    }
}

template<typename T>
void
Library::find(const std::string &option, const std::string &str, bool sort, const std::string &key, bool asc) {
    if (loginCheck()) {
        std::vector<LibraryItem *> matchesList;

        for (int i = 0; i < numOfLibItems; i++) {
            if (listOfLibItems[i]->type() == typeid(T).name()) {

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
            std::cout << "No matches found!\n";
            return;
        }
        if (sort) {
            for (int i = 0; i < numOfMatches - 1; ++i) {
                for (int j = 1; j < numOfMatches; ++j) {
                    try {
                        if (asc) {
                            if (!matchesList[i]->cmp(key, matchesList[j])) {
                                swap(matchesList[i], matchesList[j]);
                            }
                        } else {
                            if (matchesList[i]->cmp(key, matchesList[j])) {
                                swap(matchesList[i], matchesList[j]);
                            }
                        }
                    }
                    catch (const std::string &message) {
                        std::cout << message << std::endl;
                        return;
                    }
                }
            }
        }
        for (int i = 0; i < numOfMatches; ++i) {
            matchesList[i]->printInfo();
        }
    }
}

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
        std::cout << "User """ << username << """ added successfully!\n";
    }
}

void Library::user_remove(const std::string &username) {
    if (loginCheck() && rightsCheck()) {
        for (int i = 0; i < numOfUsers; i++) {
            if (listOfUsers[i]->get_username() == username) {
                if (i == currentUser) {
                    std::cout << "Invalid operation! The user is currently logged in!\n";
                    return;
                }
                delete listOfUsers[i];
                listOfUsers.erase(listOfUsers.begin() + i);
                numOfUsers--;
                std::cout << "User deleted successfully!\n";
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
            return;
        }
        if (adminRights) {
            for (int i = 0; i < numOfUsers; i++) {
                if (listOfUsers[i]->get_username() == username) {
                    passwordCheck();
                    listOfUsers[i]->set_password(passwordChange());
                    std::cout << "Password changes successfully!\n";
                    return;
                }
            }
            std::cout << "User not found!\n";
        } else {
            std::cout << "You have no permissions!\n";
        }
    }
}

void Library::users_list() {
    if (loginCheck() && rightsCheck()) {
        if (numOfUsers == 0) {
            std::cout << "There aren't any users!\n";
            return;
        }
        for (int i = 0; i < numOfUsers; ++i) {
            std::cout << "Username: " << listOfUsers[i]->get_username();
            if (listOfUsers[i]->getAdminRights()) { std::cout << " ADMINISTRATOR"; }
            else { std::cout << " Password: " << listOfUsers[i]->get_password(); }
            std::cout << " Last seen: " << listOfUsers[i]->getLastSeenDate() << std::endl;
        }
    }
}

void Library::take(const int id) {
    if (adminRights) {
        std::cout << "Administrator accounts can not take items!\n";
        return;
    }
    if (loginCheck()) {
        for (int i = 0; i < numOfLibItems; i++) {
            if (listOfLibItems[i]->get_ID() == id) {
                if (listOfLibItems[i]->getIfTaken()) {
                    std::cout << "The item is already taken!\n";
                    return;
                }
                listOfLibItems[i]->set_ifTaken(true);
                listOfLibItems[i]->setTakingDate(currentDate);
                listOfLibItems[i]->setReturnDate(currentDate.nextMonth());
                listOfUsers[currentUser]->takingItem(listOfLibItems[i]);
                std::cout << "You took """ << listOfLibItems[i]->get_title() << """!\n";
                return;
            }
        }
        std::cout << "No matches found!\n";
    }
}

void Library::returnItem(int id) {
    if (loginCheck()) {
        for (int i = 0; i < numOfLibItems; i++) {
            if (listOfLibItems[i]->get_ID() == id) {
                if (!listOfLibItems[i]->getIfTaken()) {
                    std::cout << "Invalid return!\n";
                    return;
                }
                listOfLibItems[i]->set_ifTaken(false);
                std::cout << "You returned """ << listOfLibItems[i]->get_title() << """!\n";
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

    if (input == "help") {
        help();
    } else if (input == "login") {
        login();
    } else if (input == "logout") {
        logout();
    } else if (input == "exit") {
        dataSave("Users.txt", "Articles.txt", "Books.txt", "Series.txt");
        return;
    } else if (input.find("books find") == 0 && len > 11) {
        try {
            std::string str;
            if (input.find("author") == 11) {
                if (input.find("sort") == std::string::npos) {
                    str = input.substr(18);
                    find<Book>("author", str);
                } else {
                    std::string key;
                    size_t sortPos = input.find("sort");
                    str = input.substr(18, sortPos - 19);
                    if (input.find("dsc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Book>("author", str, "sort", key, false);
                    } else if (input.find("asc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Book>("author", str, "sort", key, true);
                    } else {
                        key = input.substr(sortPos + 5);
                        find<Book>("author", str, "sort", key);
                    }
                }
            } else if (input.find("title") == 11) {
                if (input.find("sort") == std::string::npos) {
                    str = input.substr(17);
                    find<Book>("title", str);
                } else {
                    std::string key;
                    size_t sortPos = input.find("sort");
                    str = input.substr(17, sortPos - 18);
                    if (input.find("dsc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Book>("title", str, "sort", key, false);
                    } else if (input.find("asc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Book>("title", str, "sort", key, true);
                    } else {
                        key = input.substr(sortPos + 5);
                        find<Book>("title", str, "sort", key);
                    }
                }
            } else if (input.find("tag") == 11) {
                if (input.find("sort") == std::string::npos) {
                    str = input.substr(15);
                    find<Book>("tag", str);
                } else {
                    std::string key;
                    size_t sortPos = input.find("sort");
                    str = input.substr(15, sortPos - 16);
                    if (input.find("dsc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Book>("tag", str, "sort", key, false);
                    } else if (input.find("asc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Book>("tag", str, "sort", key, true);
                    } else {
                        key = input.substr(sortPos + 5);
                        find<Book>("tag", str, "sort", key);
                    }
                }
            } else {
                std::cout << "Invalid key!\n";
            }
        } catch (...) {
            std::cout << "Invalid command!\n";
        }
    } else if (input.find("series find") == 0 && len > 12) {
        try {
            std::string str;
            if (input.find("author") == 12) {
                if (input.find("sort") == std::string::npos) {
                    str = input.substr(19);
                    find<Series>("author", str);
                } else {
                    std::string key;
                    size_t sortPos = input.find("sort");
                    str = input.substr(19, sortPos - 20);
                    if (input.find("dsc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Series>("author", str, "sort", key, false);
                    } else if (input.find("asc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Series>("author", str, "sort", key, true);
                    } else {
                        key = input.substr(sortPos + 5);
                        find<Series>("author", str, "sort", key);
                    }
                }
            } else if (input.find("title") == 12) {
                if (input.find("sort") == std::string::npos) {
                    str = input.substr(18);
                    find<Series>("title", str);
                } else {
                    std::string key;
                    size_t sortPos = input.find("sort");
                    str = input.substr(18, sortPos - 19);
                    if (input.find("dsc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Series>("title", str, "sort", key, false);
                    } else if (input.find("asc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Series>("title", str, "sort", key, true);
                    } else {
                        key = input.substr(sortPos + 5);
                        find<Series>("title", str, "sort", key);
                    }
                }
            } else if (input.find("tag") == 12) {
                if (input.find("sort") == std::string::npos) {
                    str = input.substr(16);
                    find<Series>("tag", str);
                } else {
                    std::string key;
                    size_t sortPos = input.find("sort");
                    str = input.substr(16, sortPos - 17);
                    if (input.find("dsc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Series>("tag", str, "sort", key, false);
                    } else if (input.find("asc") != std::string::npos) {
                        key = input.substr(sortPos + 5, input.length() - 3 - sortPos - 6);
                        find<Series>("tag", str, "sort", key, true);
                    } else {
                        key = input.substr(sortPos + 5);
                        find<Series>("tag", str, "sort", key);
                    }
                }
            } else {
                std::cout << "Invalid key!\n";
            }
        }
        catch (...) {
            std::cout << "Invalid command!\n";
        }
    } else if (firstWord == "take" && len > 5) {
        try {
            take(stoi(input.substr(5)));
        }
        catch (...) {
            std::cout << "Invalid ID\n";
        }
    } else if (firstWord == "return" && len > 7) {
        try {
            returnItem(stoi(input.substr(7)));
        }
        catch (...) {
            std::cout << "Invalid ID!\n";
        }
    } else if (input.find("user add") == 0 && len > 9) {
        std::string password;
        if (input.find("admin") + 4 == input.length() - 1) {
            firstWord = input.substr(9, input.find(' ', 10) - 9);
            password = input.substr(input.find(' ', 10) + 1, input.length() - input.find("admin", 12) - 2);
            user_add(firstWord, password, true);
        } else {
            firstWord = input.substr(9, input.find(' ', 10) - 9);
            password = input.substr(input.find(' ', 10) + 1);
            user_add(firstWord, password);
        }
    } else if (input.find("user remove") == 0 && len > 12) {
        user_remove(input.substr(12));
    } else if (input.find("user change") == 0) {
        if (input.length() != 11) {
            firstWord = input.substr(12);
            user_change(firstWord);
        } else {
            user_change();
        }
    } else if (input == "list all") {
        list_all();
    } else if (input.find("list info") == 0 && len > 9) {
        list_info(input.substr(10));

    } else if (input == "book all") {
        item_all<Book>();
    } else if (input == "users list") {
        users_list();
    } else if (input == "series all") {
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
    std::cout << "series find\n";
    std::cout << "take\n";
    std::cout << "return\n";
    std::cout << "user change\n";
    std::cout << "user add\n";
    std::cout << "users list\n";
    std::cout << "user remove\n";
}

void Library::addUsersFromFile(const std::string &fileName) {
    std::string username;
    std::string password;
    std::string admin;
    std::ifstream myFile;
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()) {
        while (std::getline(myFile, username, '\t')) {
            std::getline(myFile, password, '\t');
            std::getline(myFile, admin, '\n');
            if (admin == "1") {
                listOfUsers.push_back(new Admin(username, password, currentDate));
                numOfUsers++;
            } else {
                listOfUsers.push_back(new Reader(username, password, currentDate));
                numOfUsers++;
            }
        }
        myFile.close();
    } else {
        throw "Users file can not be opened for reading!\n";
    }
}

void Library::addBookFromFile(const std::string &fileName) {
    std::string str;
    std::ifstream myFile;
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()) {
        while (std::getline(myFile, str, '\t')) {
            Book *bookToAdd = new Book();
            bookToAdd->setTitle(str);
            std::getline(myFile, str, '\t');
            bookToAdd->setAuthor(str);
            std::getline(myFile, str, '\t');
            try {
                bookToAdd->setYear(stoi(str));
            }
            catch (...) {
                std::cout << "Invalid string year!\n";
                bookToAdd->setYear(2000);
            }
            std::getline(myFile, str, '\t');
            bookToAdd->setPublisher(str);
            std::getline(myFile, str, '\t');
            bookToAdd->setGenre(str);
            std::getline(myFile, str, '\t');
            bookToAdd->setRating(std::stof(str));
            std::getline(myFile, str, '\t');
            bookToAdd->setShortDescription(str);
            std::getline(myFile, str, '\t');
            bookToAdd->setKeyWords(keyWordsHelper(str));
            std::getline(myFile, str, '\n');
            bookToAdd->setIsbn(str);
            listOfLibItems.push_back(bookToAdd);
            numOfLibItems++;
        }
        myFile.close();
    } else {
        throw "Books file can not be opened for reading!\n";
    }
}

std::vector<Article *> Library::articlesFromFile(int numOfArticles, const std::string &fileName) {
    static int x = 1;
    std::vector<Article *> res;
    std::ifstream myFile;
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()) {
        std::string str;
        while (str != std::to_string(x)) {
            std::getline(myFile, str);
        }
        while (std::getline(myFile, str, '\t') && numOfArticles > 0) {
            Article *article = new Article();
            article->setTitle(str);
            std::getline(myFile, str, '\t');
            article->setAuthor(str);
            std::getline(myFile, str, '\n');
            article->setKeyWords(keyWordsHelper(str));
            numOfArticles--;
            res.push_back(article);
        }
        x++;
    } else {
        throw "Articles file can not be opened for reading!\n";
    }
    return res;
}

void Library::addSeriesFromFile(const std::string &fileName, const std::string &articlesFilename) {
    std::string str;
    std::ifstream myFile;
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()) {
        while (std::getline(myFile, str, '\t')) {
            Series *seriesToAdd = new Series();
            seriesToAdd->setTitle(str);
            std::getline(myFile, str, '\t');
            seriesToAdd->setAuthor(str);
            std::getline(myFile, str, '\t');
            try {
                seriesToAdd->setNum(stoi(str));
            }
            catch (...) {
                std::cout << "Invalid string NUM!It is set to 0!\n";
                seriesToAdd->setNum(0);
            }
            std::getline(myFile, str, '\t');
            seriesToAdd->setPublisher(str);
            std::getline(myFile, str, '\t');
            seriesToAdd->setGenre(str);
            std::getline(myFile, str, '\t');
            seriesToAdd->setRating(std::stof(str));
            std::getline(myFile, str, '\t');
            seriesToAdd->setShortDescription(str);
            std::getline(myFile, str, '\t');
            seriesToAdd->setPublished(stringToDate(str));
            std::getline(myFile, str, '\t');
            seriesToAdd->setKeyWords(keyWordsHelper(str));
            std::getline(myFile, str, '\t');
            try {
                seriesToAdd->setContent(articlesFromFile(std::stoi(str), articlesFilename));
            }
            catch (...) {
                std::cout << "For series: " << seriesToAdd->get_title() << " articles can not be loaded from file!\n";
            }
            std::getline(myFile, str, '\n');
            seriesToAdd->setIsbn(str);

            listOfLibItems.push_back(seriesToAdd);
            numOfLibItems++;
        }
        myFile.close();
    } else {
        throw "Series file can not be opened for reading!\n";
    }
}

void Library::dataLoad(const std::string &uFilename, const std::string &aFileName, const std::string &bFileName,
                       const std::string &sFileName) {
    try {
        addBookFromFile(bFileName);
        addSeriesFromFile(sFileName, aFileName);
        addUsersFromFile(uFilename);
    }
    catch (const std::string &message) {
        std::cout << message;
    }
}

void Library::dataSave(const std::string &uFilename, const std::string &aFileName, const std::string &bFileName,
                       const std::string &sFileName) {
    for (int i = 0; i < numOfUsers; ++i) {
        listOfUsers[i]->writeToFile(uFilename);
    }
    for (int i = 0; i < numOfLibItems; ++i) {
        if (listOfLibItems[i]->type() == typeid(Book).name()) {
            listOfLibItems[i]->writeToFile(bFileName,aFileName);
        } else if (listOfLibItems[i]->type() == typeid(Series).name()) {
            listOfLibItems[i]->writeToFile(sFileName, aFileName);
        }
    }
}