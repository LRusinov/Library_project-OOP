#include<iostream>
#include <fstream>
#include "Library.h"
#include "Test.h"

int main() {

    Library l;
    // Test::dataLoad(l);
    //Test::funcTests(l);
    //l.menu();
l.addUsersFromFile("Users.txt");
    l.menu();
    return 0;
}