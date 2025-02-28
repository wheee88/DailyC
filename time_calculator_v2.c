#include <windows.h>
#include <stdio.h>

int main() {
    // 콘솔 출력 코드 페이지를 UTF-8로 설정
    SetConsoleOutputCP(CP_UTF8);

    while (1) {
        int choice;

        printf("\n------------------------------\n");
        printf("원하는 기능을 선택하세요:\n");
        printf("1. 시간 차이 계산 (시작 시간과 종료 시간)\n");
        printf("2. 시간 합산 (두 시간 더하기)\n");
        printf("3. 시간 빼기 (기준 시간에서 일정 시간 빼기)\n");
        printf("0. 종료\n");
        printf("------------------------------\n");
        printf("번호 입력: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // 시간 차이 계산
            int startHour, startMinute, endHour, endMinute;
            printf("시작 시간 입력 (시 분): ");
            scanf("%d %d", &startHour, &startMinute);
            printf("종료 시간 입력 (시 분): ");
            scanf("%d %d", &endHour, &endMinute);

            int startTotal = startHour * 60 + startMinute;
            int endTotal   = endHour   * 60 + endMinute;

            // 자정을 넘어간 경우 처리
            if (endTotal < startTotal) {
                endTotal += 24 * 60;
            }

            int diff       = endTotal - startTotal;
            int diffHour   = diff / 60;
            int diffMinute = diff % 60;

            printf("두 시간의 차이는 %d시간 %d분입니다.\n", diffHour, diffMinute);

        } else if (choice == 2) {
            // 시간 합산
            int hour1, minute1, hour2, minute2;
            printf("첫 번째 시간 입력 (시 분): ");
            scanf("%d %d", &hour1, &minute1);
            printf("두 번째 시간 입력 (시 분): ");
            scanf("%d %d", &hour2, &minute2);

            int totalMinutes = (hour1 * 60 + minute1) + (hour2 * 60 + minute2);
            int resultHour   = totalMinutes / 60;
            int resultMinute = totalMinutes % 60;

            // 24시간 초과 시 24시간 체계로 환산
            resultHour = resultHour % 24;

            printf("합산 결과: %d시 %d분\n", resultHour, resultMinute);

        } else if (choice == 3) {
            // 시간 빼기 기능
            int baseHour, baseMinute, subHour, subMinute;
            printf("기준 시간 입력 (시 분): ");
            scanf("%d %d", &baseHour, &baseMinute);
            printf("빼고 싶은 시간 입력 (시 분): ");
            scanf("%d %d", &subHour, &subMinute);

            int baseTotal = baseHour * 60 + baseMinute;
            int subTotal  = subHour * 60 + subMinute;
            int resultTotal = baseTotal - subTotal;

            // 결과가 음수면 24시간을 더해 24시간 체계로 환산
            if(resultTotal < 0) {
                resultTotal += 24 * 60;
            }

            int resultHour = resultTotal / 60;
            int resultMinute = resultTotal % 60;
            printf("결과: %d시 %d분\n", resultHour, resultMinute);

        } else if (choice == 0) {
            // 프로그램 종료
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            // 잘못된 입력
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }
    return 0;
}
