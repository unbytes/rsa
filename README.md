# RSA

A simple RSA implementation in C++. It is not meant to be used in production, but rather as a learning tool. The `alpha` number is 3 by default, but can be changed. This implementation uses primes numbers not more than 1000 to encode the message, but this can be changed by changing the `MAX_PRIME` constant. Also, the random primes are chosen just if the remainder of the division by 6 is 5.

## Usage

To use this program, you need to compile it first. You can do this by running the following command:

```bash
g++ rsa.cpp -o rsa
```

After that, you can run the program by running the following command:

```bash
./rsa
```

## Observations

You can't use this program with `MAX_PRIME` less than 11, because it won't find two distinct primes that p % 6 == 5.
