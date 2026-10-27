#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct TRAIN {
    int id;
    char name[100];
};


int write_file() {
    
    FILE *trains = fopen("trains.dat", "wb");
    printf("opened the file.");
    getchar();
    struct TRAIN x = {5343654, "Sigma Express"};
    fwrite(&x, sizeof(struct TRAIN), 1, trains);
    printf("Wrote train data into the file.");
    getchar();
    fclose(trains);
    printf("Closed the file");
    getchar();


    return 0;
}

void append_file(struct TRAIN x) {
    FILE *trains = fopen("trains.dat", "ab");
    printf("opened file");
    getchar();
    fwrite(&x, sizeof(struct TRAIN), 1, trains);
    printf("appended new data to the file");
    getchar();
    fclose(trains);
    printf("closed the file");
    getchar();
}

void insert_file(struct TRAIN train, int pos) {
    FILE *trains = fopen("trains.dat", "rb+");
    printf("opened the file");
    getchar();

    struct TRAIN *trains_data = (struct TRAIN *) malloc(sizeof(*trains_data));
    int size = 1, count = 0;
    struct TRAIN temp;
    while(fread(&temp, sizeof(struct TRAIN), 1, trains)) {
        count++;
        if(size < count) {
            realloc(trains_data, ++size * sizeof(*trains_data));
            printf("increased size = %d\n", size);
        }

        trains_data[count - 1] = temp;
        printf("read data %d\n", size);

    }
    printf("size of trains_data = %d\n", sizeof(trains_data));
    printf("size of struct = %d\n", sizeof(struct TRAIN));

    printf("===============================================\n");
    printf("===============================================\n");
    for(int i=0; i < size; i++) {
        
        printf("===============================================\n");
        printf("ID:%d\nName:%s", trains_data[i].id, trains_data[i].name);
        printf("\n===============================================");
        getchar();
    }
    printf("\n===============================================");

    printf("\n\n\n");
    struct TRAIN *updated_data = (struct TRAIN *) malloc(++size * sizeof(*trains_data));
    int counter = 0, i=0;
    while(counter < size) {
        if (i == pos) {
            updated_data[counter] = train;
            counter++;
            printf("inserted the target value at pos %d\n", counter-1);
        }
    
        updated_data[counter] = trains_data[i];
        printf("normally inserted value at pos %d\n", counter);
    
        counter++; i++;
    }
    
    printf("===============================================\n");
    printf("===============================================\n");
    for(int i=0; i < size; i++) {
        
        
        printf("ID:%d\nName:%s", updated_data[i].id, updated_data[i].name);
        printf("\n===============================================");
        getchar();
    }
    printf("\n===============================================");
    
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
        printf("read the file successfully, data\nName:%s\nID:%d", t1.name, t1.id);
        getchar();
    }
    fclose(trains);


}


// For testing
void cli_menu_loop() {
    int quit = 0;
    while (!quit) {
        int inp = 0;
        struct TRAIN temp;
        int pos = 0;
        
        printf("enter operation:\n");
        printf("1.append\n2.read\n3.insert\n");
        scanf("%d", &inp);

        switch (inp) {

            case 1:
            printf("ID: ");
            scanf("%d", &temp.id);
            getchar();
            printf("Name: ");
            char chr = 'a';
            int i=0;
            while(chr != '\n') {
                chr = getchar();
                temp.name[i] = chr;
                printf("%c", chr);
                i++;
            }
            temp.name[i-1] = '\0';
            
            append_file(temp);
            break;

            
            case 2:
            read_file();
            break;


            case 3:
            printf("ID: ");
            scanf("%d", &temp.id);
            printf("Name: ");
            scanf("%d", temp.name);
            printf("Position: ");
            scanf("%d", &pos);            
            
            insert_file(temp, pos);
            break;
            
            default:
            printf("exitting program...");
            quit = 1;
        }

    }
}


int main() {
    write_file();
    cli_menu_loop();

    return 0;
}