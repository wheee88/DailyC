#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

static int read_positive_number(const char *prompt, long long *value)
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

static void print_amount(long long amount)
{
    char digits[32];
    size_t length;
    size_t i;

    snprintf(digits, sizeof(digits), "%lld", amount);
    length = 0;
    while (digits[length] != '\0') {
        length++;
    }

    for (i = 0; i < length; i++) {
        putchar(digits[i]);
        if ((length - i - 1) % 3 == 0 && i + 1 < length) {
            putchar(',');
        }
    }
}

int main(void)
{
    long long total_amount;
    long long people;
    long long rounding_unit;
    long long transfer_amount;
    long long organizer_amount;
    int status;

    puts("더치페이 계산기");
    puts("총무를 제외한 사람은 반올림 단위에 맞춰 송금합니다.\n");

    status = read_positive_number("총 결제 금액(원): ", &total_amount);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "금액은 0보다 큰 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_positive_number("정산 인원(총무 포함): ", &people);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "인원은 0보다 큰 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_positive_number("송금 단위(예: 1, 10, 100, 1000): ",
                                  &rounding_unit);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "송금 단위는 0보다 큰 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    transfer_amount = (total_amount / people / rounding_unit) * rounding_unit;
    organizer_amount = total_amount - transfer_amount * (people - 1);

    puts("\n[정산 결과]");
    printf("총무 외 %lld명 송금액: ", people - 1);
    print_amount(transfer_amount);
    puts("원");
    printf("총무 최종 부담액: ");
    print_amount(organizer_amount);
    puts("원");

    if (people == 1) {
        puts("혼자 결제한 금액입니다.");
    } else if (organizer_amount == transfer_amount) {
        puts("모든 사람이 같은 금액을 부담합니다.");
    } else {
        printf("총무가 다른 사람보다 ");
        print_amount(organizer_amount - transfer_amount);
        puts("원 더 부담합니다.");
    }

    return 0;
}
