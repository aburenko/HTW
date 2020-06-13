/*
  s76905 beleg für Internetsicherheit
*/
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

void err_exit(void) {
    printf("%s\n", ERR_error_string(ERR_get_error(), NULL));

    ERR_free_strings();
    exit(EXIT_FAILURE);
}

static char *pt(unsigned char *md) {
    int i;
    static char buf[16];
    for (i = 0; i < 16; i++) {
        // write as hexadecimal to buf
        sprintf(&(buf[i * 2]), "%02x", md[i]);
    }
    return (buf);
}

unsigned char *md4_hash(unsigned char txt[], int len) {
    printf("\ncreating md4 hash\n");
    EVP_MD_CTX c;
    unsigned char *md = malloc(sizeof(unsigned char) * 16);

    ERR_load_crypto_strings();
    EVP_MD_CTX_init(&c);

    if ((EVP_DigestInit(&c, EVP_md4())) == 0) {
        err_exit();
    }
    if ((EVP_DigestUpdate(&c, txt, len)) == 0) {
        err_exit();
    }
    if ((EVP_DigestFinal(&c, md, NULL)) == 0) {
        err_exit();
    }

    // print as hexadecimal
    printf("hash was %s\n", pt(md));

    // clean ups
    EVP_MD_CTX_cleanup(&c);
    ERR_free_strings();

    return md;
}

void clean_up() {
    /* Removes all digests and ciphers */
    EVP_cleanup();
    /* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
    CRYPTO_cleanup_all_ex_data();
    /* Remove error strings */
    ERR_free_strings();
}

int decrypt(unsigned char cipher[], int cipher_len, unsigned char key[],
            unsigned char iv[], unsigned char plain[], const EVP_CIPHER *type) {
    printf("init vars\n");
    EVP_CIPHER_CTX *ctx;
    int len;
    int plain_len;
    /* Load the human readable error strings for libcrypto */
    ERR_load_crypto_strings();

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    // printf("decrypt init\n");
    if (1 != EVP_DecryptInit_ex(ctx, type, NULL, key, iv))
        handleErrors();

    printf("decrypt update\n");
    if (1 != EVP_DecryptUpdate(ctx, plain, &len, cipher, cipher_len))
        handleErrors();
    plain_len = len;

    printf("decrypt final\n");
    if (1 != EVP_DecryptFinal_ex(ctx, plain + len, &len)) {
        plain_len = -1;
        printf("decryption failed\n");
    } else {
        plain_len += len;
    }

    printf("decrypt clean up\n");
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plain_len;
}

int brutforce_decrypt(unsigned char cipher[], int cipher_len, unsigned char key[],
                      unsigned char iv[], unsigned char plain[]) {
    printf("starting brutforce\n");
    for (int i = 0; i < 256; i++) {
        printf("bf value is: %d\n", i);
        key[11] = (char)i;

        int len = decrypt(cipher, cipher_len, key, iv,
                          plain, EVP_camellia_256_cfb1());
        printf("len was: %d. Starts with: ", len);
        for (int j = 0; j < 5; j++) {
            printf("%02x", plain[j]);
        }
        printf("\n");
        if (len != -1 && plain[0] == '%' && plain[1] == 'P' && plain[2] == 'D' && plain[3] == 'F') {
            printf("\n\nFound %%PDF in decrypted file!\n\n");
            return len;
        }
        clean_up();
    }
    return -1;
}

int encrypt(unsigned char *plain, int plain_len, unsigned char *key,
            unsigned char *iv, unsigned char *cipher) {
    EVP_CIPHER_CTX *ctx;

    int len;
    int cipher_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_192_ofb(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, cipher, &len, plain, plain_len))
        handleErrors();
    cipher_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, cipher + len, &len))
        handleErrors();
    cipher_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return cipher_len;
}

void get_keys(char *file_name, unsigned char *key,
              unsigned char *iv, int sizeKey) {
    FILE *f;
    size_t r = 0;
    printf("reading keys out of a %s\n", file_name);
    f = fopen(file_name, "rb");
    if (f == NULL) {
        fputs("File error", stderr);
        exit(1);
    }

    // copy the file into the keys:
    r += fread(key, 1, sizeKey, f);
    r += fread(iv, 1, 16, f);
    fclose(f);
    if (r != sizeKey + 16) {
        fputs("Reading error", stderr);
        exit(2);
    }
    printf("key: ");
    for (int i = 0; i < sizeKey; i++) {
        printf("%02x", key[i]);
    }
    printf("\niv: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", iv[i]);
    }
    printf("\n");
}

int main(void) {
    printf("start main\n");

    /* A 256 bit key */
    unsigned char key[32];
    /* A 128 bit IV */
    unsigned char iv[16];
    get_keys("s76905-source-key-corrupt.bin", key, iv, 32);

    printf("\nreading cipher text out of a file\n");
    // Reading size of file
    FILE *f = fopen("s76905-source-cipher.bin", "r+");
    if (f == NULL) {
        fputs("Reading error", stderr);
        exit(3);
    }
    fseek(f, 0, SEEK_END);
    long int s = ftell(f);
    rewind(f);
    unsigned char cipher[s];
    unsigned char decrypted[s];
    int bytes_read = fread(cipher, sizeof(unsigned char), s, f);
    if (bytes_read != s) {
        fputs("Reading error", stderr);
        exit(4);
    }
    fclose(f);

    int cipher_len = s;
    int decrypted_len = 0;

    /* Decrypt the cipher */
    decrypted = brutforce_decrypt(cipher, cipher_len, key, iv,
                                          decrypted);

    if (decrypted_len == -1) {
        printf("\nno match for %%PDF found\n");
        exit(5);
    }

    unsigned char *md4H = md4_hash(decrypted, decrypted_len);
    /* concatenate decrypted text with hash */
    int dest_size = s + 16;
    unsigned char hashed[dest_size];
    for (int i = 0; i < s; i++) {
        hashed[i] = decrypted[i];
    }
    for (int i = 0; i < 16; i++) {
        hashed[s + i] = md4H[i];
    }
    /* Encrypt the plain with hash */
    unsigned char keyAes[24];
    unsigned char ivAes[16];
    get_keys("s76905-dest-key.bin", keyAes, ivAes, 24);
    int encrypted_len = 0;
    unsigned char encryptedhashed[dest_size];
    encrypted_len = encrypt(hashed, dest_size, keyAes, ivAes,
                            encryptedhashed);

    printf("len was: %d. Starts with: ", encrypted_len);
    for (int j = 0; j < 5; j++) {
        printf("%02x", encryptedhashed[j]);
    }
    printf("\n");

    // test
    printf("start test\n");
    unsigned char t[dest_size];
    int t_len = decrypt(encryptedhashed, encrypted_len, keyAes, ivAes,
                               t, EVP_aes_192_ofb());
    if (t_len != dest_size) {
        printf("test: size error\n");
        exit(7);
    }
    if (t[0] != '%' || t[1] != 'P' || t[2] != 'D' || t[3] != 'F') {
        printf("test: pdf not found error\n");
        exit(7);
    }
    if (t[dest_size - 2] != md4H[14] || t[dest_size - 1] != md4H[15]) {
        for (int j = 2; j >= 0; j--) {
            printf("%02x - %02x\n", t[dest_size - 1 - j], md4H[15 - j]);
        }
        printf("test: hash not found error\n");
        exit(7);
    }
    printf("end test\n");

    /* save encrypted pdf with hash */
    printf("\nsaving enrypted text + hash\n");
    f = fopen("s76905-dest-cipher.bin", "w+");
    fwrite(encryptedhashed, sizeof(unsigned char), encrypted_len, f);
    fclose(f);

    printf("exit\n");
    return 0;
}
