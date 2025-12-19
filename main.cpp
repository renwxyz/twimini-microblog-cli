#include <iostream>
#include "./include/auth.hpp"
#include "./include/posts.hpp"
using namespace std;

void menuTimeLine(addrUser rootUser) {
    int timelineChoice;
    
    do {
        cout << "\n=== TIMELINE GLOBAL ===\n";
        if (rootUser == NULL || rootUser->firstPost == NULL) {
            cout << "Timeline masih kosong. Belum ada postingan." << endl;
            break;
        } else {
            showTimeline(rootUser);
        }

        cout << "1. Like\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> timelineChoice;

        switch (timelineChoice) {
            case 1:
                int postId;
                cout << "Masukkan ID post yang ingin di-like: ";
                cin >> postId;
                likePost(rootUser, postId);
                break;
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (timelineChoice != 0);

}

void menuUser(addrUser currentUser, addrUser rootUser) {
    int postChoice;

    do {
        cout << "\n=== MENU USER ===\n";
        cout << "Login sebagai: " << currentUser->info.username << endl;
        cout << "1. Buat Post\n";
        cout << "2. Lihat Post Saya\n";
        cout << "3. Lihat Timeline Global\n";
        cout << "4. Edit Post\n";
        cout << "5. Hapus Post\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> postChoice;

        switch (postChoice) {
            case 1: {
                string content;
                cin.ignore();

                cout << "Masukkan Isi Post  : ";
                getline(cin, content);

                addrPost newPost = createPost(content);
                insertPost(currentUser, newPost);

                cout << "Postingan berhasil dibuat.\n";
                break;
            }

            case 2:
                cout << "\n=== Postingan saya ===\n";
                printPosts(currentUser);
                break;
            
            case 3:
                menuTimeLine(rootUser);
                break;
            
            case 4: {
                updatePost(currentUser);
                break;
            }

            case 5: {
                deletePost(currentUser);
                break;
            }

            case 0:
                cout << "Logout berhasil.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (postChoice != 0);

}

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
                if (currentUser != NULL) {
                    menuUser(currentUser, root);
                }
                break;

            case 3:
                cout << "Total user: " << countUsers(root) << endl;
                break;
        }

    } while (choice != 0);

    return 0;
}
