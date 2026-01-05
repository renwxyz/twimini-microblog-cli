#ifndef POSTS_HPP
#define POSTS_HPP

#include <iostream>
#include "users.hpp"
#include <ctime>       
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
};

// Create
addrPost createPost(string content);
void insertPost(addrUser user, addrPost newPost);
int generatePostId();

// Read
void printPosts(addrUser user);

// Update
void updatePost(addrUser user);
bool likePost(addrUser root, int postId);

// Delete
void deletePost(addrUser user);



#endif
