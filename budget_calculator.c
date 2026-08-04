#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256
#define MAX_EXPENSES 20
#define NAME_SIZE 80

typedef struct {
    char name[NAME_SIZE];
    long double amount;
} Expense;

static int read_value(const char *prompt, long double minimum,
                      long double *value)
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
        !isfinite(parsed) || parsed < minimum) {
        return -1;
    }

    *value = parsed;
    return 1;
}

static int read_expense_count(const char *prompt, int *value)
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

    if (errno == ERANGE || end == input || *end != '\0' || parsed < 0 ||
        parsed > MAX_EXPENSES) {
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
    Expense expenses[MAX_EXPENSES];
    long double income;
    long double total_expenses = 0.0L;
    long double balance;
    long double rate;
    int expense_count;
    int status;
    int i;

    puts("간단 가계부 계산기");
    puts("수입과 지출 항목을 입력해 이번 달 잔액을 계산합니다.\n");

    status = read_value("총 수입(원): ", 0.01L, &income);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "수입은 0보다 큰 숫자로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_expense_count("지출 항목 수(0~20): ", &expense_count);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "지출 항목 수는 0부터 20 사이의 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    for (i = 0; i < expense_count; i++) {
        char prompt[80];

        printf("\n[지출 %d]\n", i + 1);
        snprintf(prompt, sizeof(prompt), "지출 %d 이름: ", i + 1);
        status = read_text(prompt, expenses[i].name, sizeof(expenses[i].name));
        if (status == 1) {
            status = read_value("금액(원): ", 0.0L, &expenses[i].amount);
        }

        if (status != 1) {
            fputs(status == 0 ? "입력이 종료되었습니다.\n"
                              : "지출 이름 또는 금액 입력이 올바르지 않습니다.\n",
                  stderr);
            return status == 0 ? 0 : 1;
        }

        total_expenses += expenses[i].amount;
        if (!isfinite(total_expenses)) {
            fputs("지출 합계가 너무 큽니다. 입력값을 확인하세요.\n", stderr);
            return 1;
        }
    }

    balance = income - total_expenses;
    puts("\n[계산 결과]");
    printf("총 수입: %.0Lf원\n", income);
    if (expense_count > 0) {
        puts("지출 내역:");
        for (i = 0; i < expense_count; i++) {
            printf("- %s: %.0Lf원\n", expenses[i].name, expenses[i].amount);
        }
    }
    printf("총 지출: %.0Lf원\n", total_expenses);

    if (balance >= 0.0L) {
        rate = balance / income * 100.0L;
        printf("잔액: %.0Lf원\n", balance);
        printf("저축률: %.2Lf%%\n", rate);
    } else {
        rate = -balance / income * 100.0L;
        printf("예산 초과액: %.0Lf원\n", -balance);
        printf("예산 초과율: %.2Lf%%\n", rate);
    }

    return 0;
}
