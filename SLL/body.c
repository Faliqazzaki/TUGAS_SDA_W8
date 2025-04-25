#include "head.h"
#include <malloc.h>
#include <string.h>
#define Nil NULL

void alokasiArray(arrayKota *P){
    scanf("%d", &(*P).length);
    (*P).kota = malloc(sizeof(kota) * (*P).length);
}

address alokasi(char *nama){
    address P = (address)malloc(sizeof(warga));
    if(P != Nil){
        strcpy(P->nm, nama);
        P->q = Nil;
    }else{
        printf("alokasi gagal !!");
    }
    return P;
}

void addWarga(arrayKota *P, char *nama, char *domisili){
    address warga = alokasi(nama);
    int i = 0;
    address temp;
    if(warga != Nil){
        while(strcmp((*P).kota[i].kt, domisili) != 0){
            if(strcmp((*P).kota[i].kt, domisili) == 0){
                break;
            }
            i++;
        }
        // terjadi jika tidak ada sebuah kota

        if(i >= (*P).length){
            printf("tidak ada kota !!!");
            return;
        }else{
            // terjadi jika terdapat sebuah kota 
            temp = (*P).kota[i].p;
            if(temp != Nil){
                while(temp->q != Nil){
                    temp = temp->q;
                }   
                temp->q = warga;
            }else{
                (*P).kota[i].p = warga;
            }
        }
    }else{
        printf("alokasi gagal !!");
        return;
    }
}

void printMasyarakat(arrayKota P){
    int i;
    address temp;
    if(P.kota != Nil){
        i = 0;
        while(i < P.length){
            printf("Kota %d : %s", i+1, P.kota[i].kt);
            printf("\nWarga : ");
            temp = P.kota[i].p;
            if(temp != Nil){
                while(temp != Nil){
                    printf("%s , ", temp->nm);
                    temp = temp->q;
                }
            }else{
                printf("(Nil)");
            }
            printf("\n");
            i++;
        }
    }else{
        printf("tidak ada kota dan warga");
    }
}

void banner(){
    printf("===============================================================\n");
    printf("    ___                         _          _____ _      _     \n");
    printf("   / _ \\                       | |        /  ___| |    | |    \n");
    printf("  / /_\\ \\_ __ _ __ __ _ _   _  | |_ ___   \\ `--.| |    | |    \n");
    printf("  |  _  | '__| '__/ _` | | | | | __/ _ \\   `--. \\ |    | |    \n");
    printf("  | | | | |  | | | (_| | |_| | | || (_) | /\\__/ / |____| |__  \n");
    printf("  \\_| |_/_|  |_|  \\__,_|\\__, |  \\__\\___/  \\____/\\_____/\\_____/\n");
    printf("                         __/ |                                \n");
    printf("                        |___/                                 \n");
    printf("===============================================================");
}