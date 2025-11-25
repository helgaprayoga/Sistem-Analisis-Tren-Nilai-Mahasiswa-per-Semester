#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int MAX_SEMESTER = 8;
const int MAX_MAHASISWA = 100;

struct Mahasiswa {
    string nama;
    string NIM;
    int jumlahSemester;
    float ipk[MAX_SEMESTER];
    float rataRata;
    string tren;
};

void inputMahasiswa(Mahasiswa data[], int &jumlahMahasiswa) {
    char lanjut;

    do {
        if(jumlahMahasiswa >= MAX_MAHASISWA) {
            cout << "Data mahasiswa sudah penuh.\n";
            return;
        }

        cout << "\n=== Input Data Mahasiswa ===\n";

        cout << "Masukkan nama mahasiswa: ";
        cin >> ws;
        getline(cin, data[jumlahMahasiswa].nama);

        cout << "Masukkan NIM: ";
        cin >> data[jumlahMahasiswa].NIM;

        cout << "Masukkan jumlah semester (maks " << MAX_SEMESTER << "): ";
        cin >> data[jumlahMahasiswa].jumlahSemester;

        while (data[jumlahMahasiswa].jumlahSemester < 1 ||
               data[jumlahMahasiswa].jumlahSemester > MAX_SEMESTER) {
            cout << "Jumlah semester tidak valid! Masukkan ulang: ";
            cin >> data[jumlahMahasiswa].jumlahSemester;
        }

        for(int i = 0; i < data[jumlahMahasiswa].jumlahSemester; i++) {
            do {
                cout << "IPK Semester " << i+1 << ": ";
                cin >> data[jumlahMahasiswa].ipk[i];

                if(data[jumlahMahasiswa].ipk[i] < 0 || data[jumlahMahasiswa].ipk[i] > 4.00) {
                    cout << "IPK harus antara 0.00 - 4.00. Silakan input ulang.\n";
                }
            } while(data[jumlahMahasiswa].ipk[i] < 0 || data[jumlahMahasiswa].ipk[i] > 4.00);
        }

        jumlahMahasiswa++;
        cout << "Data mahasiswa berhasil ditambahkan.\n";

        cout << "Tambah mahasiswa lagi? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');
}

float hitungRataRata(Mahasiswa data[], int index) {
    float sum = 0;
    for (int i = 0; i < data[index].jumlahSemester; i++) {
        sum += data[index].ipk[i];
    }
    return sum / data[index].jumlahSemester;
}

string hitungTren(Mahasiswa data[], int index) {
    int naik = 0, turun = 0;

    for (int i = 0; i < data[index].jumlahSemester - 1; i++) {
        if (data[index].ipk[i + 1] > data[index].ipk[i]) {
            naik++;
        } else if (data[index].ipk[i + 1] < data[index].ipk[i]) {
            turun++;
        }
    }

    if (naik == 0 && turun == 0) {
        return "Stagnan";
    } else if (naik > turun) {
        return "Naik";
    } else if (naik < turun) {
        return "Turun";
    } else {
        return "Fluktuatif";
    }
}

void cariSemesterMaxMin(Mahasiswa data[], int index, int &semMax, int &semMin, float &maxIPK, float &minIPK) {
    maxIPK = data[index].ipk[0];
    minIPK = data[index].ipk[0];
    semMax = 1;
    semMin = 1;

    for(int i = 1; i < data[index].jumlahSemester; i++) {
        if(data[index].ipk[i] > maxIPK) {
            maxIPK = data[index].ipk[i];
            semMax = i + 1;
        }
        if(data[index].ipk[i] < minIPK) {
            minIPK = data[index].ipk[i];
            semMin = i + 1;
        }
    }
}

void sortingNIM(Mahasiswa data[], int jumlahMahasiswa) {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        for (int j = 0; j < jumlahMahasiswa - 1 - i; j++) {
            if (data[j].NIM > data[j + 1].NIM) {
                Mahasiswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void tampilkanSemuaData(Mahasiswa data[], int jumlahMahasiswa) {
    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << "\n======================================================================================================================================================================\n";
    cout << left
         << setw(4)  << "No"
         << setw(14) << "NIM"
         << setw(35) << "Nama";

    for (int i = 1; i <= MAX_SEMESTER; i++) {
        cout << setw(8) << ("S" + to_string(i));
    }

    cout << setw(12) << "Rata-rata"
         << setw(10) << "Tren"
         << setw(14) << "Sem Tertinggi"
         << setw(14) << "Sem Terendah"
         << endl;

    cout << "======================================================================================================================================================================\n";

    for (int i = 0; i < jumlahMahasiswa; i++) {
        data[i].rataRata = hitungRataRata(data, i);
        data[i].tren = hitungTren(data, i);

        int semMax, semMin;
        float maxIPK, minIPK;
        cariSemesterMaxMin(data, i, semMax, semMin, maxIPK, minIPK);

        cout << left
             << setw(4)  << i+1
             << setw(14) << data[i].NIM
             << setw(35) << data[i].nama;

        for (int j = 0; j < MAX_SEMESTER; j++) {
            if (j < data[i].jumlahSemester)
                cout << setw(8) << fixed << setprecision(2) << data[i].ipk[j];
            else
                cout << setw(8) << "-";
        }

        cout << left << setw(12) << fixed << setprecision(2) << data[i].rataRata;
        cout << left << setw(12) << data[i].tren;
        cout << left << setw(14) << ("S" + to_string(semMax) + " (" + to_string(maxIPK).substr(0,4) + ")");
        cout << left << setw(14) << ("S" + to_string(semMin) + " (" + to_string(minIPK).substr(0,4) + ")");
        cout << endl;


        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
}

void editMahasiswa(Mahasiswa data[], int index) {
    cout << "\n=== Edit IPK Mahasiswa ===\n";

    cout << "Nama : " << data[index].nama << endl;
    cout << "NIM  : " << data[index].NIM << endl;
    cout << "Jumlah Semester : " << data[index].jumlahSemester << endl;

    cout << "\nIPK saat ini:\n";
    for (int i = 0; i < data[index].jumlahSemester; i++) {
        cout << "Semester " << i+1 << " : " << fixed << setprecision(2) << data[index].ipk[i] << endl;
    }

    int pilihan;
    cout << "\nPilih semester yang ingin diedit (1 - " << data[index].jumlahSemester << ", 0 untuk batal): ";
    cin >> pilihan;

    if (pilihan == 0) {
        cout << "Edit dibatalkan.\n";
        return;
    }

    while (pilihan < 1 || pilihan > data[index].jumlahSemester) {
        cout << "Pilihan tidak valid! Masukkan semester yang benar: ";
        cin >> pilihan;
    }

    float ipkBaru;
    do {
        cout << "Masukkan IPK baru untuk Semester " << pilihan << " (0.00 - 4.00): ";
        cin >> ipkBaru;

        if (ipkBaru < 0.0 || ipkBaru > 4.0)
            cout << "IPK tidak valid, ulangi input.\n";

    } while (ipkBaru < 0.0 || ipkBaru > 4.0);

    data[index].ipk[pilihan - 1] = ipkBaru;

    cout << "IPK semester " << pilihan << " berhasil diperbarui!\n";

    // Update ulang nilai rata-rata & tren
    data[index].rataRata = hitungRataRata(data, index);
    data[index].tren = hitungTren(data, index);

    cout << "Rata-rata baru: " << fixed << setprecision(2) << data[index].rataRata << endl;
    cout << "Tren baru     : " << data[index].tren << endl;
}

void hapusMahasiswa(Mahasiswa data[], int &jumlahMahasiswa, int index) {
    for (int i = index; i < jumlahMahasiswa - 1; i++) {
        data[i] = data[i + 1];
    }
    jumlahMahasiswa--;
    cout << "Data mahasiswa berhasil dihapus.\n";
}

void sequentialSearchNIM(Mahasiswa data[], int &jumlahMahasiswa) {

    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    string nimDicari;

    cout << "\n=== Cari Data Mahasiswa ===\n";
    cout << "Masukkan NIM yang ingin dicari: ";
    cin >> nimDicari;

    int index = -1;

    // Sequential Search
    for (int i = 0; i < jumlahMahasiswa; i++) {
        if (data[i].NIM == nimDicari) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Data mahasiswa dengan NIM " << nimDicari << " tidak ditemukan.\n";
        return;
    }

    // Hitung ulang info
    data[index].rataRata = hitungRataRata(data, index);
    data[index].tren = hitungTren(data, index);

    int semMax, semMin;
    float maxIPK, minIPK;
    cariSemesterMaxMin(data, index, semMax, semMin, maxIPK, minIPK);

    cout << "\n=== Hasil Pencarian ===\n";
    cout << "Nama              : " << data[index].nama << endl;
    cout << "NIM               : " << data[index].NIM << endl;
    cout << "Jumlah Semester   : " << data[index].jumlahSemester << endl;

    cout << "IPK per Semester  : ";
    for (int i = 0; i < data[index].jumlahSemester; i++) {
        cout << fixed << setprecision(2) << data[index].ipk[i] << " ";
    }
    cout << endl;

    cout << "Rata-rata IPK     : " << fixed << setprecision(2) << data[index].rataRata << endl;
    cout << "Tren IPK          : " << data[index].tren << endl;
    cout << "Semester Tertinggi: S" << semMax << " (" << maxIPK << ")\n";
    cout << "Semester Terendah : S" << semMin << " (" << minIPK << ")\n";

    int pilihan;
    cout << "\nApa yang ingin Anda lakukan?\n";
    cout << "1. Edit Data\n";
    cout << "2. Hapus Data\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
    cin >> pilihan;

    if (pilihan == 1) {
        editMahasiswa(data, index);
    } 
    else if (pilihan == 2) {
        hapusMahasiswa(data, jumlahMahasiswa, index);
    }
    else {
        cout << "Kembali ke menu utama.\n";
    }
}

void selectionSortRataRataDescending(Mahasiswa data[], int jumlahMahasiswa) {
    for (int i = 0; i < jumlahMahasiswa - 1; i++) {
        int indexMax = i;

        for (int j = i + 1; j < jumlahMahasiswa; j++) {
            if (data[j].rataRata > data[indexMax].rataRata) {
                indexMax = j;
            }
        }

        if (indexMax != i) {
            Mahasiswa temp = data[i];
            data[i] = data[indexMax];
            data[indexMax] = temp;
        }
    }
}

void menuSortingIPK(Mahasiswa data[], int jumlahMahasiswa) {
    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    // Hitung rata-rata
    for (int i = 0; i < jumlahMahasiswa; i++) {
        data[i].rataRata = hitungRataRata(data, i);
    }

    // Panggil selection sort descending
    selectionSortRataRataDescending(data, jumlahMahasiswa);

    cout << "\nData berhasil di-sorting berdasarkan Rata-rata IPK (Tertinggi ke Terendah).\n";
    tampilkanSemuaData(data, jumlahMahasiswa);
}

int main() {
    Mahasiswa data[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    int pilihanMenu;
    string inputMenu;

    // Dataset Awal
    data[0] = {"Helga Arya Prayoga", "24051130022", 3, {3.8, 3.7, 3.9}, 0, ""};
    data[1] = {"Asya Tiara Syafitrah", "24051130021", 3, {3.5, 3.7, 3.9}, 0, ""};
    data[2] = {"Nadia Omara", "23051130017", 5, {3.2, 3.4, 3.5, 3.2, 3.7}, 0, ""};
    data[3] = {"Arif Syarifuddin", "23051104013", 5, {3.2, 3.5, 3.7, 3.5, 4.0}, 0, ""};
    data[4] = {"Budi Halmahera", "23051130055", 3, {3.0, 3.4, 3.6}, 0, ""};
    data[5] = {"Siti Rahmawati", "23051130062", 4, {3.1, 3.3, 3.2, 3.5}, 0, ""};
    data[6] = {"Agus Prasetyo", "22051120011", 6, {2.9, 3.0, 3.2, 3.3, 3.4, 3.5}, 0, ""};
    data[7] = {"Dewi Lestari", "22051120012", 4, {3.6, 3.7, 3.8, 3.8}, 0, ""};
    data[8] = {"Rama Fadillah", "24051130010", 2, {3.4, 3.6}, 0, ""};
    data[9] = {"Melani Putri", "24051130009", 3, {3.3, 3.4, 3.8}, 0, ""};

    jumlahMahasiswa = 10;

    cout << "============================================\n";
    cout << "     Selamat Datang di SIATMA               \n";
    cout << " Sistem Informasi Analisis Tren Mahasiswa   \n";
    cout << "============================================\n";

do {
    cout << "\n=== Menu Utama ===\n";
    cout << "1. Input Mahasiswa\n";
    cout << "2. Tampilkan Data Mahasiswa\n";
    cout << "3. Cari Data Mahasiswa\n";
    cout << "4. Sorting Mahasiswa berdasarkan Rata-rata IPK\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";

    cin >> inputMenu;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // bersihkan input buffer

    if (inputMenu.length() == 1 && inputMenu[0] >= '0' && inputMenu[0] <= '4') {
        pilihanMenu = inputMenu[0] - '0';
    } else {
        pilihanMenu = -1;
    }

    switch(pilihanMenu) {
        case 1:
            inputMahasiswa(data, jumlahMahasiswa);
            break;

        case 2:
            sortingNIM(data, jumlahMahasiswa);
            tampilkanSemuaData(data, jumlahMahasiswa);
            break;

        case 3:
            sequentialSearchNIM(data, jumlahMahasiswa);
            break;

        case 4:
            menuSortingIPK(data, jumlahMahasiswa);
            break;

        case 0:
            cout << "Terima kasih telah menggunakan SIATMA.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Silakan input menu yang tersedia (0-4).\n";
    }

} while (pilihanMenu != 0);

    return 0;
}
