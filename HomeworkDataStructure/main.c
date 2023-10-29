#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int studentNumber;
    char name[50];
    int age;
    struct Student* next;
};

typedef struct Student Student;

// Kar��la�t�rma i�levi, b�y�kten k����e s�ralamak i�in kullan�l�r
int compareDescending(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// Say�lar� ba�lang�ca tek ve �ift olmak �zere ekleyen i�lev
void addNumbersToList(Student** head) {
    int number;
    Student* newStudent;

    while (1) {
        printf("Bir say� girin (-1 ��k��): ");
        scanf("%d", &number);

        if (number == -1) {
            break;
        }

        newStudent = (Student*)malloc(sizeof(Student));
        newStudent->studentNumber = number;

        printf("��renci ad�n� girin: ");
        scanf("%s", newStudent->name);

        printf("��renci ya��n� girin: ");
        scanf("%d", &newStudent->age);

        newStudent->next = *head;
        *head = newStudent;
    }
}

// Rastgele 100 say�y� listeye ekleyen i�lev
void addRandomNumbersToList(Student** head) {
    for (int i = 0; i < 100; i++) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        newStudent->studentNumber = rand() % 1000;
        strcpy(newStudent->name, "Random");
        newStudent->age = rand() % 20 + 10;
        newStudent->next = *head;
        *head = newStudent;
    }
}

// ��renci numaras�na g�re listeyi b�y�kten k����e s�ralayan i�lev
void sortListDescending(Student** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Student* sorted = NULL;
    Student* current = *head;

    while (current != NULL) {
        Student* next = current->next;

        if (sorted == NULL || current->studentNumber > sorted->studentNumber) {
            current->next = sorted;
            sorted = current;
        } else {
            Student* search = sorted;

            while (search->next != NULL && current->studentNumber < search->next->studentNumber) {
                search = search->next;
            }

            current->next = search->next;
            search->next = current;
        }

        current = next;
    }

    *head = sorted;
}

// ��renci bilgilerini ekrana yazd�ran i�lev
int displayStudentInfo(Student* head) {
    int count = 0;
    while (head != NULL) {
        printf("%d- %s %d %d\n", ++count, head->name, head->age, head->studentNumber);
        head = head->next;
    }
    return count;
}

// �simle ��renci arayan i�lev
Student* searchStudentByName(Student* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// �simle ��renci arayarak sonraki d���m� silen i�lev
void deleteNextNode(Student* head, const char* name) {
    while (head != NULL) {
        if (head->next != NULL && strcmp(head->name, name) == 0) {
            Student* temp = head->next;
            head->next = head->next->next;
            free(temp);
            return;
        }
        head = head->next;
    }
}

// En uzun ismi bulup ekrana yazd�ran i�lev
void printLongestNameRecord(Student* head) {
    int maxNameLength = 0;
    char longestName[50] = "";

    while (head != NULL) {
        if (strlen(head->name) > maxNameLength) {
            maxNameLength = strlen(head->name);
            strcpy(longestName, head->name);
        }
        head = head->next;
    }

    if (maxNameLength > 0) {
        printf("En uzun isim: %s\n", longestName);
        printf("Uzunluk: %d\n", maxNameLength);
    } else {
        printf("Listede kay�t yok.\n");
    }
}

int main() {
    srand(time(NULL)); // Rastgele say� �reticiyi ba�lat

    Student* studentList = NULL;

    // 1. G�rev: Say�lar� tek ve �ift olmak �zere listeye ekle
    addNumbersToList(&studentList);

    // 2. G�rev: Rastgele 100 say�y� listeye ekle
    addRandomNumbersToList(&studentList);

    // 3. G�rev: ��renci numaras�na g�re listeyi b�y�kten k����e s�rala
    sortListDescending(&studentList);

    // 4. G�rev: ��renci bilgilerini ekrana yaz ve ��renci say�s�n� say
    int studentCount = displayStudentInfo(studentList);
    printf("Toplam ��renci say�s�: %d\n", studentCount);

    // 5. G�rev: �simle ��renci ara
    char searchName[50];
    printf("Aranacak bir isim girin: ");
    scanf("%s", searchName);
    Student* foundStudent = searchStudentByName(studentList, searchName);
    if (foundStudent != NULL) {
        printf("��renci bulundu: %s %d %d\n", foundStudent->name, foundStudent->age, foundStudent->studentNumber);
    } else {
        printf("��renci bulunamad�.\n");
    }

    // 6. G�rev: �simle aranan ��rencinin sonraki d���m�n� sil
    printf("Silmek i�in bir isim girin: ");
    scanf("%s", searchName);
    deleteNextNode(studentList, searchName);

    // 7. G�rev: En uzun ismi bulup ekrana yazd�r
    printLongestNameRecord(studentList);

    // Ayr�lan belle�i temizle
    while (studentList != NULL) {
        Student* temp = studentList;
        studentList = studentList->next;
        free(temp);
    }

    return 0;
}
