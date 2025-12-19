#ifndef POSTS_HPP
#define POSTS_HPP

#include <iostream>
#include "users.hpp"
#include <ctime>        // untuk time_t
using namespace std;

struct Post {
    int postId;         // ID postingan (cth id: 1, 2, 3, ...)
    string content;     // isi postingan (cth: "Hello, world!")
    int likes;          // jumlah like
    time_t timestamp;   // waktu postingan
};

typedef struct PostNode* addrPost;

struct PostNode {
    Post info;          // data postingan
    addrPost next;      // post berikutnya (N)
    addrPost prev;      // post sebelumnya (P)
};

addrPost createPost(string content);
void insertPost(addrUser user, addrPost newPost);
void updatePost(addrUser user);
void deletePost(addrUser user);
void printPosts(addrUser user);
int generatePostId();


#endif
