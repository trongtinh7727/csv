#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000

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

struct Project
{
    char *pID;
    char *pName;
    int week;
};

struct Progress
{
    char *eID;
    char *pID;
    float pg;
};

struct Employee employee[MAX];
struct Project project[MAX];
struct Progress progress[MAX];

int setEmployee()
{
    FILE *in;
    char *buf = malloc(1024);
    char *tmp;
    char trash[256];
    if (buf == NULL)
    {
        printf("No memory\n");
        return 1;
    }
    if ((in = fopen("Employee.csv", "r")) == NULL) // Reading a file
    {
        printf("File could not be opened.\n");
    }
    int i = 0;

    while (fgets(buf, 255, in) != NULL)
    {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n'))
        {
            buf[strlen(buf) - 1] = '\0';
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

void getEmployee(int n)
{
    FILE *op;
    op = fopen("result.csv", "wt");
    int i;
    for (i = 0; i <= n; i++)
    {
        fprintf(op, "%s,%s,%s,%s,%s,%s,%s", employee[i].eID, employee[i].fName, employee[i].lName, employee[i].gender, employee[i].birth, employee[i].depart, employee[i].country);
    }
    fclose(op);
}

int setProject()
{
    FILE *inp;
    char *buf = malloc(256);
    char *tmp;
    if (buf == NULL)
    {
        printf("No memory\n");
        return 1;
    }

    if ((inp = fopen("Project.csv", "r")) == NULL)
    {
        printf("File could not be opened.\n");
    }

    int i = 0;
    while (fgets(buf, 255, inp) != NULL)
    {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n'))
            buf[strlen(buf) - 1] = '\0';

        tmp = strtok(buf, ",");
        project[i].pID = strdup(tmp);

        tmp = strtok(NULL, ",");
        project[i].pName = strdup(tmp);

        tmp = strtok(NULL, ",");
        project[i].week = atoi(tmp);
        i++;
    }
    fclose(inp);
    return 0;
}

void getProject()
{

    int i;

    for (i = 0; i <= sizeof(project); i++)
    {
        if (project[i].pID != NULL)
            printf("%s\t%s\t%d\n", project[i].pID, project[i].pName, project[i].week);
        else
            break;
    }
}

int setProgress()
{
    FILE *inp;
    char *buf = malloc(256);
    char *tmp;
    if (buf == NULL)
    {
        printf("No memory\n");
        return 1;
    }

    if ((inp = fopen("Progress.csv", "r")) == NULL)
    {
        printf("File could not be opened.\n");
    }

    int i = 0;
    while (fgets(buf, 255, inp) != NULL)
    {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n'))
            buf[strlen(buf) - 1] = '\0';

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

void getProgress()
{
    int i;

    for (i = 0; i <= sizeof(progress); i++)
    {
        if (progress[i].pID != NULL)
            printf("%s\t%s\t%f\n", progress[i].eID, progress[i].pID, progress[i].pg);
        else
            break;
    }
}

void countDepart(char de[])
{

    int i;
    long c = 0;
    for (i = 0; i <= sizeof(employee); i++)
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
    int i;
    for (i = 0; i <= sizeof(employee); i++)
    {

        if (employee[i].eID != NULL)
        {
            if (strcmp(employee[i].gender, sex) == 0)
            {
                fprintf(op, "%s,%s,%s,%s,%s,%s,%s", employee[i].eID, employee[i].fName, employee[i].lName, employee[i].gender, employee[i].birth, employee[i].depart, employee[i].country);
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
    op = fopen("result.csv", "wt");
    int i;
    for (i = 0; i <= sizeof(progress); i++)
    {
        if (progress[i].eID != NULL)
        {
            if (progress[i].pg == n)
            {
                fprintf(op, "%s\n", progress[i].eID);
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
    int i, d = 0;
    float tb = 0;
    for (i = 0; i <= sizeof(progress); i++)
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
    fprintf(op, "%.3f", tb / d);
    fclose(op);
}

void sortASC(int n)
{
    struct Employee temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        if (employee[i].eID != NULL)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (employee[j].eID != NULL)
                {
                    if (strcmp(employee[j].lName, employee[j + 1].lName) > 0)
                    {
                        temp = employee[j];
                        employee[j] = employee[j + 1];
                        employee[j + 1] = temp;
                    }
                    else if (strcmp(employee[j].lName, employee[j + 1].lName) == 0)
                    {
                        if (strcmp(employee[j].fName, employee[j + 1].fName) > 0)
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

void sortDESC(int n)
{
    struct Employee temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        if (employee[i].eID != NULL)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (employee[j].eID != NULL)
                {
                    if (strcmp(employee[j].lName, employee[j + 1].lName) < 0)
                    {
                        temp = employee[j];
                        employee[j] = employee[j + 1];
                        employee[j + 1] = temp;
                    }
                    else if (strcmp(employee[j].lName, employee[j + 1].lName) == 0)
                    {
                        if (strcmp(employee[j].fName, employee[j + 1].fName) > 0)
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
    int i;
    for (i = 0; i <= sizeof(employee); i++)
    {
        if (employee[i].eID != NULL)
        {
            if (employee[i].country[strlen(employee[i].country)-1] <=32)
            {
                employee[i].country[strlen(employee[i].country)-1]='\0';
            } 
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

int creatfa(long c)
{
    FILE *fp;
    int ret;
    fp = fopen("result.csv", "wt");
    fprintf(fp, "%ld", c);
    fclose(fp);
}

void wrong()
{
    FILE *fp;
    int ret;
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

int checkn(char *s)
{
    int len = strlen(s), i, dot = 0;
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

int checkcmd(char *s)
{
    int i, space = 0;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            space++;
        }
    }
    return space;
}

void low(char *p)
{
    for (; *p; ++p)
        *p = tolower(*p);
}

int main(int argc, char const *argv[])
{

    char buf[255], *tmp, *control, *command;
    int i, cmd = -1, space = 0, len;
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
        if (control[strlen(control)-1]< 32)
        {
            control[strlen(control)-1]='\0';
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
            printf("%s",control);
            countDepart(control);
            break;
        case 1:
            if (strcmp(control, "male") == 0 || strcmp(control, "female") != 0)
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
