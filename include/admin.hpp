#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "users.hpp"
#include "posts.hpp"

// Statistik
int countTotalPosts(addrUser root);
int countUsers(addrUser root);
void maxPostLike(addrUser root);
void minPostLike(addrUser root);

#endif
