#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/* This RSA is not secure, it's just a simple implementation of the algorithm.
Also, it only works for messages with uppercase english letters and spaces. */
class RSA {
private:
    ll alpha;
    vector<ll> primes;
    const ll MAX_PRIME = 1e3;

    string encode_letter(char l) {
        ll dec = (l == 32 ? 36 : l - 55);
        return to_string(dec);
    }

    char decode_letter(string n) {
        ll dec = stoll(n);
        return dec == 36 ? 32 : dec + 55;
    }

    vector<ll> sieve(ll N) {
        bitset<1000'0007> sieve;
        vector<ll> ps{ 2, 3 };
        sieve.set();

        for (ll i = 5, step = 2; i <= N; i += step, step = 6 - step) {
            if (sieve[i]) {
                ps.push_back(i);

                for (ll j = i * i; j <= N; j += 2 * i) sieve[j] = false;
            }
        }
        return ps;
    }

    map<ll, ll> factorization(ll n) {
        map<ll, ll> ans;
        for (ll i = 2; i * i <= n; i++) {
            ll count = 0;
            for (; n % i == 0; count++, n /= i)
                ;
            if (count) ans[i] = count;
        }
        if (n > 1) ans[n]++;
        return ans;
    }

    ll phi(ll n) {
        if (n == 1) return 1;

        auto fs = factorization(n);
        auto res = n;

        for (auto [p, k] : fs) {
            res /= p;
            res *= (p - 1);
        }

        return res;
    }

    ll fpow(ll a, ll n, ll mod = LLONG_MAX) {
        if (n == 0) return 1;
        if (n == 1) return a;

        ll x = fpow(a, n / 2, mod) % mod;

        return ((x * x) % mod * (n & 1 ? a : 1ll)) % mod;
    }

public:
    RSA(ll alpha = 3) {
        this->alpha = alpha;

        primes = sieve(MAX_PRIME);
        srand((unsigned)time(NULL));
    }

    pair<vector<ll>, pair<ll, ll>> encoding(string msg) {
        ll p = 2, q = 2;

        while (p % 6 != 5) p = primes[rand() % primes.size()];
        while (q % 6 != 5 or q == p)
            q = primes[rand() % primes.size()];

        string nmb;
        for (auto ch : msg) nmb += encode_letter(ch);

        vector<ll> ans;
        ll nmb_sz = nmb.size();
        for (ll i = 0; i < nmb_sz; i++) {
            string tmp = "";

            ll max_len = log10(p * q);
            ll length = max(1ll, rand() % max_len), j = i;

            for (; j < nmb_sz && (ll)tmp.size() < length; j++) tmp += nmb[i = j];
            for (; nmb[j] == '0'; j++) tmp += nmb[i = j];
            ans.push_back(stoll(tmp));
        }

        for (auto& el : ans) el = fpow(el, alpha, p * q);

        return { ans, {p, q} };
    }

    string decode(ll n, vector<ll>& encoded) {
        ll inv = fpow(alpha, phi(phi(n)) - 1, phi(n));

        vector<string> tmp;
        for (auto& el : encoded) {
            string rev = to_string(fpow(el, inv, n));
            tmp.push_back(rev);
        }

        string nmbs;
        for (auto& el : tmp) nmbs += el;

        string ans;
        for (ll i = 0; i < (ll)nmbs.size(); i += 2) {
            ans += decode_letter(nmbs.substr(i, 2));
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    RSA rsa;
    vector<ll> code = { 130, 201, 507, 201, 261, 347, 472, 241 };
    cout << rsa.decode(799, code) << "\n"; // CARAMELO

    return 0;
}