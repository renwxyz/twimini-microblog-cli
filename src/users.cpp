#include "../include/users.hpp"
#include "../include/posts.hpp"

addrUser createUserNode(string username, string password) {
    addrUser P = new UserNode;
    P->info.username = username;
    P->info.password = password;

    // default value
    P->info.bio = "";
    P->info.totalLikes = 0;
    for (int i = 0; i < 3; i++) {
        P->info.interests[i] = "";
    }

    P->left = nullptr;
    P->right = nullptr;
    P->firstPost = nullptr;

    return P;
}

addrUser insertUser(addrUser root, addrUser newUser) {
    if (root == nullptr) {
        return newUser;
    }

    if (newUser->info.username < root->info.username) {
        root->left = insertUser(root->left, newUser);
    } else if (newUser->info.username > root->info.username) {
        root->right = insertUser(root->right, newUser);
    }
    // username sama → tidak dimasukkan (opsional)
    return root;
}

addrUser searchUser(addrUser root, string username) {
    if (root == nullptr) {
        return nullptr;
    }

    if (username == root->info.username) {
        return root;
    } else if (username < root->info.username) {
        return searchUser(root->left, username);
    } else {
        return searchUser(root->right, username);
    }
}

addrUser findMinUser(addrUser root) {
    if (root == nullptr) {
        return nullptr;
    }

    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}

addrUser findMaxUser(addrUser root) {
    if (root == nullptr) {
        return nullptr;
    }

    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}


void printUserProfile(addrUser userNode){
    if (userNode == NULL){
        cout << "User tidak valid \n";
        return;
    }

    cout << "\n=== Profil User - " << userNode->info.username << " ===\n";
    cout << "Username : " << userNode->info.username << endl;
    cout << "Bio      : " << userNode->info.bio << endl;
    cout << "Likes    : " << userNode->info.totalLikes << endl;

    cout << "Interests: ";
    for (int i = 0; i < 3; i++) {
        cout << userNode->info.interests[i];
        if (i < 2) cout << ", ";
    }
    cout << endl;
}



void inorderUsers(addrUser root) {
    if (root != nullptr) {
        inorderUsers(root->left);
        cout << root->info.username << " ";
        inorderUsers(root->right);
    }
}

void showTimeline(addrUser root) {
    if (root == NULL) {
        return;
    }

    showTimeline(root->left);

    addrPost P = root->firstPost;
    while (P != NULL) {
        tm *t = localtime(&P->info.timestamp);

        cout << "================================\n";
        cout << "User   : " << root->info.username << endl;
        cout << "PostID : " << P->info.postId << endl;
        cout << "Isi    : " << P->info.content << endl;
        cout << "Like   : " << P->info.likes << endl;
        cout << "Waktu  : "
             << t->tm_hour << ":"
             << t->tm_min << endl;

        P = P->next;
    }
    
    showTimeline(root->right);
}


bool updatePassword(addrUser userNode, string newPassword, string confirm) {
    if (newPassword == confirm){
        userNode->info.password = newPassword;
        return true;
    } else {
        return false;
    }

}

bool updateBio(addrUser userNode, string newBio){
    userNode->info.bio = newBio;
    if (userNode->info.bio == newBio){
        return true;
    } else {
        return false;
    }
}

bool updateInterest(addrUser userNode, string newInterest[3]){
    for (int i = 0; i<3; i++){
        userNode->info.interests[i] = newInterest[i];
    }

    for (int i = 0; i<3; i++){
        if (userNode->info.interests[i] != newInterest[i]){
            return false;
        }
    }

    return true;
}

addrUser deleteUser(addrUser root, string username) {
    if (root == nullptr) {
        return nullptr;
    }

    if (username < root->info.username) {
        root->left = deleteUser(root->left, username);
    }
    else if (username > root->info.username) {
        root->right = deleteUser(root->right, username);
    }
    else {
        
        //Node ditemukan 

        // CASE 1: Leaf
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // CASE 2: Satu Child (Right)
        if (root->left == nullptr) {
            addrUser temp = root->right;
            delete root;
            return temp;
        }

        // CASE 2: Satu Child (Left)
        if (root->right == nullptr) {
            addrUser temp = root->left;
            delete root;
            return temp;
        }

        // CASE 3: Dua Child (Copy-successor)
        addrUser succ = findMinUser(root->right);

        root->info.username     = succ->info.username;
        root->info.password     = succ->info.password;
        root->info.bio          = succ->info.bio;
        root->info.totalLikes   = succ->info.totalLikes;
        for (int i = 0; i < 3; i++) {
            root->info.interests[i] = succ->info.interests[i];
        }
        root->firstPost = succ->firstPost;

        root->right = deleteUser(root->right, succ->info.username);
    }

    return root;
}
