#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIO_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_GRADES 5

typedef struct {
  char fio[MAX_FIO_LENGTH];
  int group;
  char address[MAX_ADDRESS_LENGTH];
  float grades[MAX_GRADES];
} Student;

void printMenu() {
  printf("Меню:\n");
  printf("1. Прочитать из файл\n");
  printf("2. Записать в файл\n");
  printf("3. Создать список\n");
  printf("4. Просмотреть список\n");
  printf("5. Добавить абитуриента\n");
  printf("6. Линейный поиск\n");
  printf("7. Сортировка прямым выбором\n");
  printf("8. Сортировка QuickSort\n");
  printf("9. Двоичный поиск\n");
  printf("10. Задание\n");
  printf("11. Выход\n");
}
void createFile(Student **students, int *n) {
  printf("Введите количество абитуриентов: ");
  scanf("%d", n);
  if (!*students)
    free(*students);
  *students = (Student *)malloc((*n) * sizeof(Student));
  for (int i = 0; i < *n; i++) {
    printf("Введите ФИО абитуриента %d: ", i + 1);
    scanf("%s", (*students)[i].fio);
    printf("Введите номер группы абитуриента %d: ", i + 1);
    scanf("%d", &(*students)[i].group);
    printf("Введите адрес абитуриента %d: ", i + 1);
    scanf("%s", (*students)[i].address);
    printf("Введите оценки абитуриента %d: ", i + 1);
    for (int j = 0; j < MAX_GRADES; j++) {
      scanf("%f", &(*students)[i].grades[j]);
    }
  }
}
void printFile(Student *students, int n) {
  for (int i = 0; i < n; i++) {
    printf("Абитуриент %d:\n", i + 1);
    printf("ФИО: %s\n", students[i].fio);
    printf("Номер группы: %d\n", students[i].group);
    printf("Адрес: %s\n", students[i].address);
    printf("Оценки: ");
    for (int j = 0; j < MAX_GRADES; j++) {
      printf("%f ", students[i].grades[j]);
    }
    printf("\n");
  }
}
void addStudent(Student **students, int *n) {
  *students = (Student *)realloc(*students, ((*n) + 1) * sizeof(Student));
  printf("Введите ФИО нового абитуриента: ");
  scanf("%s", (*students)[*n].fio);
  printf("Введите номер группы нового абитуриента: ");
  scanf("%d", &(*students)[*n].group);
  printf("Введите адрес нового абитуриента: ");
  scanf("%s", (*students)[*n].address);
  printf("Введите оценки нового абитуриента: ");
  for (int j = 0; j < MAX_GRADES; j++) {
    scanf("%f", &(*students)[*n].grades[j]);
  }
  (*n)++;
}
// Function to write students to a file
void writeToFile(Student *students, int n) {
  FILE *file = fopen("students.txt", "w");
  if (file == NULL) {
    printf("Error opening file\n");
    return;
  }
  for (int i = 0; i < n; i++) {
    fprintf(file, "%s %d %s", students[i].fio, students[i].group,
            students[i].address);
    for (int j = 0; j < MAX_GRADES; j++) {
      fprintf(file, " %f", students[i].grades[j]);
    }
    fprintf(file, "\n");
  }
  fclose(file);
} // Function to read students from a file
void readFromFile(Student **students, int *n) {
  FILE *file = fopen("students.txt", "r");
  if (file == NULL) {
    printf("Error opening file\n");
    return;
  }
  *n = 0;
  Student *temp = (Student *)malloc(1 * sizeof(Student));
  while (fscanf(file, "%s %d %s", temp[*n].fio, &temp[*n].group,
                temp[*n].address) == 3) {
    for (int j = 0; j < MAX_GRADES; j++) {
      if (fscanf(file, " %f", &temp[*n].grades[j]) != 1) {
        printf("Error reading file\n");
        free(temp);
        fclose(file);
        return;
      }
    }
    (*n)++;
    temp = (Student *)realloc(temp, (*n + 1) * sizeof(Student));
  }
  *students = temp;
  fclose(file);
}
void linearSearch(Student *students, int n) {
  char fio[MAX_FIO_LENGTH];
  printf("Введите ФИО для поиска: ");
  scanf("%s", fio);
  int found = 0;
  for (int i = 0; i < n; i++)
    if (strcmp(students[i].fio, fio) == 0) {
      printf("Абитуриент найден:\n");
      printf("ФИО: %s\n", students[i].fio);
      printf("Номер группы: %d\n", students[i].group);
      printf("Адрес: %s\n", students[i].address);
      printf("Оценки: ");
      for (int j = 0; j < MAX_GRADES; j++) {
        printf("%f ", students[i].grades[j]);
      }
      printf("\n");
      found = 1;
      break;
    }
  if (!found) {
    printf("Абитуриент не найден\n");
  }
}
void selectionSort(Student *students, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      if (strcmp(students[j].fio, students[minIndex].fio) < 0) {
        minIndex = j;
      }
    }
    Student temp = students[i];
    students[i] = students[minIndex];
    students[minIndex] = temp;
  }
}

int partition(Student *students, int low, int high) {
  Student pivot = students[high];
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (strcmp(students[j].fio, pivot.fio) < 0) {
      i++;
      Student temp = students[i];
      students[i] = students[j];
      students[j] = temp;
    }
  }
  Student temp = students[i + 1];
  students[i + 1] = students[high];
  students[high] = temp;
  return i + 1;
}

void quickSort(Student *students, int low, int high) {
  if (low < high) {
    int pivot = partition(students, low, high);
    quickSort(students, low, pivot - 1);
    quickSort(students, pivot + 1, high);
  }
}

void binarySearch(Student *students, int n) {
  char fio[MAX_FIO_LENGTH];
  printf("Введите ФИО для поиска: ");
  scanf("%s", fio);
  int found = 0;
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (strcmp(students[mid].fio, fio) == 0) {
      printf("Абитуриент найден:\n");
      printf("ФИО: %s\n", students[mid].fio);
      printf("Номер группы: %d\n", students[mid].group);
      printf("Адрес: %s\n", students[mid].address);
      printf("Оценки: ");
      for (int j = 0; j < MAX_GRADES; j++) {
        printf("%f ", students[mid].grades[j]);
      }
      printf("\n");
      found = 1;
      break;
    } else if (strcmp(students[mid].fio, fio) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  if (!found) {
    printf("Абитуриент не найден\n");
  }
}
int countMinskStudents(Student *students, int n) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (strstr(students[i].address, "Minsk") != NULL) {
      float averageGrade = 0;
      for (int j = 0; j < MAX_GRADES; j++) {
        averageGrade += students[i].grades[j];
      }
      averageGrade /= MAX_GRADES;
      if (averageGrade >= 8.5) {
        count++;
      }
    }
  }
  return count;
}
void printMinskStudents(Student *students, int n) {
  Student *minskStudents = (Student *)malloc(n * sizeof(Student));
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (strstr(students[i].address, "Minsk") != NULL) {
      float averageGrade = 0;
      for (int j = 0; j < MAX_GRADES; j++) {
        averageGrade += students[i].grades[j];
      }
      averageGrade /= MAX_GRADES;
      if (averageGrade >= 8.5) {
        minskStudents[count] = students[i];
        count++;
      }
    }
  }
  selectionSort(minskStudents, count);
  for (int i = 0; i < count; i++) {
    printf("%s\n", minskStudents[i].fio);
  }
  free(minskStudents);
}
int main() {
  Student *students = NULL;
  int n = 0;
  int choice;
  while (1) {
    printMenu();
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      readFromFile(&students, &n);\
      break;
    case 2:
      if(students) writeToFile(students, n);
      else printf("Список студентов пуст.\n");
      break;
    case 3:
      createFile(&students, &n);
      break;
    case 4:
      printFile(students, n);
      break;
    case 5:
      addStudent(&students, &n);
      break;
    case 6:
      linearSearch(students, n);
      break;
    case 7:
      selectionSort(students, n);
      break;
    case 8:
      quickSort(students, 0, n - 1);
      break;
    case 9:
      binarySearch(students, n);
      break;
    case 10:
      printf("Количество абитуриентов из Минска с средним баллом не ниже 8.5: "
             "%d\n",
             countMinskStudents(students, n));
      printMinskStudents(students, n);
      break;
    case 11:
      printf("Завершение программы...");
      free(students);
      return 0;
    }
  }
  return 0;
}