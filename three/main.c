#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main() {
	FILE  *f = fopen("input.txt", "r");

	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	char content[200000];
	fread(content, 1, 200000, f);

	int len = strlen(content);

  int sum = 0;

  bool d = true;

	for (int i = 0; i < len - 4; i++) {
      if (strncmp(content + i, "do()", 3) == 0) {
          i += 3;
          d = true;
      } else if (strncmp(content + i, "don't()", 4) == 0) {
          i += 4;
          d = false;
      } else if (d && strncmp(content + i, "mul(", 4) == 0) {

            i += 4;
            int a = 0;
            int b = 0;
            while (content[i] >= '0' && content[i] <= '9') {
               a *= 10;
               a += content[i] - '0';
               i ++;
            }
            if (content[i] == ',') {
                i ++;
                while (content[i] >= '0' && content[i] <= '9') {
                    b *= 10;
                    b += content[i] - '0';
                    i ++;
                }
            }
            if (content[i] != ')') {
                a = 0;
            }

            sum += a * b;
        }
	}

	/*
	char line[20000];

	char *start = line;
	int res = 0;

	while(fgets(line, 20000, f)) {
		int index = 0;
		while(line[index] != '\0' && line[index + 1] != '\0' && line[index + 2] != '\0') {
			if (line[index] == 'm' && line[index+1] == 'u' && line[index+2] == 'l') {
				int a = 0;
				int b = 0;
				if (sscanf(&line[index], "mul(%d,%d)", &a, &b) != -1) {
					printf("Line: %s\n", &line[index]);
					printf("found match: %d %d\n", a,b);
					res += a*b;
				}
			}
			index++;
		}

	}
*/ 
	/*
		char *p = strstr(start, "mul(");

		while (p != NULL || p != '\0') {

			int a = 0;
			int b = 0;

			if (sscanf(start, "%d,%d)", &a, &b) != -1) {
				printf("found match: %d %d\n", a,b);
				printf("Start: %s\n", start);
				res += a*b;
			}
			start += 4;
			p = strstr(start, "mul("); 
		}
	}
	*/
	printf("Final number: %d\n", sum);

	return 0;
}
