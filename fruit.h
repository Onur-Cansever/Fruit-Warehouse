struct fruit {
    char * name;
    char * price;
    struct fruit * next;
};
typedef struct fruit Fruit;

Fruit * addFruit(Fruit * headOfFruit, char * name, char * price);
void printFruits(Fruit * headOfFruit);
Fruit * findFruit(Fruit * headOfFruit, char * name);
Fruit * deleteFruit(Fruit * headOfFruit, char * name);




Fruit * addFruit(Fruit * headOfFruit, char * name, char * price) {
    if(findFruit(headOfFruit, name) != NULL) {
        printf("There is same fruit already.\n");
        return headOfFruit;
    }
    
    if(headOfFruit == NULL) {
        headOfFruit = (Fruit *)malloc(sizeof(Fruit));
        headOfFruit->name = (char*)malloc(sizeof(char) * 32);
        headOfFruit->price = (char*)malloc(sizeof(char) * 32);
        strcpy(headOfFruit->name, name);
        strcpy(headOfFruit->price, price);
        headOfFruit->next = NULL;
        return headOfFruit;
    }else {
        Fruit * iter = headOfFruit;
        while(iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = (Fruit *)malloc(sizeof(Fruit));
        iter->next->name = (char*)malloc(sizeof(char) * 32);
        iter->next->price = (char*)malloc(sizeof(char) * 32);
        iter->next->next = NULL;
        strcpy(iter->next->name, name);
        strcpy(iter->next->price, price);
        return headOfFruit;
    }
};

void printFruits(Fruit * headOfFruit) {
    Fruit * iter = headOfFruit;
    while(iter != NULL) {
        printf("%s-%s\n", iter->name, iter->price);
        iter = iter->next;
    }
}

Fruit * findFruit(Fruit * headOfFruit, char * name) {
    Fruit * iter =  headOfFruit;
    while(iter != NULL) {
        if(strcmp(iter->name, name) == 0) {
            return iter;
        }
        iter = iter->next;
    }
    return iter;
}

Fruit * deleteFruit(Fruit * headOfFruit, char * name) {
    Fruit * temp = findFruit(headOfFruit, name);
    if(temp == NULL) {
        printf("There is no fruit that has a name like %s", name);
    }else {
        if(temp == headOfFruit) {
            headOfFruit = headOfFruit->next;
            temp->next = NULL;
            free(temp);
            printf("Fruit deleted successfully\n");
            return headOfFruit;
        }else{
            Fruit * iter = headOfFruit;
            while(iter->next != temp) {
                iter = iter->next;
            }
            iter->next = temp->next;
            temp->next = NULL;
            free(temp);
            printf("Fruit deleted successfully\n");
            return headOfFruit;
        }
    }
}