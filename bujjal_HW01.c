#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student_data{
    char first_name[100];
    char last_name[100];
    char advisor[100];
    int ta;
    float gpa;
    int credit;
    char major[100];
    char degree[100];
}Data;

void totaDegrees(Data [1024], int);
void gpaAverage(Data [1024], int);
void advisorCount(Data [1024], int);
void creditAverage(Data [1024], int);
void top3students(Data [1024], int);

int main()
{
    char filename[] = "students_database.csv"; //Enter the path to your student_database.csv file
    FILE* file = fopen(filename, "r");

    if (file==NULL){
        printf("Please check if you have given correct path to the file as we are not able to access this file.\n");
        return 0;
    }

    printf("Reading the .csv file.....\n\n\n");
    Data data[1024];
    int qnty = 0;
    char line[512];
    int flag = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        int i = 0;

        if(!flag) {
            flag = 1;
            continue;
        }

        char *data_entry;
        data_entry  = strtok(line, ",");
        while(data_entry!=NULL){
            // printf("%s ", data_entry);
            if(i==0){
                strcpy(data[qnty].first_name, data_entry);
            }
            if(i==1){
                strcpy(data[qnty].last_name, data_entry);
            }
            if(i==2){
                strcpy(data[qnty].major, data_entry);
            }
            if(i==3){
                strcpy(data[qnty].degree, data_entry);
            }
            if(i==4){
                data[qnty].gpa =  atof(data_entry);
            }
            if(i==5){
                data[qnty].credit =  atoi(data_entry);
            }
            if(i==6){
                if(strcmp(data_entry, "Yes")==0) data[qnty].ta = 1;
                else data[qnty].ta = 0;
            }
            if(i==7){
                strcpy(data[qnty].advisor, data_entry);
            }
            data_entry = strtok(NULL, ",");
            i+=1;
        }
        qnty+=1;
    }
    fclose(file);

    totaDegrees(data, qnty);
    top3students(data, qnty);
    creditAverage(data, qnty);
    gpaAverage(data, qnty);
    advisorCount(data, qnty);
    return 0;
}

void totaDegrees(Data data[1024], int qnty){
    Data dummy;
    int i = 0;
    while(i< qnty){
        int j = 0;
        while(j+i < qnty-1){
            if(strcmp(data[j].degree, data[j+1].degree)>0){
                dummy = data[j];
                data[j] = data[j+1];
                data[j+1] = dummy;
            }
            j+=1;
        }
        i+=1;
    }
    printf("Different degrees are:\n");
    if(strcmp(data[0].degree, "Undeclared")){
        printf("%s\n", data[0].degree);
    }
    for(int i=1;i<qnty;i++){
        // printf("%s\n", data[i].degree);
        if(strcmp(data[i].degree, data[i-1].degree)!=0 && strcmp(data[i].degree, "Undeclared")!=0){
            printf("%s\n", data[i].degree);
        }
    }
    printf("\n\n");
}

void top3students(Data data[1024], int qnty){
    printf("Top 3 students are: \n");
    int i, j;
    Data dummy;
    for (i = 0;  i < qnty; i++)
    {
        for (j = 0; j < qnty - i; j++)
        {
            if (data[j].gpa > data[j+1].gpa){
                dummy = data[j];
                data[j] = data[j+1];
                data[j+1] = dummy;
            }
        }
    }
    for(int i=qnty-1; i>=qnty-3; i--){
        printf("%d] %s %s\n", qnty-i, data[i].first_name, data[i].last_name);
    }
    printf("\n\n");
}

void creditAverage(Data data[1024], int qnty){
    printf("Average Credit: ");
    double added_credit = 0;
    for(int i=0;i<qnty;i++)
        added_credit += data[i].credit;
    double average_credit = added_credit/qnty;
    printf("%lf.\n", average_credit);
    printf("\n\n");
}

void gpaAverage(Data data[1024], int qnty){
    printf("Average GPA: ");
    double added_gpa = 0, total_enrolled = 0;
    for(int i=0;i<qnty;i++){
        if(strcmp("Computer Science", data[i].major)==0){
            total_enrolled += 1;
            added_gpa += data[i].gpa;
        }
    }
    double average_gpa = added_gpa/total_enrolled;
    printf("%lf.\n", average_gpa);
    printf("\n\n");
}

void advisorCount(Data data[1024], int qnty){
    printf("Departments along with the total number of advisors: \n");
    Data dummy;
    int i = 0;
    while(i< qnty){
        int j = 0;
        while(j+i < qnty-1){
            if(strcmp(data[j].major, data[j+1].major)==0 && strcmp(data[j].advisor, data[j+1].advisor)>0){
                dummy = data[j];
                data[j] = data[j+1];
                data[j+1] = dummy;
            }
            else if(strcmp(data[j].major, data[j+1].major)>0){
                dummy = data[j];
                data[j] = data[j+1];
                data[j+1] = dummy;
            }
            j+=1;
        }
        i+=1;
    }
    int prev=0;
     i=1;
    while(i <= qnty){
        int cnt=1;
        if(i==qnty || strcmp(data[i].major, data[i-1].major)){
            int j = prev+1;
            while(j<i){
                if(strcmp(data[j].advisor, data[j-1].advisor)){
                    cnt+=1;
                }
                j+=1;
            }
            prev = i;
            printf("%s: %d\n", data[i-1].major, cnt);
        }
        i+=1;
    }
}


