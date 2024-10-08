//Nama: Audric Nagata
//NIM: 2602090435
//Kelas: LA-20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data{
    char make[100]; //variabel untuk merk mobil
    char model[100]; //variabel untuk model mobil
    char year[100]; // variabel untuk tahun produksi mobil
    char mileage[100]; // variabel untuk kilometer pemakaian mobil
    char engine[100]; //variabel untuk kapasitas mesin
} car[100]; //struct disimpan dalam array karena setiap variabel akan memiliki data yang berbeda

int idx = 1; //variabel untuk menentukan baris keberapa di dalam file

void login(){ //fungsi login
    char user[100]; //variabel username
    char pass[100]; //variabel password
    int x, y, n = 1; 
    
    
    do{
        printf("Username: ");
        scanf("%[^\n]", user); getchar(); //input username
        
        printf("Password: ");
        scanf("%s", pass); // input password
        
        x = strcmp(user, "admin"); // username dan password di set admin sebagai dummy
        y = strcmp(pass, "admin"); // pembandingan antara username dan password yang diinput dengan admin
        
        if(x == 0 && y == 0){ //apabila input sama dengan admin,
            
            printf("\nSucessfully Logged In\n\n");
            getchar();
            break;
            
        } else{ //apabila berbeda
            
            printf("\nWrong Password, try again\n");
            getchar();
            n++;
        }
        
        if (n>5){ //apabila lebih dari lima kali kesalahan

            printf("\nAccess Denied");
            getchar();
            exit(1);
        }
        
    } while (n<=5);
}

void create(){ //fungsi penambahan data
    FILE *f;
    
    f = fopen("sales.txt", "a+"); //buka file sales.txt dengan mode append
    
    printf("Make: ");
    scanf("%[^\n]", car[idx].make); getchar(); //input merk mobil
    
    printf("Model: ");
    scanf("%[^\n]", car[idx].model); getchar(); //input model mobil
    
    printf("Year: ");
    scanf("%s", car[idx].year); getchar(); //input tahun produksi mobil
    
    printf("Mileage: ");
    scanf("%s", car[idx].mileage); getchar(); //input kilometer pemakaian mobil
    
    printf("Engine: ");
    scanf("%s", car[idx].engine); getchar(); //input kapasitas mesin
    
    fprintf(f, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", car[idx].make, car[idx].model, car[idx].year, car[idx].mileage, car[idx].engine); //print di dalam file sales.txt
    
    idx++; //index bertambah
    
    fclose(f); //tutup file
    
}

void read(){ //fungsi membaca file
    FILE *f;
    char line[1000]; //deklarasi variabel untuk di print di terminal
    
    f = fopen("sales.txt", "r"); //buka sales.txt dengan mode read
        
    while(fgets(line, sizeof(line), f) != NULL){ //selama baris pada file yang di scan oleh program tidak sama dengan null,
     
        printf("%s", line); //maka program akan print per baris
        
    }
    
    
    fclose(f); //tutup file
}

void update(){ //fungsi pengubah data
    FILE *f;
    int a; //deklarasi index
    
    f = fopen("sales.txt", "w"); //buka sales.txt dengan mode write
    
    printf("Please input the index you want to update: ");
    scanf("%d", &a); getchar(); //input index yang mau di ubah
    
    printf("Make: ");
    scanf("%[^\n]", car[a - 1].make); getchar(); //input merk mobil baru
    
    printf("Model: ");
    scanf("%[^\n]", car[a - 1].model); getchar(); //input model mobil baru
    
    printf("Year: ");
    scanf("%s", car[a - 1].year); getchar(); //input tahun produksi mobil baru
    
    printf("Mileage: ");
    scanf("%s", car[a - 1].mileage); getchar(); //input kilometer pemakaian mobil baru
    
    printf("Engine: ");
    scanf("%s", car[a - 1].engine); getchar(); //input kapasitas mesin baru
    
    for (int i = 0; i < idx; i++){
     
        fprintf(f, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", car[i].make, car[i].model, car[i].year, car[i].mileage, car[i].engine); //print ulang pada sales.txt setelah index tersebut diubah
        
    }
    
    fclose(f); //tutup file
}

void delete(){ //fungsi menghapus data
    FILE *f;
    
    f = fopen("sales.txt", "w"); //buka sales.txt dengan mode write
    
    int n; //deklarasi index yang mau di delete

    printf("Please input the index you want to delete: ");
    scanf("%d", &n); //input index
    
    for (int i = n - 1; i < idx; i++){
        
        car[i] = car[i + 1]; //pemindahan seluruh baris setelah index n dengan n
        
    }
    
    idx--; //index dikurangi

    for (int i = 0; i < idx; i++){
        
        fprintf(f, "%s\t\t%s\t\t%s\t\t%s\t\t%s\n", car[i].make, car[i].model, car[i].year, car[i].mileage, car[i].engine); //print ulang seluruh data di dalam file
        
    }
    
    fclose(f); //tutup file
}

void search(){ //fungsi mencari data
    
    char brand[100]; //deklarasi variabel merk
    char line[1000]; //deklarasi variabel penyimpanan
    
    printf("Search for the brand you're looking: ");
    scanf("%[^\n]", brand); //input merk yang dicari
    
    printf("Make\t\tModel\t\tYear\t\tMileage\t\tEngine\n");
    
    FILE *f;
    
    f = fopen("sales.txt", "r"); //buka sales.txt dengan mode read
    
    for (int i = 0; i < idx; i++){
        
        while (fgets(line, sizeof(line), f) != NULL){ //selama data yang dibaca bukan NULL,
        
            if (strstr(line, brand) != NULL){ //dan brand serta line memiliki kata yang sama,
            
                printf("%s", line); //maka terminal akan menunjukkan data yang dicari
            
            }
        }
    }
    
    fclose(f); //tutup file
    
}

int main()
{
    int menu;
    char ex;
    
    printf("===================================\n");
    printf("Welcome to Car's Dealer\n");
    printf("===================================\n");
    printf("Please login to continue\n");
    
    login(); //pemanggilan fungsi login
    
    do{
        printf("Menu\n");
        printf("1. Create data\n");
        printf("2. Read data\n");
        printf("3. Update data\n");
        printf("4. Delete data\n");
        printf("5. Search data\n");
        
        printf("Please pick your choice: ");
        scanf("%d", &menu); getchar(); //input angka untuk menuju fitur yang diperlukan
        
        printf("\n");
    
        switch(menu){ //apabila memilih angka diantara 1 - 5
            case 1:
                create(); //pemanggilan fungsi create
                printf("Your entry has been saved!\n");
                break;
            case 2:
                printf("Make\t\tModel\t\tYear\t\tMileage\t\tEngine\n");
                read(); //pemanggilan fungsi read
                break;
            case 3:
                update(); //pemanggilan fungsi update
                printf("Your update has been saved!\n");
                break;
            case 4:
                delete(); //pemanggilan fungsi delete
                printf("Your data has been deleted!\n");
                break;
            case 5:
                search(); getchar(); //pemanggilan fungsi search
                break;
            default:
                printf("Please pick between 1 to 5\n");
        }
        printf("\n");
        printf("Do you want to exit the program? (Y/N)");
        scanf("%c", &ex); //apakah ingin keluar dari program?
        
    }while (ex == 'N' || ex == 'n'); //apabila n, maka akan keluar dari program.
    
    return 0;
}
