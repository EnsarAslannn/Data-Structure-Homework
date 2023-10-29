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

// Karşılaştırma işlevi, büyükten küçüğe sıralamak için kullanılır
int compareDescending(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// Sayıları başlangıca tek ve çift olmak üzere ekleyen işlev
void addNumbersToList(Student** head) {
    int number;
    Student* newStudent;

    while (1) {
        printf("Bir sayı girin (-1 çıkış): ");
        scanf("%d", &number);

        if (number == -1) {
            break;
        }

        newStudent = (Student*)malloc(sizeof(Student));
        newStudent->studentNumber = number;

        printf("Öğrenci adını girin: ");
        scanf("%s", newStudent->name);

        printf("Öğrenci yaşını girin: ");
        scanf("%d", &newStudent->age);

        newStudent->next = *head;
        *head = newStudent;
    }
}

// Rastgele 100 sayıyı listeye ekleyen işlev
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

// Öğrenci numarasına göre listeyi büyükten küçüğe sıralayan işlev
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

// Öğrenci bilgilerini ekrana yazdıran işlev
int displayStudentInfo(Student* head) {
    int count = 0;
    while (head != NULL) {
        printf("%d- %s %d %d\n", ++count, head->name, head->age, head->studentNumber);
        head = head->next;
    }
    return count;
}

// İsimle öğrenci arayan işlev
Student* searchStudentByName(Student* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// İsimle öğrenci arayarak sonraki düğümü silen işlev
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

// En uzun ismi bulup ekrana yazdıran işlev
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
        printf("Listede kayıt yok.\n");
    }
}

int main() {
    srand(time(NULL)); // Rastgele sayı üreticiyi başlat

    Student* studentList = NULL;

    // 1. Görev: Sayıları tek ve çift olmak üzere listeye ekle
    addNumbersToList(&studentList);

    // 2. Görev: Rastgele 100 sayıyı listeye ekle
    addRandomNumbersToList(&studentList);

    // 3. Görev: Öğrenci numarasına göre listeyi büyükten küçüğe sırala
    sortListDescending(&studentList);

    // 4. Görev: Öğrenci bilgilerini ekrana yaz ve öğrenci sayısını say
    int studentCount = displayStudentInfo(studentList);
    printf("Toplam öğrenci sayısı: %d\n", studentCount);

    // 5. Görev: İsimle öğrenci ara
    char searchName[50];
    printf("Aranacak bir isim girin: ");
    scanf("%s", searchName);
    Student* foundStudent = searchStudentByName(studentList, searchName);
    if (foundStudent != NULL) {
        printf("Öğrenci bulundu: %s %d %d\n", foundStudent->name, foundStudent->age, foundStudent->studentNumber);
    } else {
        printf("Öğrenci bulunamadı.\n");
    }

    // 6. Görev: İsimle aranan öğrencinin sonraki düğümünü sil
    printf("Silmek için bir isim girin: ");
    scanf("%s", searchName);
    deleteNextNode(studentList, searchName);

    // 7. Görev: En uzun ismi bulup ekrana yazdır
    printLongestNameRecord(studentList);

    // Ayrılan belleği temizle
    while (studentList != NULL) {
        Student* temp = studentList;
        studentList = studentList->next;
        free(temp);
    }

    return 0;
}
