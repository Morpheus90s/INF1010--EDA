#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bitvector {
    int n_bytes;
    unsigned char* v;
} BitVector;

BitVector* create_set(int num_bits);
void free_set(BitVector* s);
void set_from_hex(BitVector* s, const unsigned char* hex_data, int num_bytes);
void print_set(const char* title, BitVector* s);

BitVector* set_remove(BitVector* s, int i);
BitVector* set_diferenca(BitVector* r, BitVector* s);

int main() {

    const unsigned char hex_S[] = {
        0x00, 0x00, 0x00, 0xFA, 0x11, 0xFF, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    };
    
    const unsigned char hex_R[] = {
        0x05, 0xEE, 0x00, 0xF1, 0x00, 0x11, 0x44, 0x55, 0x00, 0x00, 0x33, 0x77
    };

    int num_bytes = 12; // 12 bytes = 96 bits (para bater com os dados hex)
    int num_bits = num_bytes * 8;

    printf("--- Teste (a): set_remove ---\n");
    BitVector* S_a = create_set(num_bits);
    set_from_hex(S_a, hex_S, num_bytes);
    
    print_set("S Original:", S_a);
    
    printf("\nRemovendo bit 30...\n");
    set_remove(S_a, 30);
    
    printf("Removendo bit 39...\n");
    set_remove(S_a, 39);

    printf("Removendo bit 73...\n");
    set_remove(S_a, 73);
    
    print_set("\nS Modificado (a):", S_a);

    printf("\n--- Teste (b): set_diferenca ---\n");
    BitVector* R_b = create_set(num_bits);
    BitVector* S_b = create_set(num_bits);
    
    set_from_hex(R_b, hex_R, num_bytes);
    set_from_hex(S_b, hex_S, num_bytes);

    print_set("Conjunto R:", R_b);
    print_set("Conjunto S:", S_b);

    BitVector* T_b = set_diferenca(R_b, S_b);

    print_set("\nResultado T = R - S (b):", T_b);
    
    free_set(S_a);
    free_set(R_b);
    free_set(S_b);
    free_set(T_b);

    return 0;
}

BitVector* create_set(int num_bits) {
    int n_bytes = (num_bits + 7) / 8;
    
    BitVector* s = (BitVector*)malloc(sizeof(BitVector));
    if (s == NULL) {
        perror("Falha ao alocar BitVector");
        exit(1);
    }
    
    s->n_bytes = n_bytes;
    s->v = (unsigned char*)calloc(n_bytes, sizeof(unsigned char));
    if (s->v == NULL) {
        perror("Falha ao alocar vetor de bytes");
        free(s);
        exit(1);
    }
    return s;
}

void free_set(BitVector* s) {
    if (s != NULL) {
        free(s->v);
        free(s);
    }
}

void set_from_hex(BitVector* s, const unsigned char* hex_data, int num_bytes) {
    if (num_bytes > s->n_bytes) {
        printf("Erro: dados hex maiores que a capacidade do BitVector.\n");
        return;
    }
    memcpy(s->v, hex_data, num_bytes);
}

void print_set(const char* title, BitVector* s) {
    printf("%s\n", title);
    printf("  (");
    for (int i = 0; i < s->n_bytes; i++) {
        printf("%02X ", s->v[i]);
    }
    printf(")\n");
}

/* * a) set_remove
 * remove o i-ésimo elemento do conjunto s 
 */
BitVector* set_remove(BitVector* s, int i) {
    int byte_index = i / 8;
    int bit_index = i % 8;

    if (byte_index >= s->n_bytes) {
        printf("Erro: Tentando remover bit %d, que esta fora dos limites.\n", i);
        return s;
    }

    unsigned char mask = ~(1 << bit_index);
    s->v[byte_index] = s->v[byte_index] & mask;

    return s;
}

/* * b) set_diferenca
 * entrada: conjuntos r e s
 * saída: o conjunto t formado pelos elementos de r
 * que não estão em s 
 */
BitVector* set_diferenca(BitVector* r, BitVector* s) {
    
    BitVector* t = create_set(r->n_bytes * 8);

    for (int i = 0; i < r->n_bytes; i++) {
        if (i < s->n_bytes) {
             t->v[i] = r->v[i] & (~s->v[i]);
        } else {
             t->v[i] = r->v[i];
        }
    }
    
    return t;
}