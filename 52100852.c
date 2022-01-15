#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10000

struct Employee
{
    char *eID;
    char *fName;
    char *lName;
    char *gender;
    char *birth;
    char *depart;
    char *country;
};

struct Progress
{
    char *eID;
    char *pID;
    float pg;
};

struct Employee employee[MAX];
struct Progress progress[MAX];

void low(char *p)
{
    for (; *p; ++p)
        *p = tolower(*p);
}

long setEmployee()
{
    FILE *in;
    char *buf = malloc(500);
    char *tmp;
    char trash[256];
    in = fopen("Employee.csv", "r");
    long i = 0;

    while (fgets(buf, 255, in) != NULL)
    {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 2] <= 32))
        {
            buf[strlen(buf) - 2] = '\0';
        }
        tmp = strtok(buf, ",");
        employee[i].eID = strdup(tmp);

        tmp = strtok(NULL, ",");
        employee[i].fName = strdup(tmp);

        tmp = strtok(NULL, ",");
        employee[i].lName = strdup(tmp);

        tmp = strtok(NULL, ",");
        employee[i].gender = strdup(tmp);

        tmp = strtok(NULL, ",");
        employee[i].birth = strdup(tmp);

        tmp = strtok(NULL, ",");
        employee[i].depart = strdup(tmp);

        tmp = strtok(NULL, ",");
        employee[i].country = strdup(tmp);
        i++;
    }
    fclose(in);
    return i;
}

void getEmployee(long n)
{
    FILE *op;
    op = fopen("result.csv", "wt");
    long i;
    for (i = 1; i < n; i++)
    {
        fprintf(op, "%s,%s,%s,%s,%s,%s,%s\n", employee[i].eID, employee[i].fName, employee[i].lName, employee[i].gender, employee[i].birth, employee[i].depart, employee[i].country);
    }
    fclose(op);
}

long setProgress()
{
    FILE *inp;
    char *buf = malloc(256);
    char *tmp;
    inp = fopen("Progress.csv", "r");

    long i = 0;
    while (fgets(buf, 255, inp) != NULL)
    {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n'))
        {
            buf[strlen(buf) - 1] = '\0';
        }

        tmp = strtok(buf, ",");
        progress[i].eID = strdup(tmp);

        tmp = strtok(NULL, ",");
        progress[i].pID = strdup(tmp);

        tmp = strtok(NULL, ",");
        progress[i].pg = atof(tmp);
        i++;
    }
    fclose(inp);
    return 0;
}

void countDepart(char de[])
{

    long i;
    long c = 0;
    for (i = 1; i <= sizeof(employee); i++)
    {
        if (employee[i].eID != NULL)
        {

            if (strcmp(employee[i].depart, de) == 0)
            {
                c++;
            }
        }
        else
            break;
    }
    FILE *op;
    op = fopen("result.csv", "wt");
    fprintf(op, "%ld", c);
    fclose(op);
}

void listGender(char sex[])
{
    FILE *op;
    op = fopen("result.csv", "w+");
    long i = 0;
    for (i = 1; i < sizeof(employee); i++)
    {

        if (employee[i].eID != NULL)
        {
            if (strcmp(employee[i].gender, sex) == 0)
            {
                fprintf(op, "%s,%s,%s,%s,%s,%s,%s\n", employee[i].eID, employee[i].fName, employee[i].lName, employee[i].gender, employee[i].birth, employee[i].depart, employee[i].country);
            }
        }
        else
            break;
    }
    fclose(op);
}

void reportn(float n)
{
    FILE *op;
    struct Progress temp[MAX];
    long c = 0;
    long j;
    op = fopen("result.csv", "wt");
    long i;
    for (i = 1; i <= sizeof(progress); i++)
    {
        if (progress[i].eID != NULL)
        {
            if (progress[i].pg == n)
            {
                long d = 0;
                for (j = 0; j < c; j++)
                {
                    if (strcmp(progress[i].eID, temp[j].eID) == 0)
                    {
                        d++;
                    }
                }
                if (d == 0)
                {
                    fprintf(op, "%s\n", progress[i].eID);
                    temp[c++] = progress[i];
                }
            }
        }
        else
            break;
    }
    fclose(op);
}

void averageX(char *x)
{
    FILE *op;
    op = fopen("result.csv", "wt");
    long i, d = 0;
    double tb = 0;
    for (i = 1; i <= sizeof(progress); i++)
    {
        if (progress[i].eID != NULL)
        {
            if (strcmp(progress[i].pID, x) == 0)
            {
                d++;
                tb += progress[i].pg;
            }
        }
        else
            break;
    }
    if (d == 0)
    {
        fprintf(op, "%.3lf", d);
    }
    else
    {
        fprintf(op, "%.3lf", tb / d);
    }
    fclose(op);
}

void sortASC(long n)
{
    struct Employee temp;
    char s1[30], s2[30];
    long i, j;
    for (i = 1; i < n; i++)
    {
        if (employee[i].eID != NULL)
        {
            for (j = 1; j < n - i; j++)
            {
                if (employee[j].eID != NULL)
                {
                    strcpy(s1, employee[j].lName);
                    strcpy(s2, employee[j + 1].lName);
                    low(s1);
                    low(s2);
                    if (strcmp(s1, s2) > 0)
                    {
                        temp = employee[j];
                        employee[j] = employee[j + 1];
                        employee[j + 1] = temp;
                    }
                    else if (strcmp(s1, s2) == 0)
                    {
                        strcpy(s1, employee[j].fName);
                        strcpy(s2, employee[j + 1].fName);
                        low(s1);
                        low(s2);
                        if (strcmp(s1, s2) > 0)
                        {
                            temp = employee[j];
                            employee[j] = employee[j + 1];
                            employee[j + 1] = temp;
                        }
                    }
                }
                else
                    break;
            }
        }
        else
            break;
    }
}

void sortDESC(long n)
{
    struct Employee temp;
    long i, j;
    char s1[30], s2[30];
    for (i = 1; i < n; i++)
    {
        if (employee[i].eID != NULL)
        {
            for (j = 1; j < n - i; j++)
            {
                if (employee[j].eID != NULL)
                {
                    strcpy(s1, employee[j].lName);
                    strcpy(s2, employee[j + 1].lName);
                    low(s1);
                    low(s2);
                    if (strcmp(s1, s2) < 0)
                    {
                        temp = employee[j];
                        employee[j] = employee[j + 1];
                        employee[j + 1] = temp;
                    }
                    else if (strcmp(s1, s2) == 0)
                    {
                        strcpy(s1, employee[j].fName);
                        strcpy(s2, employee[j + 1].fName);
                        low(s1);
                        low(s2);
                        if (strcmp(s1, s2) > 0)
                        {
                            temp = employee[j];
                            employee[j] = employee[j + 1];
                            employee[j + 1] = temp;
                        }
                    }
                }
                else
                    break;
            }
        }
        else
            break;
    }
}

void listCountry(char country[])
{
    FILE *op;
    op = fopen("result.csv", "wt");
    long i;
    for (i = 1; i <= sizeof(employee); i++)
    {
        if (employee[i].eID != NULL)
        {
            if (strcmp(employee[i].country, country) == 0)
            {
                fprintf(op, "%s,%s,%s,%s,%s,%s,%s\n", employee[i].eID, employee[i].fName, employee[i].lName, employee[i].gender, employee[i].birth, employee[i].depart, employee[i].country);
            }
        }
        else
            break;
    }
    fclose(op);
}

void wrong()
{
    FILE *fp;
    long ret;
    fp = fopen("check.txt", "wt");
    fprintf(fp, "%s", "wrong syntax");
    fclose(fp);
}

struct Command
{
    char *command;
};

struct Command listC[9];

void setlist()
{
    listC[0].command = "count";
    listC[1].command = "list";
    listC[2].command = "report";
    listC[3].command = "average";
    listC[4].command = "sort";
    listC[5].command = "country";
}

long checkn(char *s)
{
    long len = strlen(s), i, dot = 0;

    for (i = 0; i < len - 1; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            if (s[i] == '.' && dot < 1)
            {
                dot++;
                continue;
            }
            return 0;
        }
    }
    return 1;
}

long checkcmd(char *s)
{
    long i, space = 0;
    if (s[0] == ' ' || s[strlen(s) - 2] == ' ')
    {
        return 0;
    }
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            space++;
        }
    }
    return space;
}

int main(int argc, char const *argv[])
{

    char buf[255], *tmp, *control, *command;
    long i, cmd = -1, space = 0, len;
    float n;
    len = setEmployee();
    setProgress();
    fgets(buf, 255, stdin);
    if (checkcmd(buf) == 1)
    {
        low(buf);
        tmp = strtok(buf, " ");
        command = strdup(tmp);
        tmp = strtok(NULL, " ");
        control = strdup(tmp);
        if (control[strlen(control) - 1] < 32)
        {
            control[strlen(control) - 1] = '\0';
        }
        setlist();
        for (i = 0; i < 6; i++)
        {
            if (strcmp(command, listC[i].command) == 0)
            {
                cmd = i;
            }
        }

        switch (cmd)
        {
        case 0:
            countDepart(control);
            break;
        case 1:
            if (strcmp(control, "male") == 0 || strcmp(control, "female") == 0)
            {
                control[0] = toupper(control[0]);
                listGender(control);
            }
            else
            {
                wrong();
            }
            break;
        case 2:
            if (checkn(control) == 1)
            {
                n = atof(control);
                if (n < 0 || n > 1)
                {
                    wrong();
                    break;
                }
                reportn(n);
            }
            else
            {
                wrong();
            }
            break;
        case 3:
            averageX(control);
            break;
        case 4:
            if (strcmp(control, "asc") == 0)
            {
                sortASC(len);
                getEmployee(len);
            }
            else if (strcmp(control, "desc") == 0)
            {
                sortDESC(len);
                getEmployee(len);
            }
            else
            {
                wrong();
            }
            break;
        case 5:
            control[0] = toupper(control[0]);
            listCountry(control);
            break;
        default:
            wrong();
            break;
        }
    }
    else
    {
        wrong();
    }
    return 0;
}
