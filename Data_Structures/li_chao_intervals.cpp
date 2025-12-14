using namespace std;

// T should be a numeric type like long long, double, long double
template<typename T>
struct LiChao {
    struct Line {
        T a=0, b=std::numeric_limits<T>::lowest();
        T eval(T x) const { return a * x + b; }
    };
    struct Node {
        Line ln;
        Node *l = nullptr, *r = nullptr;
    };

    T L, R;
    Node* root = nullptr;

    LiChao(T left, T right): L(left), R(right) {}

    void addFull(Node*& n, T l, T r, Line nw) {
        if (!n) { n = new Node(); }
        T m = (l + r) / 2;
        if (n->ln.eval(l) < nw.eval(l)) swap(n->ln, nw);
        if (n->ln.eval(r) >= nw.eval(r) || l == r) return;
        if (n->ln.eval(m) > nw.eval(m))
            addFull(n->r, m+1, r, nw);
        else {
            swap(n->ln, nw);
            addFull(n->l, l, m, nw);
        }
    }

    void addRange(Node*& n, T l, T r, T ql, T qr, Line ln) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            addFull(n, l, r, ln);
            return;
        }
        T m = (l + r) / 2;
        addRange(n->l, l,    m, ql, qr, ln);
        addRange(n->r, m+1,  r, ql, qr, ln);
    }

    // Inserts y = a*x + b on interval [ql, qr]
    void insert(T a, T b, T ql, T qr) {
        addRange(root, L, R, ql, qr, Line{a,b});
    }

    T query(Node* n, T l, T r, T x) const {
        if (!n) return std::numeric_limits<T>::lowest();
        T res = n->ln.eval(x);
        if (l == r) return res;
        T m = (l + r) / 2;
        if (x <= m) return max(res, query(n->l, l, m, x));
        else         return max(res, query(n->r, m+1, r, x));
    }

    T get(T x) const {
        return query(root, L, R, x);
    }
}; 
