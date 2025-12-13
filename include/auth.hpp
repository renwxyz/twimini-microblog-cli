#ifndef AUTH_HPP
#define AUTH_HPP

#include "users.hpp"
using namespace std;

void registerUser(addrUser &root);
addrUser loginUser(addrUser root);

#endif