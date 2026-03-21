class Fancy {
public:
    typedef long long ll;
    ll M = 1e9 + 7;
    vector<ll> seq;
    ll add = 0;
    ll mult = 1;


    ll power(ll base, ll exp) {
        ll res = 1;
        base %= M;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % M;
            base = (base * base) % M;
            exp /= 2;
        }
        return res;
    }


    ll modInverse(ll n) {
        return power(n, M - 2);
    }

    Fancy() {}

    void append(int val) {

        ll x = (val - add + M) % M;
        x = (x * modInverse(mult)) % M;
        seq.push_back(x);
    }

    void addAll(int inc) {
        add = (add + inc) % M;
    }

    void multAll(int m) {
        mult = (mult * m) % M;
        add = (add * m) % M;
    }

    int getIndex(int idx) {
        if (idx >= seq.size()) return -1;

        return (seq[idx] * mult + add) % M;
    }
};
