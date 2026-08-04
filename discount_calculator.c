#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

static int read_value(const char *prompt, long double minimum,
                      long double maximum, long double *value)
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
        !isfinite(parsed) || parsed < minimum || parsed > maximum) {
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

int main(void)
{
    long double original_price;
    long double discount_rate;
    long double original_total;
    long double discount_total;
    long double final_unit_price;
    long double final_total;
    long long quantity;
    int status;

    puts("할인 계산기");
    puts("상품 가격과 할인율, 수량을 기준으로 최종 결제액을 계산합니다.\n");

    status = read_value("상품 1개 가격(원): ", 0.01L, LDBL_MAX,
                        &original_price);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "가격은 0보다 큰 숫자로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_value("할인율(0~100%): ", 0.0L, 100.0L, &discount_rate);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "할인율은 0부터 100 사이의 숫자로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    status = read_positive_integer("구매 수량: ", &quantity);
    if (status != 1) {
        fputs(status == 0 ? "입력이 종료되었습니다.\n"
                          : "수량은 0보다 큰 정수로 입력하세요.\n",
              stderr);
        return status == 0 ? 0 : 1;
    }

    original_total = original_price * quantity;
    discount_total = original_total * discount_rate / 100.0L;
    final_unit_price = original_price * (100.0L - discount_rate) / 100.0L;
    final_total = original_total - discount_total;

    if (!isfinite(original_total) || !isfinite(discount_total) ||
        !isfinite(final_unit_price) || !isfinite(final_total)) {
        fputs("계산 결과가 너무 큽니다. 입력값을 확인하세요.\n", stderr);
        return 1;
    }

    puts("\n[계산 결과]");
    printf("할인 전 총액: %.0Lf원\n", original_total);
    printf("총 할인 금액: %.0Lf원\n", discount_total);
    printf("할인 후 개당 가격: %.0Lf원\n", final_unit_price);
    printf("최종 결제 금액: %.0Lf원\n", final_total);
    puts("표시 금액은 1원 단위로 반올림한 예상값입니다.");

    return 0;
}
