#include <stdio.h>
#include <stdlib.h>

int sign(int x)
{
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    return 0;
}

int is_valid(int *a, int n)
{
    int ordering = 0;
    int diff;
    for (int i = 0; i < n - 1; ++i)
    {
        diff = a[i + 1] - a[i];
        if (abs(diff) > 3 || abs(diff) < 1)
            return 0;
        if (ordering != 0 && sign(diff) != ordering)
            return 0;
        if (ordering == 0)
            ordering = sign(diff);
    }
    return 1;
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input>\n", argv[0]);
        exit(1);
    }
    FILE *fp;
    char line[81];
    int linesize, lineprogress;
    int nfields;
    int *report;
    int *abridged;
    int part1 = 0, part2 = 0;
    if ((fp = fopen(argv[1], "rt")) == NULL)
    {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(1);
    }
    int index = 0;
    while (fgets(line, 80, fp) != NULL)
    {
        index++;
        linesize = 0;
        nfields = 1;
        while (line[linesize++] != '\0')
            if (line[linesize] == ' ')
                nfields++;
        report = (int *) malloc(nfields * sizeof(int));
        abridged = (int *) malloc((nfields - 1) * sizeof(int));
        for (int i = 0, lineprogress = 0; i < nfields; ++i)
        {
            if (sscanf(line + lineprogress, "%d", report + i) != 1)
            {
                fprintf(stderr, "Error parsing file %s\n", argv[1]);
                exit(1);
            }
            while (lineprogress < linesize && line[lineprogress++] != ' ')
                ;
        }
        if (is_valid(report, nfields))
        {
            printf("Valid: %d\n", index);
            part1++;
            part2++;
            continue;
        }
        for (int i = 0; i < nfields; ++i)
        {
            for (int j = 0; j < nfields - 1; ++j)
                abridged[j] = report[j + (j>=i)];
            if (is_valid(abridged, nfields - 1))
            {
                part2++;
                break;
            }
        }
        free(report);
        free(abridged);
    }
    fclose(fp);
    printf("%d\n", part1);
    printf("%d\n", part2);
    return 0;
}
