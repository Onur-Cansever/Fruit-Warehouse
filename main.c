//Bu depo maximum 100 kullanıcıyı kaldırabilir.
#include "user.h"


int main() {
    // //read users from users.txt database file
    User * headOfUser = NULL;
    headOfUser = readUsers();
    
    // printf("Welcome to the Fruit Warehouse Program\n");
    // printf("What do you want to do?\n");
    // printf("1- Login\n");
    // printf("2- Register\n");
    // printf("3- Exit\n");
    // int answer;
    // scanf("%d", &answer);
    // switch (answer) {
    // case 1:
    //     headOfUser = lgUser(headOfUser);
    //     break;
    // case 2:
    //     headOfUser = rgUser(headOfUser);
    //     break;
    // case 3:
    //     printf("Have a nice day!");
    //     exit(0);
    //     break;
    
    // default:
    //     break;
    // }
    // //write users to users.txt database file
    // writeUsers(headOfUser);

    headOfUser = lgUser(headOfUser);

    return 0;
}

