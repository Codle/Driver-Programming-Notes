#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE* dev_file = fopen("/dev/char_dev", "r+");
    char test_str[50] = "hello world";
    char retr_str[50];
    int k;
    fwrite(test_str, strlen(test_str), 1, dev_file);
    fseek(dev_file, 0L, SEEK_SET);
    fread(retr_str, 100, 1, dev_file);
    printf("%s\n", retr_str);
    fclose(dev_file);
}