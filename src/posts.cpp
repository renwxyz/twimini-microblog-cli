#include "../include/posts.hpp"

addrPost createPost(string content) {
    addrPost P = new PostNode;
    P->info.postId = generatePostId();
    P->info.content = content;
    P->info.likes = 0;
    P->info.timestamp = time(NULL);
    P->next = NULL;
    P->prev = NULL;
    return P;
}

void insertPost(addrUser user, addrPost newPost) {
    if (user == NULL || newPost == NULL) {
        return;
    }

    if (user->firstPost == NULL) {
        user->firstPost = newPost;
    } else {
        addrPost P = user->firstPost;
        while (P->next != NULL) {
            P = P->next;
        }
        P->next = newPost;
        newPost->prev = P;
    }
}

void updatePost(addrUser user) {
    int id;
    string newContent;
    bool ketemu = false;

    if (user == NULL || user->firstPost == NULL) {
        cout << "Belum ada postingan.\n";
        return;
    }

    cout << "Masukkan ID post yang ingin diedit : ";
    cin >> id;
    cin.ignore();

    addrPost P = user->firstPost;

    while (P != NULL) {
        if (P->info.postId == id) {
            cout << "Masukkan isi post baru : ";
            getline(cin, newContent);
            P->info.content = newContent;
            cout << "Postingan berhasil diubah.\n";
            ketemu = true;
            break;
        }
        P = P->next;
    }

    if (!ketemu) {
        cout << "Tidak ada postingan dengan ID " << id << ".\n";
    }
}


void deletePost(addrUser user) {
    int id;
    bool ketemu = false;

    if (user == NULL || user->firstPost == NULL) {
        cout << "Belum ada postingan.\n";
        return;
    }

    cout << "Masukkan ID post yang ingin dihapus : ";
    cin >> id;

    addrPost P = user->firstPost;

    while (P != NULL) {
        if (P->info.postId == id) {

            if (P == user->firstPost) {
                user->firstPost = P->next;
                if (user->firstPost != NULL) {
                    user->firstPost->prev = NULL;
                }
            } else {
                P->prev->next = P->next;
                if (P->next != NULL) {
                    P->next->prev = P->prev;
                }
            }

            delete P;

            cout << "Postingan berhasil dihapus.\n";
            ketemu = true;
            break;
        }
        P = P->next;
    }

    if (!ketemu) {
        cout << "Tidak ada postingan dengan ID " << id << ".\n";
    }
}

void printPosts(addrUser user) {
    if (user == NULL) {
        return;
    }

    addrPost P = user->firstPost;
    if (P == NULL) {
        cout << "Belum ada postingan.\n";
        return;
    }

    while (P != NULL) {
        tm *t = localtime(&P->info.timestamp);
        cout << "------------------------\n";
        cout << "ID     : " << P->info.postId << endl;
        cout << "Isi    : " << P->info.content << endl;
        cout << "Like   : " << P->info.likes << endl;
        cout << "Waktu  : "
             << t->tm_hour << ":"
             << t->tm_min << endl;

        P = P->next;
    }
}

int generatePostId() {
    static int counter = 1;
    return counter++;
}