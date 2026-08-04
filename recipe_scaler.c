#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256
#define MAX_INGREDIENTS 20
#define NAME_SIZE 80
#define UNIT_SIZE 24

typedef struct {
    char name[NAME_SIZE];
    char unit[UNIT_SIZE];
    long double quantity;
} Ingredient;

static int read_positive_value(const char *prompt, long double *value)
{
    char input[INPUT_SIZE];
    char *end;
    long double parsed;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtold(input, &end);
    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (errno == ERANGE || end == input || *end != '\0' ||
        !isfinite(parsed) || parsed <= 0.0L) {
        return -1;
    }

    *value = parsed;
    return 1;
}

static int read_ingredient_count(const char *prompt, int *value)
{
    char input[INPUT_SIZE];
    char *end;
    long parsed;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtol(input, &end, 10);
    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (errno == ERANGE || end == input || *end != '\0' || parsed < 1 ||
        parsed > MAX_INGREDIENTS) {
        return -1;
    }

    *value = (int)parsed;
    return 1;
}

static int read_text(const char *prompt, char *value, size_t value_size)
{
    char input[INPUT_SIZE];
    char *start;
    char *end;
    int character;
    size_t length;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        do {
            character = getchar();
        } while (character != '\n' && character != EOF);
        return -1;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    end = start + strlen(start);
    while (end > start && isspace((unsigned char)end[-1])) {
        end--;
    }

    length = (size_t)(end - start);
    if (length == 0 || length >= value_size) {
        return -1;
    }

    memcpy(value, start, length);
    value[length] = '\0';
    return 1;
}

int main(void)
{
    Ingredient ingredients[MAX_INGREDIENTS];
    long double original_servings;
    long double target_servings;
    long double scale;
    int ingredient_count;
    int status;
    int i;

    puts("레시피 용량 조절기");
    puts("원래 인분과 원하는 인분에 맞춰 여러 재료의 양을 조절합니다.\n");

    status = read_positive_value("기존 레시피 인분: ", &original_servings);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "기존 인분은 0보다 큰 숫자로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_positive_value("만들 인분: ", &target_servings);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "만들 인분은 0보다 큰 숫자로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    scale = target_servings / original_servings;
    if (!isfinite(scale)) {
        fputs("계산 배율이 너무 큽니다. 인분을 확인하세요.\n", stderr);
        return 1;
    }

    status = read_ingredient_count("재료 수(1~20): ", &ingredient_count);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "재료 수는 1부터 20 사이의 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    for (i = 0; i < ingredient_count; i++) {
        char prompt[80];

        printf("\n[재료 %d]\n", i + 1);
        snprintf(prompt, sizeof(prompt), "재료 %d 이름: ", i + 1);
        status = read_text(prompt, ingredients[i].name,
                           sizeof(ingredients[i].name));
        if (status == 1) {
            status = read_positive_value("기존 수량: ",
                                         &ingredients[i].quantity);
        }
        if (status == 1) {
            status = read_text("단위(예: g, ml, 개): ", ingredients[i].unit,
                               sizeof(ingredients[i].unit));
        }

        if (status != 1) {
            fputs(status == 0 ? "입력이 종료되었습니다.\n"
                              : "재료명, 수량 또는 단위 입력이 올바르지 않습니다.\n",
                  stderr);
            return status == 0 ? 0 : 1;
        }

        ingredients[i].quantity *= scale;
        if (!isfinite(ingredients[i].quantity)) {
            fputs("조절한 재료 수량이 너무 큽니다. 입력값을 확인하세요.\n",
                  stderr);
            return 1;
        }
    }

    puts("\n[조절 결과]");
    printf("배율: %.2Lf배\n", scale);
    for (i = 0; i < ingredient_count; i++) {
        printf("%s: %.2Lf %s\n", ingredients[i].name,
               ingredients[i].quantity, ingredients[i].unit);
    }

    return 0;
}
