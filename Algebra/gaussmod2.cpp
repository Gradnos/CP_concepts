#include <vector>
#include <bitset>
using namespace std;


const int MAXB = 500;
struct gauss {
    vector<bitset<MAXB>> basis;
    gauss() : basis(MAXB) {}
    void add(bitset<MAXB> v) {
        for (int i = MAXB - 1; i >= 0; i--) {
            if (!v[i]) continue;
            if (!basis[i].any()) {basis[i] = v;break;}
            v ^= basis[i];
        }
    }
    bool canRepresent(bitset<MAXB> x) const {
        for (int i = MAXB - 1; i >= 0; i--) {
            if (!x[i]) continue;
            if (!basis[i].any()) return false;
            x ^= basis[i];
        }
        return true;
    }
};
