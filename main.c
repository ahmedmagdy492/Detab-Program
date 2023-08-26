#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB_STOP_WIDTH 8

char* detab(char* input, int len);
char** split(char* line, int len, int* out_len);

// \tone\ntwo\tthree\nsixteen\tseventeen\teighteen\n

int main() {
    int len = strlen("\tone\ntwo\tthree\nsixteen\tseventeen\teighteen\n");
    char* str = (char*)malloc(sizeof(char) * len + 1);
    
    if (!str)
        exit(EXIT_FAILURE);

    memset(str, 0, len + 1);
    memcpy(str, "\tone\ntwo\tthree\nsixteen\tseventeen\teighteen\n", len);

    int split_len = 0;

    char** result = split(str, len, &split_len);

    int i;

    for(i = 0; i < split_len; ++i) {
      char* newStr = detab(result[i], len);
      printf("%s\n", newStr);
      free(newStr);
    }
   

    free(result);
    free(str);
}

char* detab(char* input, int len) {
    int arr_len = 0, i, newStrCounter;
    newStrCounter = 0;

    char* newStr = (char*)malloc(sizeof(char) * (len + TAB_STOP_WIDTH*arr_len + 1));

    if (!newStr)
        exit(EXIT_FAILURE);

    memset(newStr, 0, len + 1);

    for (i = 0; i < len; ++i) {
        if (input[i] == '\t') {
            int j;
            int nOfSpaces;
            nOfSpaces = TAB_STOP_WIDTH - ((i-1)%TAB_STOP_WIDTH);
            if (nOfSpaces > 4) {
                nOfSpaces = TAB_STOP_WIDTH - (i % TAB_STOP_WIDTH);
            }
            for (j = 0; j < nOfSpaces; ++j) {
                newStr[newStrCounter + j] = '.';
            }
            newStrCounter += nOfSpaces;
        }
        else {
            newStr[newStrCounter] = input[i];
            ++newStrCounter;
        }
    }

    return newStr;
}

char** split(char* line, int line_len, int* out_len) {
  int len, i, counter;
  len = 1;
  counter = 0;

  for(i =0; i < line_len; ++i) {
    if(i != 0 && i != line_len-1) {
      if(line[i] == '\n') {
	++len;
      }
    }
  }

  *out_len = len;

  char** arr;
  arr = (char**)malloc(sizeof(char*)*len);

  char* temp = strtok(line, "\n");

  while(temp != NULL) {
    arr[counter] = temp;
    ++counter;
    temp = strtok(NULL, "\n");
  }

  return arr;
}
