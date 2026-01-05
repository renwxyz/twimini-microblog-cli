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

        cout << endl;
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
        cout << "4. Lihat profil\n";
        cout << "5. Temukan Pengguna lain\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> postChoice;

        switch (postChoice) {

            case 1: {
                string content;
                cin.ignore();

                cout << "Masukkan Isi Post: ";
                getline(cin, content);

                addrPost newPost = createPost(content);
                insertPost(currentUser, newPost);

                cout << "Postingan berhasil dibuat.\n";
                break;
            }

            case 2: {
                int postMenu;

                do {
                    cout << "\n=== Postingan saya ===\n";
                    printPosts(currentUser);
                    
                    cout << endl;
                    cout << "1. Hapus Post\n";
                    cout << "2. Edit Post\n";
                    cout << "3. Like post\n";
                    cout << "0. Kembali\n";

                    cout << "Pilih: ";
                    cin >> postMenu;

                    switch (postMenu){
                        case 1:
                            deletePost(currentUser);
                            break;
                        case 2:
                            updatePost(currentUser);
                            break;
                        case 3:
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
                } while (postMenu != 0);
                break;
            }

            case 3:
                menuTimeLine(rootUser);
                break;

            case 4:{
                int profileMenu;
                do{
                    printUserProfile(currentUser);

                    cout << "1. Update Password\n";
                    cout << "2. Update Bio\n";
                    cout << "3. Update Interests\n";
                    cout << "0. Kembali\n";
                    cout << "Pilih: ";
                    cin >> profileMenu;

                    switch(profileMenu){
                        case 1: {
                            string pass, confirm;
                            cout << "Password baru: ";
                            cin >> pass;
                            cout << "Konfirmasi password: ";
                            cin >> confirm;
                            
                            if (updatePassword(currentUser, pass, confirm)){
                                cout << "Password berhasil diupdate.\n";
                            } else {
                                cout << "Password gagal diupdate\n";
                            }
                            break;
                        }

                        case 2:{
                            string newBio;
                            cin.ignore();
                            cout << "Bio baru: ";
                            getline(cin, newBio);

                            if (updateBio(currentUser, newBio)){
                                cout << "Bio berhasil diperbarui.\n";
                            } else {
                                cout << "User tidak ditemukan.\n";
                            }
                            break;
                        }
                        
                        case 3: {
                            string newInterest[3];
                            for (int i = 0; i<3; i++){
                                cout << "Interest ke-" << i+1 << ": ";
                                cin >> newInterest[i];
                            }

                            if (updateInterest(currentUser, newInterest)){
                                cout << "Interest berhasil diperbarui.\n";
                            } else {
                                cout << "Interest gagal diperbarui.\n";
                            }
                            break;
                        }

                        case 0:
                            break;
                        default:
                            cout << "Pilihan tidak valid.\n";
                    }
                } while (profileMenu !=0);
                break;
            }

            case 5: {
                string usernameDicari;
                int postOption;

                cout << "Masukkan username yang akan dicari: ";
                cin >> usernameDicari;
                cout << endl;

                addrUser foundUser = searchUser(rootUser, usernameDicari);
                    
                if (foundUser == nullptr){
                    cout << "Pengguna dengan username: " << usernameDicari << " Tidak ditemukan.\n";
                    break;
                }

                cout << "Pengguna dengan username: " << foundUser->info.username << " ditemukan!\n";
                cout << endl;    

                do {
                    cout << "1. Lihat Profile\n";
                    cout << "2. Lihat Postingan\n";
                    cout << "0. Kembali\n";
                    
                    cout << "pilih: ";
                    cin >> postOption;

                    switch (postOption) {
                        case 1:
                            printUserProfile(foundUser);
                            break;
                        case 2:{
                            printPosts(foundUser);
                            int option;
                            
                            do{
                                cout << "1. Like Postingan\n";
                                cout << "0. Kembali\n";
                                cout << "Pilih: ";
                                cin >> option;

                                switch(option){
                                    case 1:
                                        int postId;
                                        cout << "Masukkan id postingan: ";
                                        cin >> postId;

                                        if(!(likePost(foundUser, postId))){
                                            cout << "Like gagal.\n";
                                            break;
                                        }

                                        break;
                                    case 0:
                                        cout << "Kembali...\n";
                                        break;
                                    default:
                                        cout << "Pilihan tidak falid.\n";
                                }
                            } while(option != 0);

                            break;
                        } 
                        case 0:
                            cout << "Kembali...\n";
                            break;
                        default:
                            cout << "Pilihan tidak falid.\n";
                    }
                } while(postOption != 0);
                break;
            }

            case 0:
                cout << "Logout berhasil.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
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
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (choice != 0);

    return 0;
}
