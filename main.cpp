
#include "Library.h"


int main() {

    Library l;
    l.addUsersFromFile("Users.txt");
    l.addBookFromFile("Books.txt");
    l.addSeriesFromFile("Series.txt");
    l.menu();
    return 0;
}