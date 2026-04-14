# Italian Affine Cipher (Encrypt/Decrypt) — C++

A C++ console application that encrypts and decrypts text using the Affine Cipher over the 21-letter Italian alphabet.

## How It Works

The Affine Cipher uses the formula:

- **Encryption:** y = (a×x + b) mod 21
- **Decryption:** x = a⁻¹ × (y - b) mod 21

Where `a` and `b` are the secret keys.

## Italian Alphabet (21 letters)

`A B C D E F G H I L M N O P Q R S T U V Z`  (excludes J, K, W, X, Y from the standard alphabet)

## Features

- Encrypt and decrypt any message using the Italian alphabet
- Preserves case (uppercase/lowercase) and non-letter characters
- Validates that key `a` is coprime with 21 (required for decryption)
- Full input validation with descriptive error messages
- Repeatable — run multiple operations without restarting

## Error Handling

- Rejects letters outside the Italian alphabet
- Rejects key `a` values that are not coprime with 21
- Handles invalid menu choices gracefully

## Implementation Notes

Built using **basic C++ only** — no vectors, no pointers. Uses only:

- `string` and character operations
- loops and switch statements
- Modular arithmetic for encryption/decryption

## How to Compile and Run

```bash
g++ Italian cipher.cpp -o affine_cipher
./affine_cipher
```

## Valid Values for Key `a`

Key `a` must be coprime with 21:

`1, 2, 4, 5, 8, 10, 11, 13, 16, 17, 19, 20`
