#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

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

static int read_positive_integer(const char *prompt, long long *value)
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

    if (errno == ERANGE || end == input || *end != '\0' || parsed <= 0) {
        return -1;
    }

    *value = parsed;
    return 1;
}

static int get_value(const char *prompt, const char *error_message,
                     long double *value)
{
    int status = read_positive_value(prompt, value);

    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n" : error_message, stderr);
    }

    return status;
}

int main(void)
{
    long double distance;
    long double fuel_efficiency;
    long double fuel_price;
    long double fuel_needed;
    long double total_cost;
    long double cost_per_person;
    long long people;
    int status;

    puts("이동 연료비 계산기");
    puts("총 이동 거리를 기준으로 필요한 연료와 인원별 비용을 계산합니다.\n");

    status = get_value("총 이동 거리(km): ",
                       "이동 거리는 0보다 큰 숫자로 입력하세요.\n", &distance);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    status = get_value("차량 평균 연비(km/L): ",
                       "평균 연비는 0보다 큰 숫자로 입력하세요.\n",
                       &fuel_efficiency);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    status = get_value("연료 가격(원/L): ",
                       "연료 가격은 0보다 큰 숫자로 입력하세요.\n", &fuel_price);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    status = read_positive_integer("비용을 나눌 인원: ", &people);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "인원은 0보다 큰 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    fuel_needed = distance / fuel_efficiency;
    total_cost = fuel_needed * fuel_price;
    cost_per_person = total_cost / people;

    if (!isfinite(fuel_needed) || !isfinite(total_cost) ||
        !isfinite(cost_per_person)) {
        fputs("계산 결과가 너무 큽니다. 입력값을 확인하세요.\n", stderr);
        return 1;
    }

    puts("\n[예상 결과]");
    printf("필요 연료: %.2LfL\n", fuel_needed);
    printf("총 예상 연료비: %.0Lf원\n", total_cost);
    printf("1인당 예상 비용: %.0Lf원\n", cost_per_person);
    puts("실제 연비와 교통 상황에 따라 비용이 달라질 수 있습니다.");

    return 0;
}
