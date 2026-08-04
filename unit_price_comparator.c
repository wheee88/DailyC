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

static int get_value(const char *prompt, const char *error_message,
                     long double *value)
{
    int status = read_positive_value(prompt, value);

    if (status == 1) {
        return 1;
    }

    fputs(status == 0 ? "입력이 종료되었습니다.\n" : error_message, stderr);
    return status;
}

int main(void)
{
    long double price_a;
    long double quantity_a;
    long double price_b;
    long double quantity_b;
    long double unit_price_a;
    long double unit_price_b;
    long double difference;
    long double tolerance;
    long double saving_rate;
    int status;

    puts("단위가격 비교기");
    puts("두 상품의 용량 단위는 같게 입력하세요. (예: 둘 다 g 또는 둘 다 ml)\n");

    status = get_value("상품 A 가격(원): ",
                       "가격은 0보다 큰 숫자로 입력하세요.\n", &price_a);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    status = get_value("상품 A 용량: ",
                       "용량은 0보다 큰 숫자로 입력하세요.\n", &quantity_a);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    status = get_value("상품 B 가격(원): ",
                       "가격은 0보다 큰 숫자로 입력하세요.\n", &price_b);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    status = get_value("상품 B 용량: ",
                       "용량은 0보다 큰 숫자로 입력하세요.\n", &quantity_b);
    if (status != 1) {
        return status == 0 ? 0 : 1;
    }

    unit_price_a = price_a / quantity_a;
    unit_price_b = price_b / quantity_b;
    difference = unit_price_a - unit_price_b;
    if (difference < 0.0L) {
        difference = -difference;
    }
    tolerance = (unit_price_a + unit_price_b) * 1e-12L;

    puts("\n[비교 결과]");
    printf("상품 A 단위가격: %.2Lf원\n", unit_price_a);
    printf("상품 B 단위가격: %.2Lf원\n", unit_price_b);

    if (difference <= tolerance) {
        puts("두 상품의 단위가격이 같습니다.");
    } else if (unit_price_a < unit_price_b) {
        saving_rate = (unit_price_b - unit_price_a) / unit_price_b * 100.0L;
        printf("상품 A가 단위가격 기준 %.2Lf%% 저렴합니다.\n", saving_rate);
    } else {
        saving_rate = (unit_price_a - unit_price_b) / unit_price_a * 100.0L;
        printf("상품 B가 단위가격 기준 %.2Lf%% 저렴합니다.\n", saving_rate);
    }

    return 0;
}
