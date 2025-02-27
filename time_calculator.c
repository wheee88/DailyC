#include <stdio.h>

int main() {
    int startHour, startMinute, endHour, endMinute;
    
    // 시작 시간 입력 (시와 분)
    printf("시작 시간 (시 분): ");
    scanf("%d %d", &startHour, &startMinute);
    
    // 종료 시간 입력 (시와 분)
    printf("종료 시간 (시 분): ");
    scanf("%d %d", &endHour, &endMinute);
    
    // 입력한 시간을 분으로 변환
    int startTotal = startHour * 60 + startMinute;
    int endTotal = endHour * 60 + endMinute;
    
    // 종료 시간이 시작 시간보다 작으면 자정을 넘어간 것으로 처리
    if (endTotal < startTotal) {
        endTotal += 24 * 60; // 24시간을 분으로 환산하여 더함
    }
    
    // 시간 차이 계산
    int diff = endTotal - startTotal;
    int diffHour = diff / 60;
    int diffMinute = diff % 60;
    
    // 결과 출력
    printf("두 시간의 차이는 %d시간 %d분입니다.\n", diffHour, diffMinute);
    return 0;
}
