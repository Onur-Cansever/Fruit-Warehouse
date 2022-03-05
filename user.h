#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fruit.h"

struct user {
    char * username;
    char * password;
    struct fruit * warehouse;
    struct user * next;
};
typedef struct user User;

User * addUser(User * headOfUser, char * username, char * password) {
    if(headOfUser == NULL) {
        headOfUser = (User *)malloc(sizeof(User));
        headOfUser->username = (char*)malloc(sizeof(char) * 32);
        strcpy(headOfUser->username, username);
        headOfUser->password = (char*)malloc(sizeof(char) * 32);
        strcpy(headOfUser->password, password);
        headOfUser->warehouse = NULL;
        headOfUser->next = NULL;
    }else{
        User * iter = headOfUser;
        while(iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = (User *)malloc(sizeof(User));
        iter->next->username = (char*)malloc(sizeof(char) * 32);
        strcpy(iter->next->username, username);
        iter->next->password = (char*)malloc(sizeof(char) * 32);
        strcpy(iter->next->password, password);
        iter->next->warehouse = NULL;
        iter->next->next = NULL;
    }
    return headOfUser;
};

//read Users from users.txt databse file
User * readUsers() {
    FILE * fp = fopen("users.txt", "r");
    
    if(fp == NULL) {
        return NULL;
    }else{
        User * headOfUser = NULL;
        char * username = (char*)malloc(sizeof(char) * 32);
        char * password = (char*)malloc(sizeof(char) * 32);
        char * line = (char*)malloc(sizeof(char) * 65);
        
        //check the file is empty or not ? 
        if(fscanf(fp, "%s", line) == -1) {
            return headOfUser;
        }
        fseek(fp, 0, SEEK_SET);
        while(1) {
            if(feof(fp)) break;
            fscanf(fp, "%s", line);


            //split the line as username and password
            //and decode username and password
            int sayac1 = 0, sayac2 = 0;
            while(line[sayac1] != '-') {
                username[sayac1] = line[sayac1] - 1;
                sayac1++;
            }
            sayac1++;
            while(line[sayac1] != '\0') {
                password[sayac2] = line[sayac1] - 1;
                sayac1++; sayac2++;
            }
            //-----

            
            headOfUser = addUser(headOfUser, username, password);
            memset(username, '\0', 32);
            memset(password, '\0', 32);
        }
        
        fclose(fp);
        return headOfUser;
    }
}

User * findUser(User * headOfUser, char * username) {
    User * iter = headOfUser;
    while(iter != NULL) {
        if(strcmp(iter->username, username) == 0) {
            return iter;
        }else {
            iter = iter->next;
        }
    }
    return NULL; 
}

//printUsers
void printUsers(User * headOfUser) {
    User * iter = headOfUser;
    while(iter != NULL) {
        printf("%s-%s\n", iter->username, iter->password);
        iter = iter->next;
    }
}


//deleteUser
User * deleteUser(User * headOfUser, char * username) {
    if(findUser(headOfUser, username) == NULL) {
        printf("%s isimli kullanici zaten sistemde yoktur.\n", username);
        return headOfUser;
    }else{
        User * iter = headOfUser;
        User * temp;
        if(strcmp(headOfUser->username, username) == 0) {
            temp = headOfUser;
            headOfUser = headOfUser->next;
            temp->next = NULL;
            free(temp);
            return headOfUser;
        }
        while(strcmp(iter->next->username, username) != 0) {
            iter = iter->next;
        }
        if(iter->next->next != NULL) {
            temp = iter->next;
            iter->next = iter->next->next;
            temp->next = NULL;
            free(temp);
            return headOfUser;
        }else{
            temp = iter->next;
            iter->next = NULL;
            free(temp);
            return headOfUser;
        }
    }
}


//write Users to users.txt database file
void writeUsers(User * headOfUser) {
    FILE * fp = fopen("users.txt", "w");
    if(fp == NULL) {
        printf("Hata: Dosya yazma korumalidir.");
    }else{
        User * iter = headOfUser;
        while(iter != NULL) {

            //encode the line
            int i = 0;
            while(iter->username[i] != '\0') {
                (iter->username)[i++] += 1;
            }
            i = 0;
            while(iter->password[i] != '\0') {
                (iter->password)[i++] += 1;
            }
            //encode the line


            fprintf(fp, "%s-%s", iter->username, iter->password);
            if(iter->next != NULL) {
                iter = iter->next;
                fprintf(fp, "\n");
            }else {
                break;
            }
        }
        fclose(fp);
    }
}

User * rgUser(User * headOfUser) {
    char * username = (char*)malloc(sizeof(char) * 32);
    char * password = (char*)malloc(sizeof(char) * 32);
    char * temp = (char*)malloc(sizeof(char) * 32);

    printf("Please enter your username: ");
    scanf("%s", username);
    printf("Please enter your username again: ");
    scanf("%s", temp);
    if(strcmp(username, temp) == 0) {
        if(!findUser(headOfUser, username)) {
            memset(temp, '\0', 32);
            printf("Please enter your password: ");
            scanf("%s", password);
            printf("Please enter your password again: ");
            scanf("%s", temp);
            if(strcmp(password, temp) == 0) {
                headOfUser = addUser(headOfUser, username, password);
                printf("Registiration successfull\n");
                return headOfUser;
            }else {
                printf("Password is not verified correctly. Please try again.\n");
                return headOfUser;
            }
            
            
            return headOfUser;
        }else{
            printf("There is already user that have a same username\n");
            return headOfUser;
        }
        
    }else {
        printf("Usernames is not verified correctly. Please try again.\n");
        return headOfUser;
    }
}


Fruit * readFruitDB(char * username, Fruit * headOfFruit) {
    FILE * fp = fopen(username, "r");
    if(fp == NULL) {
        return headOfFruit;
    }else{
        char * name = (char*)malloc(sizeof(char) * 32);
        char * price = (char*)malloc(sizeof(char) * 32);
        char * line = (char*)malloc(sizeof(char) * 65);
        
        //check the file is empty or not ? 
        if(fscanf(fp, "%s", line) == -1) {
            return headOfFruit;
        }
        fseek(fp, 0, SEEK_SET);


        while(1) {
            if(feof(fp)) break;

            memset(name, '\0', 32);
            memset(price, '\0', 32);

            fscanf(fp, "%s", line);

            //split the line as username and password  by watching the decoding
            int sayac1 = 0, sayac2 = 0;
            while(line[sayac1] != '-') {
                name[sayac1] = line[sayac1] - 1;
                sayac1++;
            }
            sayac1++;
            while(line[sayac1] != '\0') {
                price[sayac2] = line[sayac1] - 1;
                sayac1++; sayac2++;
            }
            //-----
            
            headOfFruit = addFruit(headOfFruit, name, price);
        }
    }
    return headOfFruit;
}

Fruit * addFruitDB(Fruit * headOfFruit) {
    char * name = (char*)malloc(sizeof(char) * 32);
    char * price = (char*)malloc(sizeof(char) * 32);

    printf("Fruit name: ");
    scanf("%s", name);
    printf("Fruit's price: ");
    scanf("%s", price);
    
    headOfFruit = addFruit(headOfFruit, name, price);
    return headOfFruit;
}

Fruit * deleteFruitDB(Fruit * headOfFruit) {
    char * name = (char*)malloc(sizeof(char) * 32);

    printf("Fruit name: ");
    scanf("%s", name);

    headOfFruit = deleteFruit(headOfFruit, name);
    return headOfFruit;
}

Fruit * writeFruitDB(char * username, Fruit * headOfFruit) {
    FILE * fp = fopen(username, "w");
    if(fp == NULL) {
        printf("Hata: Cannot write data to file.");
    }else{
        Fruit * iter = headOfFruit;
        while(iter != NULL) {

            //encode the line
            int i = 0;
            while(iter->name[i] != '\0') {
                (iter->name)[i++] += 1;
            }
            i = 0;
            while(iter->price[i] != '\0') {
                (iter->price)[i++] += 1;
            }
            //encode the line


            fprintf(fp, "%s-%s", iter->name, iter->price);
            if(iter->next != NULL) {
                iter = iter->next;
                fprintf(fp, "\n");
            }else {
                break;
            }
        }
        fclose(fp);
    }
}

Fruit * updateFruit(Fruit * headOfFruit) {
    char * name = (char*)malloc(sizeof(char) * 32);
    char * price = (char*)malloc(sizeof(char) * 32);
    Fruit * temp;

    printf("What do you want to update ? Please choose fruit name or price. \n");
    printf("1- update fruit's name\n");
    printf("2- update fruit's price\n");
    int answer = 0;
    scanf("%d", &answer);
    switch (answer) {
        case 1:
            printf("Please enter your fruit name to update its name:");
            scanf("%s", name);
            temp = findFruit(headOfFruit, name);
            if(temp == NULL) {
                printf("There is no name in fruit database.");
            }else {
                printf("Please enter your new fruit name:");
                scanf("%s", name);
                strcpy(temp->name, name);
                printf("Updated fruit name successfully");
            }
            break;
        case 2:
            printf("Please enter your fruit name to update its price:");
            scanf("%s", name);
            temp = findFruit(headOfFruit, name);
            if(temp == NULL) {
                printf("There is no name in fruit database.");
            }else {
                printf("Please enter your price value:");
                scanf("%s", price);
                strcpy(temp->price, price);
                printf("Updated fruit's price successfully");
            }
            break;
    }

    return headOfFruit;
}




User * lgUser(User * headOfUser) {
    char * username = (char*)malloc(sizeof(char) * 32);
    char * password = (char*)malloc(sizeof(char) * 32);

    printf("Please enter your username: ");
    scanf("%s", username);
    User * temp = findUser(headOfUser, username);
    if(temp == NULL) {
        printf("There is no user that registered the system");
        return headOfUser;
    }else {
        printf("Please enter your password: ");
        scanf("%s", password);
        
        if(strcmp(temp->password, password) == 0) {
            while(1) {
                printf("\nLogin successfull. What do you want do?");
                printf("\n1- update my username\n");
                printf("2- update my password\n");
                printf("3- delete my account\n");
                printf("4- show fruit database\n");
                printf("5- add fruit to the database\n");
                printf("6- delete fruit from database\n");
                printf("7- update fruit from database\n");
                printf("8- log out\n\n");
            
                int answer = 0;
                scanf("%d", &answer);
                if(answer == 1) {
                    char * temp2 = (char*)malloc(sizeof(char) * 32);

                    printf("Please enter your new username: ");
                    scanf("%s", username);
                    printf("Please enter your new username again: ");
                    scanf("%s", temp2);

                    if(strcmp(username, temp2) == 0) {
                        strcpy(temp->username, username);
                        printf("updated username successfully\n");
                    }else {
                        printf("New username is not verified correctly. Please try again.\n");
                    }
                    return headOfUser;
                }else if(answer == 2) {
                    char * temp2 = (char*)malloc(sizeof(char) * 32);

                    printf("Please enter your new password: ");
                    scanf("%s", password);
                    printf("Please enter your new password again: ");
                    scanf("%s", temp2);

                    if(strcmp(password, temp2) == 0) {
                        strcpy(temp->password, password);
                        printf("Updated password successfully\n");
                    }else {
                        printf("New password is not verified correctly. Please try again.\n");
                    }
                    return headOfUser;
                }else if(answer == 3) {
                    printf("Your account deleted successfully, have a nice day.\n");
                    headOfUser = deleteUser(headOfUser, temp->username);
                    return headOfUser;
                }else if(answer >= 4 && answer <= 6) {
                    //read the fruit database if it hasn't rode.
                    if(temp->warehouse == NULL) {
                        temp->warehouse = readFruitDB(temp->username, temp->warehouse);
                    }
                    if(answer == 4) {
                        printf("--- Your Fruit Database ---\n");
                        printFruits(temp->warehouse);
                    }else if(answer == 5) {
                        temp->warehouse = addFruitDB(temp->warehouse);
                    }else if(answer == 6) {
                        temp->warehouse = deleteFruitDB(temp->warehouse);
                    }  
                }else if(answer == 7) {
                    temp->warehouse = updateFruit(temp->warehouse);
                }else if(answer == 8) {
                    printf("Log out successfull!");
                    writeFruitDB(temp->username, temp->warehouse);
                    free(temp->warehouse);
                    temp->warehouse = NULL;
                    return headOfUser;
                }
            }
        }else {
            printf("Wrong password. Please try again.\n");
            return headOfUser;
        }
    }
}