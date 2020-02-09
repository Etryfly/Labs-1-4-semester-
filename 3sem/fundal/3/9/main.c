

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define SIZE_OF_NAMES 150

typedef struct a {
    char* city;
    char* street;
    int house;
    int block;
    int index;
} Address;

typedef struct m {
    Address* address;
    int id;
} Mail;

typedef struct Post {
    Address address;
    Mail* mails;
} Post;

Mail* createMail(int id, Address* address) {
    Mail *mail = malloc(sizeof(Mail));
    mail->address = address;
    mail->id = id;
    return mail;
}

void sortMailByIdAndIndex(Mail* mails, int size) {
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; ++j) {
            if (mails[j].address->index > mails[j + 1].address->index) {
                Mail tmp = mails[j];
                mails[j] = mails[j + 1];
                mails[j + 1] = tmp;
            } else if (mails[j].address->index == mails[j + 1].address->index) {
                if (mails[j].id > mails[j + 1].id) {
                    Mail tmp = mails[j];
                    mails[j] = mails[j + 1];
                    mails[j + 1] = tmp;
                }
            }
        }
    }
}

Address* createAddress(char *city, char *street, int house, int block, int index) {
    Address* address = malloc(sizeof(Address));
    address->city = city;
    address->street = street;
    address->house = house;
    address->block = block;
    address->index = index;
    return address;
}

int main() {
    Post* post = malloc(sizeof(Post));
    printf("Enter address of post IN format: City Street House Block Index");
    char bufCity[SIZE_OF_NAMES];
    char bufStreet[SIZE_OF_NAMES];
    int house;
    int block;
    int index;
    scanf("%s %s %d %d %d", bufCity, bufStreet, &house, &block, &index);
    char* city = malloc(sizeof(char) * (strlen(bufCity)+1));
    char* street = malloc(sizeof(char) * (strlen(bufStreet)+1));
    strcpy(city, bufCity);
    strcpy(street, bufStreet);
    Address *postAddress = createAddress(city, street, house, block, index);
    post->address = *postAddress;

    int sizeOfMails = 5;
    int curSizeOfMails = 0;

    Mail* mails = malloc(sizeof(Mail) * sizeOfMails);
    int id = 0;
    post->mails = mails;
    int chose = -1;
    while (chose != 5) {
        chose = -1;
        printf("1. Добавление\n"
               "2. Удаление\n"
               "3. Поиск по ID\n"
               "4. Просмотр mail\n"
               "5. Выход\n");
        scanf("%d", &chose);
//        Mail* ptr = post->mails;
        switch (chose) {
            case 1:
                if (curSizeOfMails == sizeOfMails) {
                    sizeOfMails *= 2;
                    post->mails = realloc(post->mails, sizeof(Mail) * sizeOfMails);
                }
                printf("City Street House Block Index\n");
                scanf("%s %s %d %d %d", bufCity, bufStreet, &house, &block, &index);
                city = malloc(sizeof(char) * (strlen(bufCity)+1));
                street = malloc(sizeof(char) * (strlen(bufStreet)+1));
                strcpy(city, bufCity);
                strcpy(street, bufStreet);
                Address *addr = createAddress(city, street, house, block, index);

                (post->mails + curSizeOfMails)->address = addr;
                (post->mails + curSizeOfMails)->id = id++;
                curSizeOfMails ++;
                sortMailByIdAndIndex(mails, curSizeOfMails);
                break;
            case 2:
                printf("Enter ID\n");
                int id;
                scanf("%d", &id);
                for (int j = 0; j < curSizeOfMails; ++j) {
                    if (curSizeOfMails != 1) {
                        if (post->mails[j].id == id) {
                            for (int i = j; i < curSizeOfMails - 1; ++i) {
                                post->mails[j] = post->mails[j + 1];
                            }
                            curSizeOfMails --;
                            break;

                        }
                    } else {
                        curSizeOfMails = 0;
                    }
                }
                break;

            case 3:
                printf("Enter ID\n");
                scanf("%d", &id);
                for (int j = 0; j < curSizeOfMails; ++j) {
                    if (post->mails[j].id == id) {
                        printf("ID | City | Street | House | Block | Index\n");

                        Mail curMail = post->mails[j];
                        printf("%d | %s | %s | %d | %d | %d\n", curMail.id, curMail.address->city, curMail.address->street,
                               curMail.address->house, curMail.address->block, curMail.address->index);
                        break;
                    }
                }
                break;


            case 4:
                printf("ID | City | Street | House | Block | Index\n");
                for (int i = 0; i < curSizeOfMails; ++i) {
                    Mail curMail = post->mails[i];
                    printf("%d | %s | %s | %d | %d | %d\n", curMail.id, curMail.address->city, curMail.address->street,
                           curMail.address->house, curMail.address->block, curMail.address->index);
                }
                break;
            case 5:
                return 0;
        }



    }


}