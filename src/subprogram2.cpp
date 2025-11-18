#include <iostream>
#include <iomanip>
#include <string>
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

        // validasi jumlah semester
        while (data[jumlahMahasiswa].jumlahSemester < 1 ||
               data[jumlahMahasiswa].jumlahSemester > MAX_SEMESTER) {
            cout << "Jumlah semester tidak valid! Masukkan ulang: ";
            cin >> data[jumlahMahasiswa].jumlahSemester;
        }

        // input IPK dgn validasi max 4.00
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

void tampilkanSemuaData(Mahasiswa data[], int jumlahMahasiswa) {
    if (jumlahMahasiswa == 0) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    cout << "\n===============================================================================================================================\n";
    cout << left
         << setw(5)  << "No"
         << setw(12) << "NIM"
         << setw(25) << "Nama"
         << setw(7)  << "S1"
         << setw(7)  << "S2"
         << setw(7)  << "S3"
         << setw(7)  << "S4"
         << setw(7)  << "S5"
         << setw(7)  << "S6"
         << setw(7)  << "S7"
         << setw(7)  << "S8"
         << setw(12) << "Rata-rata"
         << setw(10) << "Tren"
         << endl;
    cout << "===============================================================================================================================\n";

    for (int i = 0; i < jumlahMahasiswa; i++) {
        data[i].rataRata = hitungRataRata(data, i);
        data[i].tren = hitungTren(data, i);

        cout << left
             << setw(5)  << i+1
             << setw(12) << data[i].NIM
             << setw(25) << data[i].nama;

        for (int j = 0; j < MAX_SEMESTER; j++) {
            if (j < data[i].jumlahSemester)
                cout << setw(7) << fixed << setprecision(2) << data[i].ipk[j];
            else
                cout << setw(7) << "-";
        }

        cout << setw(12) << fixed << setprecision(2) << data[i].rataRata
             << setw(10) << data[i].tren
             << endl;

        cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
    }
}


int main() {
    Mahasiswa data[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    int pilihanMenu;

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
        cin >> pilihanMenu;

        switch(pilihanMenu) {
            case 1:
                inputMahasiswa(data, jumlahMahasiswa);
                break;

            case 2:
                tampilkanSemuaData(data, jumlahMahasiswa);
                break;

            case 3:
                cout << "Menu 3 belum tersedia.\n";
                break;

            case 4:
                cout << "Menu 4 belum tersedia.\n";
                break;

            case 0:
                cout << "Terima kasih telah menggunakan SIATMA.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihanMenu != 0);

    return 0;
}