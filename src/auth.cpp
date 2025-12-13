#include "../include/auth.hpp"

void registerUser(addrUser &root){
    string username, password;

    cout << "\n=== REGISTER ===\n";
    cout << "Username: ";
    cin >> username;

    // Cek apakah username sudah ada
    if (searchUser(root, username) != NULL) {
        cout << "Username sudah digunakan. Coba nama lain.\n";
        return;
    }

    cout << "Password: ";
    cin >> password;

    // Buat node user
    addrUser newUser = createUserNode(username, password);

    // Insert ke BST
    root = insertUser(root, newUser);

    cout << "Registrasi berhasil!\n";
}

addrUser loginUser(addrUser root) {
    string username, password;

    cout << "\n=== LOGIN ===\n";
    cout << "Username: ";
    cin >> username;

    addrUser user = searchUser(root, username);

    if (user == NULL) {
        cout << "Username tidak ditemukan.\n";
        return NULL;
    }

    cout << "Password: ";
    cin >> password;

    if (user->info.password != password) {
        cout << "Password salah.\n";
        return NULL;
    }

    cout << "Login berhasil! Selamat datang, " << user->info.username << "!\n";

    return user;
}
