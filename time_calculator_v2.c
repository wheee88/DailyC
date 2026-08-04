#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128
#define MINUTES_PER_DAY (24LL * 60LL)

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

static int read_pair(const char *prompt, long long *first, long long *second)
{
    char input[INPUT_SIZE];
    char *first_end;
    char *second_end;
    long long parsed_first;
    long long parsed_second;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed_first = strtoll(input, &first_end, 10);
    if (errno == ERANGE || first_end == input) {
        return -1;
    }

    errno = 0;
    parsed_second = strtoll(first_end, &second_end, 10);
    if (errno == ERANGE || second_end == first_end) {
        return -1;
    }

    while (isspace((unsigned char)*second_end)) {
        second_end++;
    }
    if (*second_end != '\0') {
        return -1;
    }

    *first = parsed_first;
    *second = parsed_second;
    return 1;
}

static int read_clock_time(const char *prompt, long long *total_minutes)
{
    long long hour;
    long long minute;
    int status = read_pair(prompt, &hour, &minute);

    if (status != 1) {
        return status;
    }
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return -1;
    }

    *total_minutes = hour * 60 + minute;
    return 1;
}

static int read_duration(const char *prompt, long long *minutes_in_day)
{
    long long hour;
    long long minute;
    int status = read_pair(prompt, &hour, &minute);

    if (status != 1) {
        return status;
    }
    if (hour < 0 || minute < 0 || minute > 59) {
        return -1;
    }

    *minutes_in_day = (hour % 24) * 60 + minute;
    return 1;
}

static long long normalize_time(long long total_minutes)
{
    total_minutes %= MINUTES_PER_DAY;
    if (total_minutes < 0) {
        total_minutes += MINUTES_PER_DAY;
    }
    return total_minutes;
}

static void print_clock_result(const char *label, long long total_minutes)
{
    total_minutes = normalize_time(total_minutes);
    printf("%s%02lld:%02lld\n", label, total_minutes / 60,
           total_minutes % 60);
}

int main(void)
{
    long long choice;

    while (1) {
        long long first_time;
        long long second_time;
        long long duration;
        long long difference;
        int status;

        puts("\n------------------------------");
        puts("원하는 기능을 선택하세요:");
        puts("1. 시간 차이 계산");
        puts("2. 기준 시간에 기간 더하기");
        puts("3. 기준 시간에서 기간 빼기");
        puts("0. 종료");
        puts("------------------------------");

        status = read_integer("번호 입력: ", &choice);
        if (status == 0) {
            puts("입력이 종료되어 프로그램을 종료합니다.");
            break;
        }
        if (status < 0) {
            fputs("메뉴 번호는 정수로 입력하세요.\n", stderr);
            continue;
        }

        if (choice == 0) {
            puts("프로그램을 종료합니다.");
            break;
        }

        if (choice == 1) {
            status = read_clock_time("시작 시간(시 분): ", &first_time);
            if (status == 1) {
                status = read_clock_time("종료 시간(시 분): ", &second_time);
            }
            if (status == 0) {
                puts("입력이 종료되어 프로그램을 종료합니다.");
                break;
            }
            if (status < 0) {
                fputs("시간은 0~23시, 0~59분 범위로 입력하세요.\n", stderr);
                continue;
            }

            difference = normalize_time(second_time - first_time);
            printf("두 시간의 차이: %lld시간 %lld분\n", difference / 60,
                   difference % 60);
        } else if (choice == 2 || choice == 3) {
            status = read_clock_time("기준 시간(시 분): ", &first_time);
            if (status == 1) {
                status = read_duration("기간(시 분): ", &duration);
            }
            if (status == 0) {
                puts("입력이 종료되어 프로그램을 종료합니다.");
                break;
            }
            if (status < 0) {
                fputs("기준 시간 또는 기간의 범위를 확인하세요.\n", stderr);
                continue;
            }

            if (choice == 2) {
                print_clock_result("더한 결과: ", first_time + duration);
            } else {
                print_clock_result("뺀 결과: ", first_time - duration);
            }
        } else {
            fputs("0부터 3 사이의 메뉴 번호를 입력하세요.\n", stderr);
        }
    }

    return 0;
}
