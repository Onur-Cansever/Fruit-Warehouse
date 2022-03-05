//Bu depo maximum 100 kullanıcıyı kaldırabilir.
#include "user.h"


int main() {
    //read Users from users.txt database txt file.
    User * headOfUser = NULL;
    headOfUser = readUsers();
    
    while(1) {
        printf("Welcome to the Fruit Warehouse Program\n");
        printf("What do you want to do?\n");
        printf("1- Login\n");
        printf("2- Register\n");
        printf("3- Exit\n");
        int answer;
        scanf("%d", &answer);
        if(answer == 1) {
            headOfUser = lgUser(headOfUser);
        }else if(answer == 2) {
            headOfUser = rgUser(headOfUser);
        }else if(answer == 3) {
            printf("Have a nice day!");
            break;
        }
    }

    //write users to users.txt database txt file
    writeUsers(headOfUser);
    return 0;
}

