# 프로세스 관리 기초

## 프로세스 개념

프로세스는 실행 중인 프로그램의 인스턴스입니다. 리눅스에서 모든 실행 중인 프로그램은 프로세스로 관리됩니다.

## 프로세스 확인 명령어

### 1. 기본 프로세스 명령어
```bash
# 모든 프로세스 보기
ps aux

# 프로세스 트리 형태로 보기
ps auxf

# 특정 사용자의 프로세스만 보기
ps -u username

# 특정 프로세스 찾기
ps aux | grep process_name

# 프로세스 ID로 확인
ps -p PID
```

### 2. 실시간 프로세스 모니터링
```bash
# 실시간 프로세스 모니터링
top

# 향상된 top (설치 필요)
htop

# 프로세스 모니터링 (간단한 형태)
htop -d 1
```

### 3. 프로세스 정보 상세 확인
```bash
# 특정 프로세스의 상세 정보
ps -p PID -o pid,ppid,cmd,%mem,%cpu,etime

# 프로세스의 환경 변수
cat /proc/PID/environ

# 프로세스의 파일 디스크립터
ls -la /proc/PID/fd

# 프로세스의 메모리 맵
cat /proc/PID/maps
```

## 실습 예제

### 실습 1: 프로세스 정보 수집
```bash
# 프로세스 정보 수집 스크립트
cat > process_info.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 정보 수집 ==="
echo

echo "1. 전체 프로세스 수:"
ps aux | wc -l
echo "총 $(ps aux | wc -l)개의 프로세스 실행 중"

echo -e "\n2. CPU 사용률 상위 5개 프로세스:"
ps aux --sort=-%cpu | head -6

echo -e "\n3. 메모리 사용률 상위 5개 프로세스:"
ps aux --sort=-%mem | head -6

echo -e "\n4. 실행 시간이 긴 프로세스 (상위 5개):"
ps aux --sort=-etime | head -6

echo -e "\n5. 현재 사용자의 프로세스:"
ps -u $(whoami) | wc -l
echo "현재 사용자: $(ps -u $(whoami) | wc -l)개 프로세스"

echo -e "\n6. 시스템 프로세스 (PID < 1000):"
ps aux | awk '$2 < 1000 {print $2, $11}' | head -10

echo -e "\n7. 프로세스 상태별 분류:"
ps aux | awk '{print $8}' | sort | uniq -c | sort -nr
EOF

chmod +x process_info.sh
./process_info.sh
```

### 실습 2: 프로세스 생성과 종료
```bash
# 프로세스 생성과 종료 실습
cat > process_lifecycle.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 생성과 종료 실습 ==="
echo

echo "1. 백그라운드 프로세스 생성:"
sleep 60 &
SLEEP_PID=$!
echo "sleep 프로세스 생성: PID $SLEEP_PID"

echo -e "\n2. 프로세스 확인:"
ps -p $SLEEP_PID

echo -e "\n3. 프로세스 상태 확인:"
ps -p $SLEEP_PID -o pid,ppid,state,cmd

echo -e "\n4. 프로세스 종료 (SIGTERM):"
kill $SLEEP_PID
echo "SIGTERM 신호 전송"

echo -e "\n5. 프로세스 상태 재확인:"
sleep 1
ps -p $SLEEP_PID
if [ $? -eq 0 ]; then
    echo "프로세스가 아직 실행 중입니다"
else
    echo "프로세스가 종료되었습니다"
fi

echo -e "\n6. 강제 종료 실습:"
sleep 60 &
SLEEP_PID2=$!
echo "새로운 sleep 프로세스 생성: PID $SLEEP_PID2"

sleep 2
echo "강제 종료 (SIGKILL):"
kill -9 $SLEEP_PID2
echo "SIGKILL 신호 전송"

sleep 1
ps -p $SLEEP_PID2
if [ $? -eq 0 ]; then
    echo "프로세스가 아직 실행 중입니다"
else
    echo "프로세스가 강제 종료되었습니다"
fi
EOF

chmod +x process_lifecycle.sh
./process_lifecycle.sh
```

### 실습 3: 프로세스 모니터링
```bash
# 프로세스 모니터링 스크립트
cat > process_monitor.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 모니터링 ==="
echo

# 모니터링할 프로세스 이름
PROCESS_NAME="sleep"

echo "1. $PROCESS_NAME 프로세스 모니터링 시작"
echo "Ctrl+C로 종료"

# 프로세스 모니터링 루프
while true; do
    clear
    echo "=== 프로세스 모니터링 $(date) ==="
    echo
    
    # 프로세스 개수
    COUNT=$(ps aux | grep -v grep | grep $PROCESS_NAME | wc -l)
    echo "$PROCESS_NAME 프로세스 수: $COUNT"
    
    if [ $COUNT -gt 0 ]; then
        echo -e "\n$PROCESS_NAME 프로세스 상세 정보:"
        ps aux | grep -v grep | grep $PROCESS_NAME
    else
        echo -e "\n$PROCESS_NAME 프로세스가 실행 중이 아닙니다"
    fi
    
    echo -e "\n전체 프로세스 수: $(ps aux | wc -l)"
    echo -e "CPU 사용률 상위 3개:"
    ps aux --sort=-%cpu | head -4
    
    sleep 2
done
EOF

chmod +x process_monitor.sh
# 실행하려면: ./process_monitor.sh
```

## 프로세스 제어

### 1. 프로세스 종료
```bash
# 프로세스 종료 명령어들
kill PID              # 기본 종료 (SIGTERM)
kill -9 PID           # 강제 종료 (SIGKILL)
kill -15 PID          # 정상 종료 (SIGTERM)
kill -2 PID           # 인터럽트 (SIGINT)

# 프로세스 이름으로 종료
killall process_name
pkill process_name

# 패턴으로 프로세스 종료
pkill -f "pattern"
```

### 2. 프로세스 일시정지/재개
```bash
# 프로세스 일시정지
kill -19 PID          # SIGSTOP
kill -STOP PID

# 프로세스 재개
kill -18 PID          # SIGCONT
kill -CONT PID

# 백그라운드 작업 제어
jobs                  # 백그라운드 작업 목록
fg %1                 # 작업을 포그라운드로
bg %1                 # 작업을 백그라운드로
```

### 3. 프로세스 우선순위 변경
```bash
# nice 값 확인
ps -o pid,ni,cmd

# nice 값 변경 (새 프로세스)
nice -n 10 command

# 실행 중인 프로세스 우선순위 변경
renice 10 PID

# 사용자별 프로세스 우선순위 변경
renice 5 -u username
```

## 실습 예제

### 실습 4: 프로세스 제어 실습
```bash
# 프로세스 제어 실습
cat > process_control.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 제어 실습 ==="
echo

echo "1. 백그라운드 작업 생성:"
sleep 300 &
SLEEP_PID=$!
echo "sleep 300 프로세스 생성: PID $SLEEP_PID"

echo -e "\n2. 작업 목록 확인:"
jobs

echo -e "\n3. 프로세스 일시정지:"
kill -STOP $SLEEP_PID
echo "프로세스 일시정지 완료"

echo -e "\n4. 프로세스 상태 확인:"
ps -p $SLEEP_PID -o pid,state,cmd

echo -e "\n5. 프로세스 재개:"
kill -CONT $SLEEP_PID
echo "프로세스 재개 완료"

echo -e "\n6. 프로세스 우선순위 변경:"
renice 10 $SLEEP_PID
echo "nice 값 10으로 변경"

echo -e "\n7. 변경된 우선순위 확인:"
ps -p $SLEEP_PID -o pid,ni,cmd

echo -e "\n8. 프로세스 종료:"
kill $SLEEP_PID
echo "프로세스 종료 완료"
EOF

chmod +x process_control.sh
./process_control.sh
```

### 실습 5: 프로세스 검색과 필터링
```bash
# 프로세스 검색과 필터링 실습
cat > process_search.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 검색과 필터링 ==="
echo

echo "1. 특정 사용자의 프로세스:"
ps -u $(whoami) | head -5

echo -e "\n2. 특정 명령어를 포함한 프로세스:"
ps aux | grep -v grep | grep "bash" | head -5

echo -e "\n3. CPU 사용률이 높은 프로세스 (상위 5개):"
ps aux --sort=-%cpu | head -6

echo -e "\n4. 메모리 사용률이 높은 프로세스 (상위 5개):"
ps aux --sort=-%mem | head -6

echo -e "\n5. 실행 시간이 긴 프로세스 (상위 5개):"
ps aux --sort=-etime | head -6

echo -e "\n6. 특정 상태의 프로세스:"
echo "실행 중인 프로세스 (R):"
ps aux | awk '$8 ~ /R/ {print $2, $8, $11}' | head -5

echo -e "\n대기 중인 프로세스 (S):"
ps aux | awk '$8 ~ /S/ {print $2, $8, $11}' | head -5

echo -e "\n7. 프로세스 트리 구조:"
ps auxf | head -20

echo -e "\n8. 프로세스별 파일 디스크립터 수:"
lsof | awk '{print $2}' | sort | uniq -c | sort -nr | head -10
EOF

chmod +x process_search.sh
./process_search.sh
```

## 프로세스 상태

### 1. 프로세스 상태 코드
```bash
# 프로세스 상태 설명
cat > process_states.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 상태 코드 설명 ==="
echo

echo "R (Running): 실행 중 또는 실행 대기 중"
echo "S (Sleeping): 인터럽트 가능한 대기 상태"
echo "D (Disk sleep): 인터럽트 불가능한 대기 상태"
echo "Z (Zombie): 좀비 프로세스 (종료되었지만 정리되지 않음)"
echo "T (Stopped): 일시정지 상태"
echo "t (Tracing stop): 디버깅 중 일시정지"
echo "X (Dead): 완전히 종료된 프로세스"

echo -e "\n현재 시스템의 프로세스 상태 분포:"
ps aux | awk '{print $8}' | sort | uniq -c | sort -nr
EOF

chmod +x process_states.sh
./process_states.sh
```

### 2. 좀비 프로세스 처리
```bash
# 좀비 프로세스 처리 실습
cat > zombie_process.sh << 'EOF'
#!/bin/bash

echo "=== 좀비 프로세스 처리 ==="
echo

echo "1. 좀비 프로세스 확인:"
ps aux | awk '$8 ~ /Z/ {print $2, $8, $11}'

echo -e "\n2. 좀비 프로세스 개수:"
ZOMBIE_COUNT=$(ps aux | awk '$8 ~ /Z/ {count++} END {print count+0}')
echo "좀비 프로세스 수: $ZOMBIE_COUNT"

if [ $ZOMBIE_COUNT -gt 0 ]; then
    echo -e "\n3. 좀비 프로세스 상세 정보:"
    ps aux | awk '$8 ~ /Z/ {print $2, $3, $4, $8, $11}'
    
    echo -e "\n4. 좀비 프로세스의 부모 프로세스:"
    ps aux | awk '$8 ~ /Z/ {print $3}' | while read ppid; do
        ps -p $ppid -o pid,ppid,cmd 2>/dev/null
    done
else
    echo "좀비 프로세스가 없습니다"
fi

echo -e "\n5. 좀비 프로세스 정리 방법:"
echo "- 부모 프로세스에 SIGCHLD 신호 전송"
echo "- 부모 프로세스 재시작"
echo "- 시스템 재부팅 (최후의 수단)"
EOF

chmod +x zombie_process.sh
./zombie_process.sh
```

## 프로세스 리소스 모니터링

### 1. 프로세스 리소스 사용량
```bash
# 프로세스 리소스 모니터링
cat > process_resources.sh << 'EOF'
#!/bin/bash

echo "=== 프로세스 리소스 모니터링 ==="
echo

echo "1. CPU 사용률 상위 프로세스:"
ps aux --sort=-%cpu | head -10

echo -e "\n2. 메모리 사용률 상위 프로세스:"
ps aux --sort=-%mem | head -10

echo -e "\n3. 프로세스별 파일 디스크립터 사용량:"
lsof | awk '{print $2}' | sort | uniq -c | sort -nr | head -10

echo -e "\n4. 프로세스별 네트워크 연결 수:"
ss -tuln | awk '{print $6}' | sort | uniq -c | sort -nr | head -10

echo -e "\n5. 프로세스별 디스크 I/O:"
echo "iostat -x 1 1"  # iostat이 설치되어 있다면

echo -e "\n6. 프로세스별 메모리 맵:"
echo "특정 프로세스의 메모리 맵을 보려면:"
echo "cat /proc/PID/maps"
EOF

chmod +x process_resources.sh
./process_resources.sh
```

## 유용한 명령어들

### 1. 프로세스 관련 명령어
```bash
# 프로세스 정보
ps, top, htop, pstree

# 프로세스 제어
kill, killall, pkill, renice

# 프로세스 검색
pgrep, pidof

# 프로세스 모니터링
lsof, fuser, strace
```

### 2. 프로세스 디버깅
```bash
# 프로세스 추적
strace -p PID

# 프로세스의 시스템 콜 모니터링
strace -e trace=file command

# 프로세스의 네트워크 활동 모니터링
strace -e trace=network command
```

## 주의사항

1. **프로세스 종료 주의**
   - `kill -9`는 최후의 수단으로만 사용
   - 중요한 프로세스 종료 전에 의존성 확인

2. **좀비 프로세스**
   - 좀비 프로세스는 부모 프로세스가 정리해야 함
   - 좀비 프로세스가 많아지면 시스템 성능 저하

3. **프로세스 우선순위**
   - nice 값이 낮을수록 높은 우선순위
   - 일반 사용자는 nice 값을 높일 수만 있음

4. **리소스 모니터링**
   - CPU 사용률이 80% 이상 지속되면 주의
   - 메모리 사용률이 90% 이상이면 스왑 사용 확인

5. **보안 고려사항**
   - 다른 사용자의 프로세스 정보 접근 제한
   - 시스템 프로세스 종료 주의