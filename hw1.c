#include <stdio.h>
#include <string.h>

int main(void) {
    char a[100], b[100], c[200];
    memset(c, 0, 200);
    scanf("%s %s", a, b);
    int n = strlen(a), m = strlen(b);
    int top = m + n - 2;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--){
            char digit_a = a[i] - '0';
            char digit_b = b[j] - '0';
            c[top - (i + j)] += (digit_a * digit_b);
            if (c[top - (i + j)] >= 10) {
                c[top - (i + j) + 1] += c[top - (i + j)] / 10;
                c[top - (i + j)] = c[top - (i + j)] % 10;
            }
        }
    }
    for (int i = top; i >= 0; i--)
        printf("%c\n", c[i] + '0');
    return 0;
}
