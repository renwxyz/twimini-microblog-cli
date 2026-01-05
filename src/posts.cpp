#include "../include/posts.hpp"

addrPost createPost(string content) {
    addrPost P = new PostNode;
    P->info.postId = generatePostId();
    P->info.content = content;
    P->info.likes = 0;
    P->info.timestamp = time(NULL);
    P->next = NULL;
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

bool likePost(addrUser root, int postId) {
    if (root == NULL) return false;

    // cari di subtree kiri
    if (likePost(root->left, postId)){
        return true;
    }

    addrPost P = root->firstPost;
    while (P != NULL) {
        if (P->info.postId == postId) {
            P->info.likes++;

            root->info.totalLikes++;

            cout << "Post ID " << postId << " berhasil di-like." << endl;
            cout << "Total like sekarang: " << P->info.likes << endl;
            return true;
        }
        P = P->next;
    }

    // cari di subtree kanan
    return likePost(root->right, postId);
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

    addrPost curr = user->firstPost;
    addrPost prev = NULL;

    while (curr != NULL) {
        if (curr->info.postId == id) {

            if (prev == NULL) {
                user->firstPost = curr->next;
            } else {
                prev->next = curr->next;
            }

            delete curr;
            cout << "Postingan berhasil dihapus.\n";
            ketemu = true;
            break;
        }

        prev = curr;
        curr = curr->next;
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

        cout << "=======================\n";
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