#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 128
#define UNIT_SIZE 24

enum {
    LENGTH = 1,
    WEIGHT = 2,
    TEMPERATURE = 3
};

static int read_integer(const char *prompt, long long *value)
{
    char input[INPUT_SIZE];
    char *end;
    long long parsed;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoll(input, &end, 10);
    while (isspace((unsigned char)*end)) {
        end++;
    }
    if (errno == ERANGE || end == input || *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 1;
}

static int read_number(const char *prompt, long double *value)
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
        !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 1;
}

static int read_unit(const char *prompt, char *unit)
{
    char input[INPUT_SIZE];
    char *start;
    char *end;
    size_t length;
    size_t i;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
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
    if (length == 0 || length >= UNIT_SIZE) {
        return -1;
    }

    memcpy(unit, start, length);
    unit[length] = '\0';
    for (i = 0; i < length; i++) {
        unit[i] = (char)tolower((unsigned char)unit[i]);
    }

    return 1;
}

static int find_unit(int category, const char *unit, long double *factor)
{
    if (category == LENGTH) {
        if (strcmp(unit, "mm") == 0) {
            *factor = 0.001L;
        } else if (strcmp(unit, "cm") == 0) {
            *factor = 0.01L;
        } else if (strcmp(unit, "m") == 0) {
            *factor = 1.0L;
        } else if (strcmp(unit, "km") == 0) {
            *factor = 1000.0L;
        } else if (strcmp(unit, "in") == 0) {
            *factor = 0.0254L;
        } else if (strcmp(unit, "ft") == 0) {
            *factor = 0.3048L;
        } else {
            return 0;
        }
    } else if (category == WEIGHT) {
        if (strcmp(unit, "mg") == 0) {
            *factor = 0.001L;
        } else if (strcmp(unit, "g") == 0) {
            *factor = 1.0L;
        } else if (strcmp(unit, "kg") == 0) {
            *factor = 1000.0L;
        } else if (strcmp(unit, "lb") == 0) {
            *factor = 453.59237L;
        } else if (strcmp(unit, "oz") == 0) {
            *factor = 28.349523125L;
        } else {
            return 0;
        }
    } else if (category == TEMPERATURE) {
        if (strcmp(unit, "c") == 0 || strcmp(unit, "celsius") == 0 ||
            strcmp(unit, "섭씨") == 0) {
            *factor = 0.0L;
        } else if (strcmp(unit, "f") == 0 || strcmp(unit, "fahrenheit") == 0 ||
                   strcmp(unit, "화씨") == 0) {
            *factor = 1.0L;
        } else {
            return 0;
        }
    } else {
        return 0;
    }

    return 1;
}

static long double convert_temperature(long double value, long double from,
                                        long double to)
{
    long double celsius = from == 0.0L ? value : (value - 32.0L) * 5.0L / 9.0L;

    return to == 0.0L ? celsius : celsius * 9.0L / 5.0L + 32.0L;
}

int main(void)
{
    long long category;
    long double value;
    long double from_factor;
    long double to_factor;
    long double result;
    char from_unit[UNIT_SIZE];
    char to_unit[UNIT_SIZE];
    int status;

    puts("단위 변환기");
    puts("1. 길이(mm, cm, m, km, in, ft)");
    puts("2. 무게(mg, g, kg, lb, oz)");
    puts("3. 온도(c, f)");

    status = read_integer("분야 선택: ", &category);
    if (status != 1 || category < LENGTH || category > TEMPERATURE) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "분야는 1부터 3 사이의 정수로 선택하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_number("변환할 값: ", &value);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "값은 숫자로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }
    if (category != TEMPERATURE && value < 0.0L) {
        fputs("길이와 무게는 음수로 입력할 수 없습니다.\n", stderr);
        return 1;
    }

    status = read_unit("현재 단위: ", from_unit);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "현재 단위가 올바르지 않습니다.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }
    status = read_unit("변환할 단위: ", to_unit);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "변환 단위가 올바르지 않습니다.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    if (!find_unit((int)category, from_unit, &from_factor) ||
        !find_unit((int)category, to_unit, &to_factor)) {
        fputs("선택한 분야에 맞는 단위를 입력하세요.\n", stderr);
        return 1;
    }

    if (category == TEMPERATURE) {
        result = convert_temperature(value, from_factor, to_factor);
    } else {
        result = value * from_factor / to_factor;
    }

    if (!isfinite(result)) {
        fputs("변환 결과가 너무 큽니다. 입력값을 확인하세요.\n", stderr);
        return 1;
    }

    printf("변환 결과: %.4Lf %s\n", result, to_unit);
    return 0;
}
