#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char name[110];
char gender[110];
int age;
float height;
int weight;

struct node
{
    char name[110], gender[110];
    int age;
    float height, weight;
};

void input_name()
{
    do
    {
        strcpy(name, "");
        printf("Member username [Must be Unique] [5 - 20 characters]: ");
        scanf("%s", name);
        fflush(stdin);
    } while (strlen(name) < 5 || strlen(name) > 20);
}

void input_gender()
{
    do
    {
        strcpy(gender, "");
        printf("Member gender [Male | Female] (Case Sensitive): ");
        scanf("%s", gender);
        fflush(stdin);

        if (strcmp(gender, "Male") == 0 || strcmp(gender, "Female") == 0)
            return;
    } while (1);
}

void input_age()
{
    do
    {
        age = -1;
        printf("Member age [17 - 40]: ");
        scanf("%d", &age);
        fflush(stdin);
    } while (age < 17 || age > 40);
}

void input_height()
{
    do
    {
        height = -1.0;
        printf("Member height [1.0 - 2.0 m]: ");
        scanf("%f", &height);
        fflush(stdin);
    } while (height < 1.0 || height > 2.0);
}

void input_weight()
{
    do
    {
        weight = -1;
        printf("Member weight [50 - 150 kg]: ");
        scanf("%d", &weight);
        fflush(stdin);
    } while (weight < 50 || weight > 150);
}

float calculate_bmi(float weight, float height)
{
    return weight / (height * height);
}

void total_bmi(float weight, float height)
{
    float bmi = calculate_bmi(weight, height);
    printf("BMI: %.2f\n", bmi);
    // Tampilkan kategori BMI (misal: Underweight, Normal, Overweight, Obese)
    // Berdasarkan nilai BMI yang dihitung.
}

void view_all_members(struct node members[], int count)
{
    if (count == 0)
    {
        printf("No members available.\n");
        return;
    }

    printf("All Members:\n");
    printf("-----------------------------------------------------\n");
    printf("| %-20s | %-10s | %-4s | %-6s | %-6s |\n", "Name", "Gender", "Age", "Height", "Weight");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("| %-20s | %-10s | %-4d | %-6.2f | %-6d |\n",
               members[i].name, members[i].gender, members[i].age, members[i].height, members[i].weight);
    }

    printf("-----------------------------------------------------\n");
}

void delete_member(struct node members[], int *count, const char *nameToDelete)
{
    int found = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(members[i].name, nameToDelete) == 0)
        {
            found = 1;
            // Jika nama ditemukan, pindahkan semua data setelahnya ke posisi saat ini
            for (int j = i; j < *count - 1; j++)
            {
                strcpy(members[j].name, members[j + 1].name);
                strcpy(members[j].gender, members[j + 1].gender);
                members[j].age = members[j + 1].age;
                members[j].height = members[j + 1].height;
                members[j].weight = members[j + 1].weight;
            }
            (*count)--;
            printf("Member '%s' has been deleted.\n", nameToDelete);
            break;
        }
    }
    if (!found)
    {
        printf("Member '%s' not found.\n", nameToDelete);
    }
}

void menu()
{
    puts("BiFit");
    puts("==================");
    puts("1. Add New Member");
    puts("2. View All Member");
    puts("3. Delete Member");
    puts("0. Exit");
    printf("Choose >> ");
}

int main()
{
    struct node members[100]; // Misalkan maksimal 100 member
    int count = 0; // Jumlah anggota saat ini

    int choice;
    do
    {
        menu();
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            input_name();
            input_gender();
            input_age();
            input_height();
            input_weight();
            total_bmi(weight, height);
            strcpy(members[count].name, name);
            strcpy(members[count].gender, gender);
            members[count].age = age;
            members[count].height = height;
            members[count].weight = weight;
            count++;
            break;
        case 2:
            view_all_members(members, count);
            break;
        case 3:
            {
                char nameToDelete[110];
                printf("Enter the name of the member to delete: ");
                scanf("%s", nameToDelete);
                delete_member(members, &count, nameToDelete);
            }
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}

