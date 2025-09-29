#pragma once

struct DiffieHellman;
struct DiffieHellman dh_init_root(int a, int p, int g);
struct DiffieHellman dh_init(int a, int p);
void dh_shared_secret(struct DiffieHellman *dh, int B);
void XOR(char *data, unsigned int size, char key);