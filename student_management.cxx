#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent() {
    FILE *fp = fopen("students.txt", "a");
    struct Student s;

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    printf("\n---- Student Records ----\n");

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        printf("\nID: %d\nName: %s\nAge: %d\nMarks: %.2f\n", s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int searchID, found = 0;

    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchID);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        if (s.id == searchID) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nMarks: %.2f\n", s.id, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) printf("\nStudent not found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int deleteID, found = 0;

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &deleteID);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        if (s.id != deleteID)
            fprintf(temp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) printf("\nRecord deleted successfully!\n");
    else printf("\nStudent not found!\n");
}

void updateStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int updateID, found = 0;

    printf("\nEnter Student ID to update: ");
    scanf("%d", &updateID);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        if (s.id == updateID) {
            printf("\nEnter new Name: ");
            scanf("%s", s.name);
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fprintf(temp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) printf("\nRecord updated successfully!\n");
    else printf("\nStudent not found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n\n---- Student Management System ----\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice, try again!\n");
        }
    }

    return 0;
}