# 백그라운드 작업 관리

## 백그라운드 작업 개념

백그라운드 작업은 터미널과 독립적으로 실행되는 프로세스입니다. 사용자가 다른 작업을 할 수 있도록 하면서 백그라운드에서 작업을 계속 수행할 수 있습니다.

## 백그라운드 작업 기본 명령어

### 1. 백그라운드 작업 생성
```bash
# 명령어 뒤에 &를 붙여서 백그라운드 실행
command &

# 예시
sleep 60 &
find / -name "*.txt" > results.txt &

# 백그라운드 작업 생성과 동시에 PID 저장
sleep 60 &
BG_PID=$!
echo "백그라운드 작업 PID: $BG_PID"
```

### 2. 백그라운드 작업 관리
```bash
# 현재 작업 목록 보기
jobs

# 작업 번호로 포그라운드로 가져오기
fg %1

# 작업 번호로 백그라운드로 보내기
bg %1

# 작업 번호로 작업 종료
kill %1
```

### 3. nohup을 사용한 백그라운드 작업
```bash
# 터미널 종료 후에도 계속 실행
nohup command &

# 출력을 파일로 리다이렉션
nohup command > output.log 2>&1 &

# 예시
nohup find / -name "*.log" > find_results.log 2>&1 &
```

## 실습 예제

### 실습 1: 기본 백그라운드 작업
```bash
# 기본 백그라운드 작업 실습
cat > background_basics.sh << 'EOF'
#!/bin/bash

echo "=== 백그라운드 작업 기본 실습 ==="
echo

echo "1. 백그라운드 작업 생성:"
sleep 30 &
SLEEP_PID=$!
echo "sleep 30 백그라운드 작업 생성: PID $SLEEP_PID"

echo -e "\n2. 현재 작업 목록:"
jobs

echo -e "\n3. 작업 상세 정보:"
jobs -l

echo -e "\n4. 작업 상태 확인:"
ps -p $SLEEP_PID -o pid,state,cmd

echo -e "\n5. 작업을 포그라운드로 가져오기:"
fg %1

echo -e "\n6. 작업을 다시 백그라운드로 보내기:"
bg %1

echo -e "\n7. 작업 종료:"
kill %1
echo "작업 종료 완료"

echo -e "\n8. 작업 목록 재확인:"
jobs
EOF

chmod +x background_basics.sh
./background_basics.sh
```

### 실습 2: 여러 백그라운드 작업 관리
```bash
# 여러 백그라운드 작업 관리 실습
cat > multiple_jobs.sh << 'EOF'
#!/bin/bash

echo "=== 여러 백그라운드 작업 관리 ==="
echo

echo "1. 여러 백그라운드 작업 생성:"
sleep 60 &
JOB1_PID=$!
echo "작업 1 (sleep 60): PID $JOB1_PID"

sleep 120 &
JOB2_PID=$!
echo "작업 2 (sleep 120): PID $JOB2_PID"

sleep 180 &
JOB3_PID=$!
echo "작업 3 (sleep 180): PID $JOB3_PID"

echo -e "\n2. 현재 작업 목록:"
jobs -l

echo -e "\n3. 작업 상태별 분류:"
jobs -l | awk '{print $3}' | sort | uniq -c

echo -e "\n4. 특정 작업 상태 확인:"
echo "작업 1 상태:"
ps -p $JOB1_PID -o pid,state,cmd

echo -e "\n5. 작업 제어 실습:"
echo "작업 1을 포그라운드로 가져오기:"
fg %1

echo -e "\n작업 1을 다시 백그라운드로 보내기:"
bg %1

echo -e "\n6. 작업 종료:"
echo "작업 1 종료:"
kill %1

echo "작업 2 종료:"
kill %2

echo "작업 3 종료:"
kill %3

echo -e "\n7. 최종 작업 목록:"
jobs
EOF

chmod +x multiple_jobs.sh
./multiple_jobs.sh
```

### 실습 3: nohup을 사용한 장기 실행 작업
```bash
# nohup을 사용한 장기 실행 작업 실습
cat > nohup_jobs.sh << 'EOF'
#!/bin/bash

echo "=== nohup을 사용한 장기 실행 작업 ==="
echo

echo "1. nohup으로 백그라운드 작업 생성:"
nohup sleep 300 > sleep_output.log 2>&1 &
NOHUP_PID=$!
echo "nohup 작업 생성: PID $NOHUP_PID"

echo -e "\n2. 작업 상태 확인:"
jobs -l

echo -e "\n3. 출력 파일 확인:"
echo "출력 파일 내용:"
cat sleep_output.log

echo -e "\n4. 프로세스 상태 확인:"
ps -p $NOHUP_PID -o pid,state,cmd

echo -e "\n5. 터미널 종료 시뮬레이션:"
echo "터미널이 종료되어도 작업은 계속 실행됩니다"
echo "작업을 확인하려면: ps -p $NOHUP_PID"

echo -e "\n6. 작업 종료:"
kill $NOHUP_PID
echo "nohup 작업 종료 완료"

echo -e "\n7. 출력 파일 정리:"
rm -f sleep_output.log
echo "출력 파일 정리 완료"
EOF

chmod +x nohup_jobs.sh
./nohup_jobs.sh
```

## 작업 제어 신호

### 1. 작업 제어 신호들
```bash
# 작업 제어 신호 설명
cat > job_signals.sh << 'EOF'
#!/bin/bash

echo "=== 작업 제어 신호 설명 ==="
echo

echo "SIGTERM (15): 정상 종료 신호"
echo "SIGKILL (9): 강제 종료 신호"
echo "SIGSTOP (19): 작업 일시정지"
echo "SIGCONT (18): 작업 재개"
echo "SIGINT (2): 인터럽트 신호 (Ctrl+C)"
echo "SIGTSTP (20): 터미널에서 일시정지 (Ctrl+Z)"

echo -e "\n신호 전송 방법:"
echo "kill -SIGNAL PID"
echo "kill -SIGNAL %JOB_NUMBER"
echo "killall -SIGNAL PROCESS_NAME"
EOF

chmod +x job_signals.sh
./job_signals.sh
```

### 2. 작업 제어 신호 실습
```bash
# 작업 제어 신호 실습
cat > signal_practice.sh << 'EOF'
#!/bin/bash

echo "=== 작업 제어 신호 실습 ==="
echo

echo "1. 백그라운드 작업 생성:"
sleep 300 &
SLEEP_PID=$!
echo "sleep 300 백그라운드 작업 생성: PID $SLEEP_PID"

echo -e "\n2. 작업 상태 확인:"
jobs -l

echo -e "\n3. 작업 일시정지 (SIGSTOP):"
kill -STOP $SLEEP_PID
echo "SIGSTOP 신호 전송"

echo -e "\n4. 일시정지 후 작업 상태:"
jobs -l
ps -p $SLEEP_PID -o pid,state,cmd

echo -e "\n5. 작업 재개 (SIGCONT):"
kill -CONT $SLEEP_PID
echo "SIGCONT 신호 전송"

echo -e "\n6. 재개 후 작업 상태:"
jobs -l
ps -p $SLEEP_PID -o pid,state,cmd

echo -e "\n7. 작업 종료 (SIGTERM):"
kill -TERM $SLEEP_PID
echo "SIGTERM 신호 전송"

echo -e "\n8. 최종 작업 상태:"
sleep 1
jobs -l
ps -p $SLEEP_PID -o pid,state,cmd
EOF

chmod +x signal_practice.sh
./signal_practice.sh
```

## 스크립트에서 백그라운드 작업 관리

### 1. 스크립트 내 백그라운드 작업
```bash
# 스크립트 내 백그라운드 작업 관리
cat > script_background.sh << 'EOF'
#!/bin/bash

echo "=== 스크립트 내 백그라운드 작업 관리 ==="
echo

# 백그라운드 작업 함수
start_background_job() {
    local job_name=$1
    local duration=$2
    
    echo "백그라운드 작업 시작: $job_name"
    sleep $duration &
    local job_pid=$!
    echo "$job_name PID: $job_pid"
    return $job_pid
}

# 작업 모니터링 함수
monitor_jobs() {
    echo "현재 실행 중인 작업들:"
    jobs -l
    
    echo -e "\n프로세스 상태:"
    for job in $(jobs -p); do
        ps -p $job -o pid,state,cmd
    done
}

# 작업 종료 함수
cleanup_jobs() {
    echo "모든 백그라운드 작업 종료 중..."
    jobs -p | xargs kill 2>/dev/null
    echo "작업 정리 완료"
}

# 메인 실행
echo "1. 여러 백그라운드 작업 시작:"
start_background_job "작업1" 60
JOB1_PID=$!

start_background_job "작업2" 120
JOB2_PID=$!

start_background_job "작업3" 180
JOB3_PID=$!

echo -e "\n2. 작업 모니터링:"
monitor_jobs

echo -e "\n3. 5초 대기 후 재모니터링:"
sleep 5
monitor_jobs

echo -e "\n4. 작업 정리:"
cleanup_jobs

echo -e "\n5. 최종 상태:"
jobs -l
EOF

chmod +x script_background.sh
./script_background.sh
```

### 2. 백그라운드 작업 모니터링 스크립트
```bash
# 백그라운드 작업 모니터링 스크립트
cat > job_monitor.sh << 'EOF'
#!/bin/bash

echo "=== 백그라운드 작업 모니터링 ==="
echo

# 모니터링 함수
monitor_background_jobs() {
    while true; do
        clear
        echo "=== 백그라운드 작업 모니터링 $(date) ==="
        echo
        
        # 현재 작업 목록
        echo "현재 작업 목록:"
        jobs -l
        
        # 작업이 없으면 종료
        if [ $(jobs -l | wc -l) -eq 0 ]; then
            echo "실행 중인 백그라운드 작업이 없습니다"
            break
        fi
        
        # 각 작업의 상세 정보
        echo -e "\n작업 상세 정보:"
        for job in $(jobs -p); do
            echo "PID $job:"
            ps -p $job -o pid,ppid,state,%cpu,%mem,cmd
            echo
        done
        
        # 시스템 리소스 사용량
        echo "시스템 리소스 사용량:"
        echo "CPU 사용률: $(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)%"
        echo "메모리 사용률: $(free | grep Mem | awk '{printf "%.1f%%", $3/$2 * 100.0}')"
        
        sleep 3
    done
}

# 모니터링 시작
monitor_background_jobs
EOF

chmod +x job_monitor.sh
# 실행하려면: ./job_monitor.sh
```

## 고급 백그라운드 작업 관리

### 1. 작업 큐 시스템
```bash
# 작업 큐 시스템 구현
cat > job_queue.sh << 'EOF'
#!/bin/bash

echo "=== 작업 큐 시스템 ==="
echo

# 작업 큐 배열
declare -a JOB_QUEUE=()
declare -a RUNNING_JOBS=()
MAX_CONCURRENT_JOBS=3

# 작업 추가 함수
add_job() {
    local job_name=$1
    local job_command=$2
    local job_duration=$3
    
    JOB_QUEUE+=("$job_name:$job_command:$job_duration")
    echo "작업 추가: $job_name"
}

# 작업 실행 함수
execute_job() {
    local job_info=$1
    IFS=':' read -r job_name job_command job_duration <<< "$job_info"
    
    echo "작업 실행 시작: $job_name"
    eval "$job_command" &
    local job_pid=$!
    RUNNING_JOBS+=("$job_name:$job_pid")
    echo "작업 $job_name 시작: PID $job_pid"
}

# 작업 상태 확인 함수
check_jobs() {
    local new_running_jobs=()
    
    for job_info in "${RUNNING_JOBS[@]}"; do
        IFS=':' read -r job_name job_pid <<< "$job_info"
        
        if ps -p $job_pid > /dev/null 2>&1; then
            new_running_jobs+=("$job_info")
        else
            echo "작업 완료: $job_name"
        fi
    done
    
    RUNNING_JOBS=("${new_running_jobs[@]}")
}

# 작업 큐 처리 함수
process_queue() {
    while [ ${#JOB_QUEUE[@]} -gt 0 ] || [ ${#RUNNING_JOBS[@]} -gt 0 ]; do
        # 완료된 작업 확인
        check_jobs
        
        # 새 작업 시작 (동시 실행 작업 수 제한)
        while [ ${#RUNNING_JOBS[@]} -lt $MAX_CONCURRENT_JOBS ] && [ ${#JOB_QUEUE[@]} -gt 0 ]; do
            local next_job="${JOB_QUEUE[0]}"
            JOB_QUEUE=("${JOB_QUEUE[@]:1}")
            execute_job "$next_job"
        done
        
        # 상태 출력
        echo "대기 중인 작업: ${#JOB_QUEUE[@]}"
        echo "실행 중인 작업: ${#RUNNING_JOBS[@]}"
        
        sleep 2
    done
    
    echo "모든 작업 완료"
}

# 메인 실행
echo "작업 큐 시스템 시작"

# 작업 추가
add_job "작업1" "sleep 10" 10
add_job "작업2" "sleep 15" 15
add_job "작업3" "sleep 20" 20
add_job "작업4" "sleep 25" 25
add_job "작업5" "sleep 30" 30

# 작업 큐 처리
process_queue
EOF

chmod +x job_queue.sh
./job_queue.sh
```

## 유용한 명령어들

### 1. 백그라운드 작업 관련 명령어
```bash
# 작업 관리
jobs, fg, bg, kill

# 프로세스 관리
ps, top, htop

# 신호 전송
kill, killall, pkill

# 장기 실행
nohup, screen, tmux
```

### 2. 작업 모니터링
```bash
# 작업 상태 확인
jobs -l

# 프로세스 상태 확인
ps aux | grep process_name

# 실시간 모니터링
top, htop, iotop
```

## 주의사항

1. **터미널 종료 시 작업 유지**
   - `nohup` 사용으로 터미널 종료 후에도 작업 계속
   - `screen`이나 `tmux` 사용 권장

2. **작업 제어 신호**
   - `SIGKILL`은 최후의 수단으로만 사용
   - 중요한 작업은 `SIGTERM`으로 정상 종료

3. **리소스 관리**
   - 동시 실행 작업 수 제한
   - 메모리 사용량 모니터링

4. **작업 로그**
   - 백그라운드 작업의 출력을 파일로 저장
   - 에러 로그 별도 관리

5. **작업 의존성**
   - 작업 간 의존성 고려
   - 순차 실행이 필요한 작업 구분