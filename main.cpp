#include <iostream>
#include "./include/auth.hpp"
using namespace std;

int main() {
    addrUser root = NULL;
    addrUser currentUser = NULL;

    int choice;

    do {
        cout << "\n=== TEST REGISTER & LOGIN ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Lihat jumlah user (test)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(root);
                break;

            case 2:
                currentUser = loginUser(root);
                break;

            case 3:
                cout << "Total user: " << countUsers(root) << endl;
                break;
        }

    } while (choice != 0);

    return 0;
}
