#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Struktur ADT untuk Destinasi Wisata
struct Destination {
    string name;           // Nama destinasi
    int duration;          // Durasi kunjungan (dalam jam)
    string transportation; // Transportasi yang digunakan (misalnya: bus, kereta, pesawat)

    // Konstruktor untuk menetapkan nilai awal
    Destination(string n, int d, string t) : name(n), duration(d), transportation(t) {}

    // Fungsi untuk menampilkan informasi destinasi
    void display() const {
        cout << setw(20) << left << name
             << setw(20) << left << duration
             << setw(15) << left << transportation << endl;
    }
};

// Kelas ADT untuk Rute Wisata
class TravelRoute {
private:
    vector<Destination> route; // Menyimpan destinasi-destinasi dalam perjalanan

public:
    // Menambahkan destinasi baru ke rute
    void addDestination(const string& name, int duration, const string& transportation) {
        route.push_back(Destination(name, duration, transportation));
    }

    // Menampilkan seluruh rute wisata
    void displayRoute() const {
        cout << "\nRute Wisata:\n";
        cout << setw(20) << left << "Destinasi"
             << setw(20) << left << "Durasi (Jam)"
             << setw(15) << left << "Transportasi" << endl;
        cout << string(55, '-') << endl;

        for (const auto& dest : route) {
            dest.display();
        }
    }

    // Menyimpan rute wisata ke dalam file CSV
    void saveToCSV(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        file << "Destinasi,Durasi (Jam),Transportasi\n";  // Header CSV
        for (const auto& dest : route) {
            file << dest.name << ","
                 << dest.duration << ","
                 << dest.transportation << "\n";
        }

        file.close();
        cout << "Rute wisata telah disimpan ke " << filename << endl;
    }

    // Menghitung total durasi perjalanan
    int getTotalDuration() const {
        int total = 0;
        for (const auto& dest : route) {
            total += dest.duration;
        }
        return total;
    }
};

// Fungsi untuk menampilkan menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Tambah Destinasi\n";
    cout << "2. Tampilkan Rute Wisata\n";
    cout << "3. Simpan Rute ke CSV\n";
    cout << "4. Keluar\n";
}

// Fungsi utama
int main() {
    TravelRoute travelRoute;
    int choice;
    string name, transportation, filename;
    int duration;

    while (true) {
        displayMenu();
        cout << "Pilih opsi: ";
        cin >> choice;
        cin.ignore();  // Untuk membersihkan buffer

        switch (choice) {
            case 1:
                // Menambahkan destinasi baru
                cout << "\nMasukkan Nama Destinasi: ";
                getline(cin, name);
                cout << "Masukkan Durasi (Jam): ";
                cin >> duration;
                cin.ignore();
                cout << "Masukkan Transportasi yang Digunakan: ";
                getline(cin, transportation);
                travelRoute.addDestination(name, duration, transportation);
                break;

            case 2:
                // Menampilkan rute wisata
                travelRoute.displayRoute();
                cout << "\nTotal Durasi Perjalanan: " << travelRoute.getTotalDuration() << " jam\n";
                break;

            case 3:
                // Menyimpan rute wisata ke file CSV
                cout << "\nMasukkan nama file (misal: rute_wisata.csv): ";
                getline(cin, filename);
                travelRoute.saveToCSV(filename);
                break;

            case 4:
                // Keluar dari program
                cout << "Terima kasih telah menggunakan program ini!\n";
                return 0;

            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    }

    return 0;
}