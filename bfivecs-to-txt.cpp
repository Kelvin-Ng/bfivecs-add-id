#define __STDC_FORMAT_MACROS 1

#include <cstring>
#include <cstdio>
#include <cinttypes>
#include <cstdlib>
#include <string>

template <typename T>
void bfivecs_to_txt(FILE* fp_in, FILE* fp_out, int max_dim, const std::string& fmt_str) {
    T buf[max_dim];
    int32_t dim;

    std::string fmt_str_1 = fmt_str + " ";
    std::string fmt_str_2 = fmt_str + "\n";
    const char* fmt_cstr_1 = fmt_str_1.c_str();
    const char* fmt_cstr_2 = fmt_str_2.c_str();

    while (1) {
        fread(&dim, 4, 1, fp_in);

        size_t res = fread(buf, sizeof(T), dim, fp_in);
        if (res != dim) {
            break;
        }

        for (unsigned i = 0; i < dim - 1; ++i) {
            fprintf(fp_out, fmt_cstr_1, buf[i]);
        }
        fprintf(fp_out, fmt_cstr_2, buf[dim - 1]);
    }
}

int main(int argc, char** argv) {
    if (argc != 5) {
        printf("Usage: ./bfivecs-add-id <input> <output> <max_dim> [bvecs|fvecs|ivecs]\n");
        return 1;
    }

    const char* input = argv[1];
    const char* output = argv[2];
    int max_dim = atoi(argv[3]);
    const char* type = argv[4];

    FILE* fp_in = fopen(input, "rb");
    FILE* fp_out = fopen(output, "wb");

    if (!strcmp(type, "bvecs")) {
        bfivecs_to_txt<uint8_t>(fp_in, fp_out, max_dim, "%" PRIu8);
    } else if (!strcmp(type, "fvecs")) {
        bfivecs_to_txt<float>(fp_in, fp_out, max_dim, "%.1f");
    } else if (!strcmp(type, "ivecs")) {
        bfivecs_to_txt<int32_t>(fp_in, fp_out, max_dim, "%" PRIi32);
    }

    fclose(fp_out);
    fclose(fp_in);
}

