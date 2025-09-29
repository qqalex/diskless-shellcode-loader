#include <math.h>

void XOR(char *data, unsigned int size, char key) {
  for (unsigned int i = 0; i < size; i++)
    data[i] = data[i] ^ key;
};

struct DiffieHellman {
  int a;       // secret (private) key
  long long p; // safe prime modulus
  int g;       // primitive root modulo
  long long A; // public key
  long long s; // shared secret
};

struct DiffieHellman dh_init_root(int a, int p, int g) {
  struct DiffieHellman dh;
  dh.a = a;
  dh.p = p;
  dh.g = g;
  dh.A = (long long)pow(g, a) % p;
  return dh;
};

struct DiffieHellman dh_init(int a, int p) { return dh_init_root(a, p, 2); }

void dh_shared_secret(struct DiffieHellman *dh, int B)
{
  dh->s = (long long)pow(B, dh->a) % dh->p;
}