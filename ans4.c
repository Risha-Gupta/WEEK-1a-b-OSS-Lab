#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_LEN 50

int main() {
    char paragraph[1000], words[MAX_WORDS][MAX_LEN];
    int count[MAX_WORDS] = {0}, i, j, k, n = 0;
    char word[MAX_LEN];

    printf("Enter a paragraph:\n");
    fgets(paragraph, sizeof(paragraph), stdin);
    paragraph[strcspn(paragraph, "\n")] = '\0';

    for (i = 0; paragraph[i]; i++)
        paragraph[i] = tolower(paragraph[i]);

    i = 0;
    while (paragraph[i] != '\0') {
        while (!isalpha(paragraph[i]) && paragraph[i] != '\0')
            i++;
        if (paragraph[i] == '\0') break;
        j = 0;
        while (isalpha(paragraph[i])) {
            word[j++] = paragraph[i++];
        }
        word[j] = '\0';
        for (k = 0; k < n; k++) {
            if (strcmp(words[k], word) == 0) {
                count[k]++;
                break;
            }
        }
        if (k == n) {
            strcpy(words[n], word);
            count[n] = 1;
            n++;
        }
    }

    for (i = 0; i < n; i++)
        printf("%s: %d\n", words[i], count[i]);

    return 0;
}
