#include <iostream>
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

        // Validasi jumlah semester
        while (data[jumlahMahasiswa].jumlahSemester < 1 ||
               data[jumlahMahasiswa].jumlahSemester > MAX_SEMESTER) {
            cout << "Jumlah semester tidak valid! Masukkan ulang: ";
            cin >> data[jumlahMahasiswa].jumlahSemester;
        }

        // Input IPK dengan validasi max 4.00
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
    
    for (int i = 0; i < jumlahMahasiswa; i++) {
        data[i].rataRata = hitungRataRata(data, i);
        data[i].tren = hitungTren(data, i);

        cout << "\nNama : " << data[i].nama << endl;
        cout << "NIM : " << data[i].NIM << endl;

        cout << "IPK : ";
        for (int j = 0; j < data[i].jumlahSemester; j++) {
            cout << data[i].ipk[j] << " ";
        }

        cout << "\nRata - rata : " << data[i].rataRata << endl;
        cout << "Tren Nilai : " << data[i].tren << endl;
        
    }
    
}

int main() {
    Mahasiswa data[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    int pilihanMenu;

    // Opening SIATMA
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
