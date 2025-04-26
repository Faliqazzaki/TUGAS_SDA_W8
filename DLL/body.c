#include "head.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define Nil NULL

void mainProgram(){
    banner();
    List head; 
    head.first = Nil;
    addKota(&head, "jawa");
    addKota(&head, "sunda");
    addKota(&head, "banten");
    addWarga(&head, "ajet", "jawa");
    addWarga(&head, "farel", "jawa");
    addWarga(&head, "farel", "sunda");
    addWarga(&head, "farel", "banten");
    printMasyarakat(head);
}

addressKota alokasiKota(char *nama){
    addressKota P = (addressKota)malloc(sizeof(kota));
    if(P != Nil){
        strcpy(P->kt, nama);
        P->p = Nil;
        P->next = Nil;
    }else{
        printf("alokasi gagal !!");
    }
    return P;
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

void addKota(List *P, char *domisili){
    addressKota kota = alokasiKota(domisili);
    addressKota prev = Nil;
    addressKota head = (P)->first;
    if(kota != Nil){
        if(head != Nil){
            while((head != Nil) && (strcmp(head->kt, domisili) != 0)){
                prev = head;
                head = head->next;
            }
            if(head == Nil){
                prev->next = kota;
                printf("kota %s berhasil ditambahkan. \n", domisili);
            }else if(strcmp(head->kt, domisili) == 0){
                printf("kota sudah ada....");
            }
        }else{
            (P)->first = kota; 
            printf("\nkota %s berhasil ditambahkan. \n", domisili);
        }
    }else{
        printf("alokasi gagal !!");
    }
}

void addWarga(List *P, char *nama, char *domisili){
    // List (*P) selalu didepan
    address warga = alokasi(nama);
    address prev = Nil;
    addressKota head = (*P).first;
    address headWarga = Nil;
    if( warga == Nil){
        printf("alokasi gagal !!");
        return;
    }
    if(head != Nil){
        while((head != Nil) && (strcmp(head->kt, domisili) != 0)){
            head = head->next;
        }
        
        if(head == Nil){
            printf("input tidak ada kota dalam list\n");
            free(warga);
            return;
        }
        if(strcmp(head->kt, domisili) == 0){
            headWarga = head->p;
            if(headWarga != Nil){
                while((headWarga->q != Nil) && (strcmp(headWarga->nm, nama) != 0)){
                    prev = headWarga;
                    headWarga = headWarga->q;
                }
                if(headWarga->q == Nil){
                    headWarga->q = warga;
                }
                if(strcmp(headWarga->nm, nama) == 0){
                    printf("nama duplikat pada kota %s \n", domisili);
                    return;
                }
            }else{
                head->p = warga;
                headWarga = head->p;
            }
        }
    }else {
        printf("tidak ada kota.....");
        return;
    }

}

void printMasyarakat(List P){
    addressKota tempKota = P.first;
    address temp = Nil;
    if(tempKota != Nil){
        while(tempKota != Nil){
            printf("Kota %s ", tempKota->kt);
            printf("\nWarga : ");
            temp = tempKota->p;
            if(temp != Nil){
                while(temp != Nil){
                    printf("%s - ", temp->nm);
                    temp = temp->q;
                }
                printf("(Nil)");
            }else{
                printf("(Nil)");
            }
            printf("\n");
            tempKota = tempKota->next;
        }
    }else{
        printf("tidak ada kota dan warga");
    }
}


void deleteWarga(List *dataKota, char *nama, char *domisili){

}

void deleteKota(List *dataKota, char *kota){
    addressKota head_kota = (dataKota)->first;
    addressKota prev_kota = Nil;
    address temp_warga = Nil;
    address head_warga = Nil;

    if(head_kota != Nil){
        
    }else{
        printf("Tidak ada data masyarakat yang bisa dihapus..");
    }
}