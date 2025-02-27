#include <stdio.h>

int main() {
    int choice;
    
    printf("원하는 기능을 선택하세요:\n");
    printf("1. 시간 차이 계산 (시작 시간과 종료 시간)\n");
    printf("2. 시간 합산 (두 시간 더하기)\n");
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
        int endTotal = endHour * 60 + endMinute;
        
        // 자정을 넘어간 경우 처리
        if (endTotal < startTotal) {
            endTotal += 24 * 60;
        }
        
        int diff = endTotal - startTotal;
        int diffHour = diff / 60;
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
        int resultHour = totalMinutes / 60;
        int resultMinute = totalMinutes % 60;
        
        printf("합산 결과: %d시간 %d분\n", resultHour, resultMinute);
    } else {
        printf("잘못된 선택입니다.\n");
    }
    
    return 0;
}
