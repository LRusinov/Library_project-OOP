#include "Library.h"

int main() {
    Library l;
    l.dataLoad("Users.txt", "Articles.txt", "Books.txt", "Series.txt");
    l.menu();

    return 0;
}