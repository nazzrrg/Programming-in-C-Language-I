#include <stdio.h>
// дан класс учеников. колияество учеников произвольное
// для каждого имеется информация об оценке за 1 и 2 полугодие
// написать функцию которая возвращает для каждого семестра среднюю оценку
// найти для каждого ученика среднюю оценку по полугодиям и вернуть макс минус мин

struct student_marks{
    int semester_1;
    int semester_2;
};

struct average_marks{
    float semester_1;
    float semester_2;
    float max_min_difference;
};

float avg(int a, int b) {
    return (float)(a + b)/2;
}

struct average_marks evaluate(struct student_marks* students, size_t array_size) {
    struct average_marks result;
    result.semester_1 = 0;
    result.semester_2 = 0;
    result.max_min_difference = 0;
    float min_mark;
    float max_mark;

    if (array_size > 0 && students != NULL) {
        min_mark = avg(students[0].semester_1, students[0].semester_2);
        max_mark = min_mark;
    }

    for (size_t i = 0; i < array_size; ++i) {
        float average = avg(students[i].semester_1, students[i].semester_2);
        if (average > max_mark) max_mark = average;
        if (average < min_mark) min_mark = average;

        result.semester_1 += (float)students[i].semester_1;
        result.semester_2 += (float)students[i].semester_2;
    }

    result.semester_1 /= array_size;
    result.semester_2 /= array_size;
    result.max_min_difference = max_mark - min_mark;

    return result;
}

int main() {

    return 0;
}