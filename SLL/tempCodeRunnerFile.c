
    
    arrayKota dataKota;

    // Alokasi array kota
    printf("Masukkan jumlah kota: ");
    alokasiArray(&dataKota);

    // Input nama kota
    for (int i = 0; i < dataKota.length; i++) {
        printf("Masukkan nama kota ke-%d: ", i + 1);
        scanf("%s", dataKota.kota[i].kt);
        dataKota.kota[i].p = Nil; // Inisialisasi pointer warga ke Nil
    }

    // Menambahkan warga ke kota
    char nama[50], domisili[50];
    char pilihan;
    do {
        printf("Masukkan nama warga: ");
        scanf("%s", nama);
        printf("Masukkan domisili kota: ");
        scanf("%s", domisili);

        addWarga(&dataKota, nama, domisili);

        printf("Apakah ingin menambahkan warga lagi? (y/n): ");
        scanf(" %c", &pilihan);
    } while (pilihan == 'y' || pilihan == 'Y');

    // Cetak daftar masyarakat
    printf("\nDaftar masyarakat:\n");
    printMasyarakat(dataKota);

    // Bebaskan memori yang dialokasikan
    for (int i = 0; i < dataKota.length; i++) {
        address temp = dataKota.kota[i].p;
        while (temp != Nil) {
            address toFree = temp;
            temp = temp->q;
            free(toFree);
        }
    }
    free(dataKota.kota);