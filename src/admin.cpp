#include "../include/admin.hpp"

int countTotalPosts(addrUser root) {
    if (root == NULL) return 0;

    int count = 0;
    PostNode* p = root->firstPost;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count + countTotalPosts(root->left) + countTotalPosts(root->right);
}


int countUsers(addrUser root) {
    if (root == nullptr) return 0;
    return 1 + countUsers(root->left) + countUsers(root->right);
}

void minPostLikeHelper(addrUser root, Post &minPost, bool &found) {
    if (root == NULL) return;

    PostNode* p = root->firstPost;
    while (p != NULL) {
        if (!found || p->info.likes < minPost.likes) {
            minPost = p->info;
            found = true;
        }
        p = p->next;
    }

    minPostLikeHelper(root->left, minPost, found);
    minPostLikeHelper(root->right, minPost, found);
}

void minPostLike(addrUser root) {
    Post minPost;
    bool found = false;

    minPostLikeHelper(root, minPost, found);

    if (found) {
        cout << "\nPost dengan LIKE Paling Sedikit (Min)\n";
        cout << "ID           : " << minPost.postId << endl;
        cout << "Jumlah like  : " << minPost.likes << endl;
        cout << "Isi          : " << minPost.content << endl;
    } else {
        cout << "\nBelum ada postingan\n";
    }
}

void maxPostLikeHelper(addrUser root, Post &maxPost) {
    if (root == NULL) return;

    PostNode* p = root->firstPost;
    while (p != NULL) {
        if (p->info.likes > maxPost.likes) {
            maxPost = p->info;
        }
        p = p->next;
    }

    maxPostLikeHelper(root->left, maxPost);
    maxPostLikeHelper(root->right, maxPost);
}

void maxPostLike(addrUser root) {
    Post maxPost;
    maxPost.likes = -1;

    maxPostLikeHelper(root, maxPost);

    if (maxPost.likes >= 0) {
        cout << "\nPost dengan LIKE Paling Banyak (Max)\n";
        cout << "ID           : " << maxPost.postId << endl;
        cout << "Jumlah like  : " << maxPost.likes << endl;
        cout << "Isi          : " << maxPost.content << endl;
    } else {
        cout << "\nBelum ada postingan\n";
    }
}


