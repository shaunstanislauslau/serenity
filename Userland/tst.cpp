#include <LibC/stdio.cpp>

int main(int argc, char** argv)
{
    printf("Counting to 100000: \033[s");
    for (unsigned i = 0; i <= 100000; ++i) {
        printf("\033[u\033[s%u", i);
    }
    printf("\n");
    return 0;
}