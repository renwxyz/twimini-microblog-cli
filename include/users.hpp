#ifndef USERS_HPP
#define USERS_HPP

#include <iostream>
using namespace std;

// Forward declaration
struct PostNode;  

struct User {
    string username;
    string password;
    string bio;
    string interests[3];
    int totalLikes;   
};

typedef struct UserNode* addrUser;

struct UserNode {
    User info;               // Record user
    addrUser left;           // BST kiri
    addrUser right;          // BST kanan
    PostNode* firstPost;     // Multi Linked List 1-N
};

// Create
addrUser createUserNode(string username, string password);
addrUser insertUser(addrUser root, addrUser newNode);

// Read
addrUser searchUser(addrUser root, string username);
addrUser findMinUser(addrUser root);
addrUser findMaxUser(addrUser root);

void printUserProfile(addrUser userNode);
void inorderUsers(addrUser root);
void showTimeline(addrUser root);
int countUsers(addrUser root);

// Update
bool updatePassword(addrUser userNode, string newPassword, string confirm);
bool updateBio(addrUser userNode, string newBio);
bool updateInterest(addrUser userNode, string newInterests[3]);

// Delete
addrUser deleteUser(addrUser root, string username);

#endif
