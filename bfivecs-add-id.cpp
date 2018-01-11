#include <cstring>
#include <cstdio>
#include <cinttypes>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc != 6) {
        printf("Usage: ./bfivecs-add-id <input> <output> <max_dim> [bvecs|fvecs|ivecs] <contains_dim: [0|1]>\n");
        return 1;
    }

    const char* input = argv[1];
    const char* output = argv[2];
    int max_dim = atoi(argv[3]);
    const char* type = argv[4];
    const char* contains_dim = argv[5];

    int element_len;
    if (!strcmp(type, "bvecs")) {
        element_len = 1;
    } else {
        element_len = 4;
    }

    FILE* fp_in = fopen(input, "rb");
    FILE* fp_out = fopen(output, "wb");

    int32_t max_entry_len = element_len * max_dim;
    char buf[max_entry_len];

    int32_t i = 0;
    int32_t dim;
    while (1) {
        fread(&dim, 4, 1, fp_in);

        size_t res = fread(buf, element_len, dim, fp_in);
        if (res != dim) {
            break;
        }

        fwrite(&i, 4, 1, fp_out);
        if (contains_dim[0] == '1') {
            fwrite(&dim, 4, 1, fp_out);
        }
        fwrite(buf, element_len, dim, fp_out);

        ++i;
    }

    fclose(fp_out);
    fclose(fp_in);
}

