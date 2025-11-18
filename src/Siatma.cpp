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

int main() {
    Mahasiswa data[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    int pilihanMenu;
    string inputMenu;

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
            cout << "Menu 3 belum tersedia.\n";
            break;

        case 4:
            cout << "Menu 4 belum tersedia.\n";
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
