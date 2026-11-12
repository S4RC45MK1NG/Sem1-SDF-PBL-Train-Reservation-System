#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct SEAT {
    int ticketID;
};

struct CART {
    char type;
    struct SEAT seats[60];
    int cost;
};

struct TRAIN {
    int id;
    char name[100];
    char start[100];
    char dest[100];
    struct CART carts[5];
};

struct TRAIN default_train = { 0, "", "", "", {{ '\0', {{0}}, 0 }} };

// Admin Commands

int write_file() {
    
    FILE *trains = fopen("trains.dat", "wb");
    printf("opened the file.");
    getchar();
    struct TRAIN x = default_train;
    x.id = 1235234;
    strcpy(x.name, "Test Express 1");


    fwrite(&x, sizeof(struct TRAIN), 1, trains);
    printf("Wrote train data into the file.");
    getchar();
    fclose(trains);
    printf("Closed the file");
    getchar();


    return 0;
}

void append_file() {
    struct TRAIN train;
    printf("ID: ");
    scanf("%d", &train.id);
    getchar();
    
    printf("Name: ");
    char chr = 'a';
    int i=0;
    while(chr != '\n') {
        chr = getchar();
        train.name[i] = chr;
        printf("%c", chr);
        i++;
    }
    train.name[i-1] = '\0';

    for (int i=1; i <= 5; i++) {
        int valid = 0;
        while (!valid) {
            printf("Enter type of CART %d\nA (First AC), B (Second AC), C (Third AC), S (Sleeper), G (General)): ", i);
            char temp = toupper(getchar());
            
            
            
            if (temp == 'A' || temp == 'B' || temp == 'C' ||  temp == 'S' ||  temp == 'G') {
                train.carts[i-1].type = temp;
                valid = 1;
            }
            else {
                printf("Invalid type.\n");
                getchar();
            }
        }

        printf("Enter cost per seat: ");
        scanf("%d", &train.carts[i-1].cost);
            
        getchar();
    }


    FILE *trains = fopen("trains.dat", "ab");
    printf("opened file");
    getchar();
    fwrite(&train, sizeof(struct TRAIN), 1, trains);
    printf("appended new data to the file");
    getchar();
    fclose(trains);
    printf("closed the file");
    getchar();
}



void read_file() {
    FILE *trains = fopen("trains.dat", "rb");
    if (trains == NULL) {
        printf("Couldn't open the file\n");
        fclose(trains);
        return;
    }

    printf("opened the file successfully");
    getchar();

    struct TRAIN t1;
    
    while(1 == fread(&t1, sizeof(struct TRAIN), 1, trains)) {
        printf("read the file successfully, data\nName:%s\nID:%d\n", t1.name, t1.id);
        for (int i=0; i<5; i++) {
            printf("CART %d, Type %c\n", i+1, t1.carts[i].type);
            for (int j=0; j<15; j++) {
                printf("Seat %d:%d\t\tSeat %d:%d\t\tSeat %d:%d\t\tSeat %d:%d\n", j+1, t1.carts[i].seats[j].ticketID,  
                                                                            j+15, t1.carts[i].seats[j+15].ticketID,  
                                                                            j+30, t1.carts[i].seats[j+30].ticketID,  
                                                                            j+45, t1.carts[i].seats[j+45].ticketID
                                                                        );
            }
            getchar();
        }
        getchar();
    }
    fclose(trains);


}


int remove_train(int id) {
    FILE *trains = fopen("trains.dat", "rb");
    FILE *temp = fopen("trains.tmp", "wb");
    struct TRAIN t;
    int found = 0;

    if (trains == NULL || temp == NULL) {
        printf("Couldn't open the file.\n");
        if (trains) fclose(trains);
        if (temp) fclose(temp);
        remove("trains.tmp");
        return 0;
    }

    while (fread(&t, sizeof(struct TRAIN), 1, trains) == 1) {
        if (t.id == id) {
            found = 1;
            continue;               /* skip -> effectively deletes it */
        }
        fwrite(&t, sizeof(struct TRAIN), 1, temp);
    }

    fclose(trains);
    fclose(temp);

    if (!found) {
        remove("trains.tmp");       /* nothing changed */
        printf("No train with ID %d found.\n", id);
        return 0;
    }

    remove("trains.dat");
    rename("trains.tmp", "trains.dat");
    printf("Removed train with ID %d.\n", id);
    return 1;
}


// For testing
void cli_menu_loop_admin() {
    int quit = 0;
    while (!quit) {
        int inp = 0;
        struct TRAIN train;
        int id = 0;
        
        printf("enter operation:\n");
        printf("1.append\n2.read\n3.remove\n");
        scanf("%d", &inp);

        switch (inp) {

            case 1:
            append_file();
            break;

            
            case 2:
            read_file();
            break;


            case 3:
            
            printf("Enter train ID: ");
            scanf("%d", &id);
            remove_train(id);
            break;

            default:
            printf("exitting program...");
            quit = 1;
        }

    }
}


int main() {

    cli_menu_loop_admin();

    return 0;
}