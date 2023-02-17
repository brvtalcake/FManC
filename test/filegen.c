#include <stdio.h>
#include <limits.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    unsigned long long size = 0;
    unsigned char cpt = 0;

    srand(time(NULL));
    FILE *file1 = fopen("plain_text_data/gen.txt", "wb+");
    FILE *file2 = fopen("plain_text_data/gen2.txt", "wb+");
    if (file1 == NULL || file2 == NULL) return 1;
    unsigned char to_write = 0;
    for (; cpt <= 2; ++cpt)
    {
        size = 0;
        for (; size < ULLONG_MAX; ++size)
        {
            to_write = (rand() % ((int)'z' - (int)'a' + 1)) + (int)'a';
            fputc(to_write, file1);
            fputc(to_write, file2);
        }
    }

    fputc('\0', file1);
    fputc('\xc3', file2);
    fputc('\xa9', file2);
    fputc('\0', file2);

    fclose(file1);
    fclose(file2);

    return 0;
}