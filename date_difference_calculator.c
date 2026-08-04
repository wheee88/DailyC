#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 128

typedef struct {
    int year;
    int month;
    int day;
} Date;

static int is_leap_year(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

static int days_in_month(int year, int month)
{
    static const int days[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days[month - 1];
}

static int digit_value(const char *text, int start, int count)
{
    int value = 0;
    int i;

    for (i = 0; i < count; i++) {
        value = value * 10 + (text[start + i] - '0');
    }

    return value;
}

static int read_date(const char *prompt, Date *date)
{
    char input[INPUT_SIZE];
    const char *rest;
    int i;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    if (strlen(input) < 10) {
        return -1;
    }

    for (i = 0; i < 10; i++) {
        if ((i == 4 || i == 7) ? input[i] != '-'
                               : !isdigit((unsigned char)input[i])) {
            return -1;
        }
    }

    rest = input + 10;
    while (isspace((unsigned char)*rest)) {
        rest++;
    }
    if (*rest != '\0') {
        return -1;
    }

    date->year = digit_value(input, 0, 4);
    date->month = digit_value(input, 5, 2);
    date->day = digit_value(input, 8, 2);

    if (date->year < 1 || date->month < 1 || date->month > 12 ||
        date->day < 1 || date->day > days_in_month(date->year, date->month)) {
        return -1;
    }

    return 1;
}

static long long date_to_serial(Date date)
{
    static const int days_before_month[] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    long long previous_year = date.year - 1;
    long long serial;

    serial = previous_year * 365 + previous_year / 4 - previous_year / 100 +
             previous_year / 400;
    serial += days_before_month[date.month - 1];
    if (date.month > 2 && is_leap_year(date.year)) {
        serial++;
    }
    serial += date.day - 1;

    return serial;
}

int main(void)
{
    Date start_date;
    Date end_date;
    long long difference;
    long long absolute_difference;
    int status;

    puts("날짜 간격 계산기");
    puts("두 날짜는 YYYY-MM-DD 형식으로 입력하세요.\n");

    status = read_date("시작 날짜: ", &start_date);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "시작 날짜가 올바르지 않습니다.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_date("종료 날짜: ", &end_date);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "종료 날짜가 올바르지 않습니다.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    difference = date_to_serial(end_date) - date_to_serial(start_date);
    absolute_difference = difference < 0 ? -difference : difference;

    puts("\n[계산 결과]");
    printf("두 날짜의 차이: %lld일\n", absolute_difference);
    printf("시작일과 종료일을 모두 포함한 기간: %lld일\n",
           absolute_difference + 1);

    if (difference > 0) {
        printf("종료 날짜가 시작 날짜보다 %lld일 뒤입니다.\n", difference);
    } else if (difference < 0) {
        printf("종료 날짜가 시작 날짜보다 %lld일 앞입니다.\n",
               absolute_difference);
    } else {
        puts("시작 날짜와 종료 날짜가 같습니다.");
    }

    return 0;
}
