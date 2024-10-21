#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Kelas dasar untuk Aset
class Aset {
public:
    string nama;
    string jenis;
    int kuantitas;
    double harga;

    Aset(string nama, string jenis, int kuantitas, double harga)
        : nama(nama), jenis(jenis), kuantitas(kuantitas), harga(harga) {}

    virtual ~Aset() {}
    virtual void cetakInfo() = 0;
};

// Kelas untuk Saham
class Saham : public Aset {
public:
    double pertumbuhan;
    double dividen;

    Saham(string nama, int kuantitas, double harga, double pertumbuhan, double dividen)
        : Aset(nama, "saham", kuantitas, harga), pertumbuhan(pertumbuhan), dividen(dividen) {}

    void cetakInfo() override {
        cout << "Nama: " << nama << endl;
        cout << "Jenis: Saham" << endl;
        cout << "Kuantitas: " << kuantitas << endl;
        cout << "Harga: " << harga << endl;
        cout << "Pertumbuhan: " << pertumbuhan << "%" << endl;
        cout << "Dividen: " << dividen << "%" << endl;
    }
};

// Kelas untuk Obligasi
class Obligasi : public Aset {
public:
    double bunga;
    int maturitas;

    Obligasi(string nama, int kuantitas, double harga, double bunga, int maturitas)
        : Aset(nama, "obligasi", kuantitas, harga), bunga(bunga), maturitas(maturitas) {}

    void cetakInfo() override {
        cout << "Nama: " << nama << endl;
        cout << "Jenis: Obligasi" << endl;
        cout << "Kuantitas: " << kuantitas << endl;
        cout << "Harga: " << harga << endl;
        cout << "Bunga: " << bunga << "%" << endl;
        cout << "Maturitas: " << maturitas << " tahun" << endl;
    }
};

// Fungsi untuk menghitung total valuasi portofolio
double hitungTotalValuasi(const vector<Aset*>& daftarAset) {
    double totalValuasi = 0;
    for (Aset* aset : daftarAset) {
        totalValuasi += aset->kuantitas * aset->harga;
    }
    return totalValuasi;
}

// Fungsi untuk mencetak daftar aset
void cetakDaftarAset(const vector<Aset*>& daftarAset) {
    if (daftarAset.empty()) {
        cout << "Daftar aset kosong." << endl;
        return;
    }
    for (Aset* aset : daftarAset) {
        aset->cetakInfo();
        cout << "-------------------------------------" << endl;
    }
}

int main() {
    vector<Aset*> daftarAset;
    int banyakAset;

    // Input jumlah aset yang akan dilacak
    cout << "Masukkan jumlah aset: ";
    cin >> banyakAset;

    // Input data aset berdasarkan jenisnya
    for (int i = 0; i < banyakAset; ++i) {
        string nama, jenis;
        int kuantitas;
        double harga;

        cout << "Masukkan nama, jenis (saham/obligasi), kuantitas, dan harga: ";
        cin >> nama >> jenis >> kuantitas >> harga;

        if (jenis == "saham") {
            double pertumbuhan, dividen;
            cout << "Masukkan pertumbuhan (%) dan dividen (%): ";
            cin >> pertumbuhan >> dividen;
            daftarAset.push_back(new Saham(nama, kuantitas, harga, pertumbuhan, dividen));
        } else if (jenis == "obligasi") {
            double bunga;
            int maturitas;
            cout << "Masukkan bunga (%) dan maturitas (tahun): ";
            cin >> bunga >> maturitas;
            daftarAset.push_back(new Obligasi(nama, kuantitas, harga, bunga, maturitas));
        } else {
            cout << "Jenis aset tidak dikenal." << endl;
        }
    }

    int pilihan;
    do {
        // Menampilkan menu pilihan command
        cout << "\nPilih perintah yang ingin dijalankan:" << endl;
        cout << "1. Cetak daftar aset" << endl;
        cout << "2. Hitung total valuasi portofolio" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cetakDaftarAset(daftarAset);
            break;
        case 2: {
            double totalValuasi = hitungTotalValuasi(daftarAset);
            cout << "Total valuasi portofolio: " << totalValuasi << endl;
            break;
        }
        case 3:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
    } while (pilihan != 3);

    // Hapus alokasi memori dinamis
    for (Aset* aset : daftarAset) {
        delete aset;
    }

    return 0;
}
