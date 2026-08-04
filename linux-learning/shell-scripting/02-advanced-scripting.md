# 고급 Bash 스크립팅

## 고급 변수 처리

### 1. 변수 확장과 치환
```bash
# 기본 변수 확장
VAR="hello"
echo $VAR
echo ${VAR}

# 기본값 설정
echo ${VAR:-"default"}  # VAR가 설정되지 않았으면 default
echo ${VAR:="default"}  # VAR가 설정되지 않았으면 default로 설정

# 변수 길이
echo ${#VAR}

# 문자열 자르기
echo ${VAR:0:3}    # 처음 3글자
echo ${VAR:2}      # 3번째부터 끝까지
echo ${VAR: -3}    # 마지막 3글자

# 문자열 치환
echo ${VAR/hello/goodbye}  # 첫 번째 hello를 goodbye로
echo ${VAR//l/L}           # 모든 l을 L로
echo ${VAR/#hello/goodbye} # 시작이 hello면 goodbye로
echo ${VAR/%hello/goodbye} # 끝이 hello면 goodbye로
```

### 2. 배열과 연관 배열
```bash
# 일반 배열
declare -a ARRAY=("item1" "item2" "item3")
echo ${ARRAY[0]}
echo ${ARRAY[@]}
echo ${#ARRAY[@]}

# 연관 배열
declare -A ASSOC_ARRAY
ASSOC_ARRAY["name"]="홍길동"
ASSOC_ARRAY["age"]="30"
ASSOC_ARRAY["city"]="서울"

echo ${ASSOC_ARRAY["name"]}
echo ${!ASSOC_ARRAY[@]}  # 키 목록
echo ${ASSOC_ARRAY[@]}   # 값 목록
```

## 실습 예제

### 실습 1: 고급 변수 처리
```bash
# 고급 변수 처리 실습
cat > advanced_variables.sh << 'EOF'
#!/bin/bash

echo "=== 고급 변수 처리 실습 ==="
echo

# 기본 변수 설정
NAME="홍길동"
AGE=""
CITY="서울"

echo "1. 기본값 설정:"
echo "이름: ${NAME:-"이름 없음"}"
echo "나이: ${AGE:-"나이 없음"}"
echo "도시: ${CITY:-"도시 없음"}"

echo -e "\n2. 변수 길이:"
echo "이름 길이: ${#NAME}"
echo "도시 길이: ${#CITY}"

echo -e "\n3. 문자열 자르기:"
FULL_NAME="홍길동"
echo "원본: $FULL_NAME"
echo "처음 2글자: ${FULL_NAME:0:2}"
echo "3번째부터: ${FULL_NAME:2}"
echo "마지막 2글자: ${FULL_NAME: -2}"

echo -e "\n4. 문자열 치환:"
TEXT="hello world hello"
echo "원본: $TEXT"
echo "첫 번째 hello를 goodbye로: ${TEXT/hello/goodbye}"
echo "모든 hello를 goodbye로: ${TEXT//hello/goodbye}"
echo "시작이 hello면 goodbye로: ${TEXT/#hello/goodbye}"
echo "끝이 hello면 goodbye로: ${TEXT/%hello/goodbye}"

echo -e "\n5. 배열 처리:"
declare -a FRUITS=("사과" "바나나" "오렌지" "포도")
echo "과일 배열:"
for i in "${!FRUITS[@]}"; do
    echo "  [$i]: ${FRUITS[$i]}"
done

echo -e "\n6. 연관 배열:"
declare -A PERSON
PERSON["name"]="김철수"
PERSON["age"]="25"
PERSON["job"]="개발자"
PERSON["city"]="부산"

echo "사람 정보:"
for key in "${!PERSON[@]}"; do
    echo "  $key: ${PERSON[$key]}"
done

echo -e "\n7. 변수 확장 예제:"
FILE_PATH="/home/user/documents/file.txt"
echo "파일 경로: $FILE_PATH"
echo "디렉토리: ${FILE_PATH%/*}"
echo "파일명: ${FILE_PATH##*/}"
echo "확장자: ${FILE_PATH##*.}"
echo "확장자 제외: ${FILE_PATH%.*}"
EOF

chmod +x advanced_variables.sh
./advanced_variables.sh
```

### 실습 2: 정규표현식과 패턴 매칭
```bash
# 정규표현식과 패턴 매칭 실습
cat > regex_patterns.sh << 'EOF'
#!/bin/bash

echo "=== 정규표현식과 패턴 매칭 실습 ==="
echo

# 테스트 문자열들
TEST_STRINGS=(
    "hello123"
    "user@example.com"
    "010-1234-5678"
    "192.168.1.1"
    "file.txt"
    "script.sh"
    "12345"
    "abc"
)

echo "1. 기본 패턴 매칭:"
for str in "${TEST_STRINGS[@]}"; do
    if [[ $str =~ ^[a-z]+[0-9]+$ ]]; then
        echo "  $str: 영문자+숫자 패턴 일치"
    else
        echo "  $str: 영문자+숫자 패턴 불일치"
    fi
done

echo -e "\n2. 이메일 주소 검증:"
EMAILS=("user@example.com" "invalid-email" "test@domain.co.kr" "bad@")
for email in "${EMAILS[@]}"; do
    if [[ $email =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
        echo "  $email: 유효한 이메일"
    else
        echo "  $email: 유효하지 않은 이메일"
    fi
done

echo -e "\n3. 전화번호 검증:"
PHONES=("010-1234-5678" "02-123-4567" "031-123-4567" "123-456-7890")
for phone in "${PHONES[@]}"; do
    if [[ $phone =~ ^0[0-9]{1,2}-[0-9]{3,4}-[0-9]{4}$ ]]; then
        echo "  $phone: 유효한 전화번호"
    else
        echo "  $phone: 유효하지 않은 전화번호"
    fi
done

echo -e "\n4. IP 주소 검증:"
IPS=("192.168.1.1" "10.0.0.1" "256.1.1.1" "192.168.1")
for ip in "${IPS[@]}"; do
    if [[ $ip =~ ^([0-9]{1,3}\.){3}[0-9]{1,3}$ ]]; then
        # 각 옥텟이 0-255 범위인지 확인
        IFS='.' read -ra ADDR <<< "$ip"
        valid=true
        for octet in "${ADDR[@]}"; do
            if [ $octet -gt 255 ]; then
                valid=false
                break
            fi
        done
        if $valid; then
            echo "  $ip: 유효한 IP 주소"
        else
            echo "  $ip: 유효하지 않은 IP 주소 (범위 초과)"
        fi
    else
        echo "  $ip: 유효하지 않은 IP 주소 (형식 오류)"
    fi
done

echo -e "\n5. 파일 확장자 검증:"
FILES=("script.sh" "document.txt" "image.jpg" "archive.tar.gz" "noextension")
for file in "${FILES[@]}"; do
    if [[ $file =~ \.(sh|bash)$ ]]; then
        echo "  $file: 스크립트 파일"
    elif [[ $file =~ \.(txt|md)$ ]]; then
        echo "  $file: 텍스트 파일"
    elif [[ $file =~ \.(jpg|png|gif)$ ]]; then
        echo "  $file: 이미지 파일"
    elif [[ $file =~ \.(tar|gz|zip)$ ]]; then
        echo "  $file: 압축 파일"
    else
        echo "  $file: 기타 파일"
    fi
done

echo -e "\n6. 문자열 추출:"
LOG_LINE="2023-12-25 10:30:45 [INFO] User login: john.doe"
if [[ $LOG_LINE =~ ([0-9]{4}-[0-9]{2}-[0-9]{2}) ]]; then
    echo "  날짜: ${BASH_REMATCH[1]}"
fi
if [[ $LOG_LINE =~ \[([A-Z]+)\] ]]; then
    echo "  로그 레벨: ${BASH_REMATCH[1]}"
fi
if [[ $LOG_LINE =~ User login: ([a-zA-Z.]+) ]]; then
    echo "  사용자: ${BASH_REMATCH[1]}"
fi
EOF

chmod +x regex_patterns.sh
./regex_patterns.sh
```

### 실습 3: 고급 함수와 모듈화
```bash
# 고급 함수와 모듈화 실습
cat > advanced_functions.sh << 'EOF'
#!/bin/bash

echo "=== 고급 함수와 모듈화 실습 ==="
echo

# 로깅 함수
log() {
    local level=$1
    shift
    local message="$*"
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[$timestamp] [$level] $message"
}

# 에러 처리 함수
handle_error() {
    local exit_code=$1
    local message=$2
    if [ $exit_code -ne 0 ]; then
        log "ERROR" "$message (종료 코드: $exit_code)"
        exit $exit_code
    fi
}

# 파일 처리 함수
process_file() {
    local file_path=$1
    local operation=$2
    
    if [ ! -f "$file_path" ]; then
        log "ERROR" "파일이 존재하지 않습니다: $file_path"
        return 1
    fi
    
    case $operation in
        "count_lines")
            local count=$(wc -l < "$file_path")
            log "INFO" "파일 줄 수: $count"
            echo $count
            ;;
        "count_words")
            local count=$(wc -w < "$file_path")
            log "INFO" "파일 단어 수: $count"
            echo $count
            ;;
        "search")
            local pattern=$3
            local matches=$(grep -c "$pattern" "$file_path" 2>/dev/null || echo "0")
            log "INFO" "패턴 '$pattern' 매칭 수: $matches"
            echo $matches
            ;;
        *)
            log "ERROR" "지원하지 않는 작업: $operation"
            return 1
            ;;
    esac
}

# 데이터베이스 시뮬레이션 함수
db_insert() {
    local table=$1
    local data=$2
    local id=$(date +%s)
    echo "$id|$data" >> "db_${table}.txt"
    log "INFO" "데이터 삽입 완료: ID=$id, Table=$table"
    echo $id
}

db_select() {
    local table=$1
    local id=$2
    local file="db_${table}.txt"
    
    if [ ! -f "$file" ]; then
        log "ERROR" "테이블이 존재하지 않습니다: $table"
        return 1
    fi
    
    if [ -n "$id" ]; then
        local result=$(grep "^$id|" "$file")
        if [ -n "$result" ]; then
            echo "$result"
        else
            log "WARNING" "ID $id를 찾을 수 없습니다"
            return 1
        fi
    else
        cat "$file"
    fi
}

# 설정 파일 처리 함수
load_config() {
    local config_file=$1
    if [ ! -f "$config_file" ]; then
        log "ERROR" "설정 파일이 존재하지 않습니다: $config_file"
        return 1
    fi
    
    while IFS='=' read -r key value; do
        # 주석과 빈 줄 건너뛰기
        [[ $key =~ ^[[:space:]]*# ]] && continue
        [[ -z $key ]] && continue
        
        # 공백 제거
        key=$(echo "$key" | xargs)
        value=$(echo "$value" | xargs)
        
        # 변수로 설정
        eval "$key=\"$value\""
        log "DEBUG" "설정 로드: $key=$value"
    done < "$config_file"
}

# 메인 실행
echo "1. 로깅 함수 테스트:"
log "INFO" "애플리케이션 시작"
log "WARNING" "경고 메시지"
log "ERROR" "에러 메시지"

echo -e "\n2. 파일 처리 함수 테스트:"
# 테스트 파일 생성
echo "첫 번째 줄
두 번째 줄
세 번째 줄
네 번째 줄" > test_file.txt

log "INFO" "테스트 파일 생성 완료"

# 파일 처리
line_count=$(process_file "test_file.txt" "count_lines")
word_count=$(process_file "test_file.txt" "count_words")
search_count=$(process_file "test_file.txt" "search" "번째")

echo -e "\n3. 데이터베이스 함수 테스트:"
# 데이터 삽입
user_id1=$(db_insert "users" "홍길동|30|서울")
user_id2=$(db_insert "users" "김철수|25|부산")

# 데이터 조회
echo "모든 사용자:"
db_select "users"
echo -e "\n특정 사용자 (ID: $user_id1):"
db_select "users" "$user_id1"

echo -e "\n4. 설정 파일 처리 테스트:"
# 설정 파일 생성
cat > config.txt << 'CONFIG'
# 애플리케이션 설정
APP_NAME=MyApp
APP_VERSION=1.0.0
DEBUG_MODE=true
LOG_LEVEL=INFO
DATABASE_HOST=localhost
DATABASE_PORT=3306
CONFIG

# 설정 로드
load_config "config.txt"
echo "애플리케이션: $APP_NAME $APP_VERSION"
echo "디버그 모드: $DEBUG_MODE"
echo "데이터베이스: $DATABASE_HOST:$DATABASE_PORT"

echo -e "\n5. 정리:"
rm -f test_file.txt db_users.txt config.txt
log "INFO" "임시 파일 정리 완료"
EOF

chmod +x advanced_functions.sh
./advanced_functions.sh
```

### 실습 4: 스크립트 모니터링과 로깅
```bash
# 스크립트 모니터링과 로깅 실습
cat > monitoring_logging.sh << 'EOF'
#!/bin/bash

echo "=== 스크립트 모니터링과 로깅 실습 ==="
echo

# 로그 설정
LOG_FILE="script_monitor.log"
PID_FILE="script_monitor.pid"

# 로그 함수
log_message() {
    local level=$1
    shift
    local message="$*"
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    local pid=$$
    echo "[$timestamp] [PID:$pid] [$level] $message" | tee -a "$LOG_FILE"
}

# 프로세스 모니터링 함수
monitor_processes() {
    local process_name=$1
    local max_count=$2
    
    local count=$(pgrep -c "$process_name")
    if [ $count -gt $max_count ]; then
        log_message "WARNING" "프로세스 '$process_name'이 $max_count개를 초과했습니다 (현재: $count개)"
        return 1
    else
        log_message "INFO" "프로세스 '$process_name' 정상 (현재: $count개)"
        return 0
    fi
}

# 시스템 리소스 모니터링
monitor_resources() {
    local cpu_threshold=80
    local memory_threshold=90
    
    # CPU 사용률 확인
    local cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)
    if (( $(echo "$cpu_usage > $cpu_threshold" | bc -l) )); then
        log_message "WARNING" "CPU 사용률이 높습니다: ${cpu_usage}%"
    else
        log_message "INFO" "CPU 사용률 정상: ${cpu_usage}%"
    fi
    
    # 메모리 사용률 확인
    local memory_usage=$(free | grep Mem | awk '{printf "%.1f", $3/$2 * 100.0}')
    if (( $(echo "$memory_usage > $memory_threshold" | bc -l) )); then
        log_message "WARNING" "메모리 사용률이 높습니다: ${memory_usage}%"
    else
        log_message "INFO" "메모리 사용률 정상: ${memory_usage}%"
    fi
}

# 디스크 사용량 모니터링
monitor_disk() {
    local threshold=90
    
    df -h | awk 'NR>1 {gsub(/%/, "", $5); if($5 > threshold) print $0}' threshold=$threshold | while read line; do
        if [ -n "$line" ]; then
            log_message "WARNING" "디스크 사용률이 높습니다: $line"
        fi
    done
}

# 네트워크 연결 모니터링
monitor_network() {
    local port=$1
    local max_connections=$2
    
    if [ -n "$port" ]; then
        local connections=$(ss -tuln | grep ":$port " | wc -l)
        if [ $connections -gt $max_connections ]; then
            log_message "WARNING" "포트 $port의 연결 수가 많습니다: $connections개"
        else
            log_message "INFO" "포트 $port 연결 수 정상: $connections개"
        fi
    fi
}

# 로그 로테이션
rotate_logs() {
    local log_file=$1
    local max_size=1048576  # 1MB
    
    if [ -f "$log_file" ]; then
        local file_size=$(stat -c%s "$log_file")
        if [ $file_size -gt $max_size ]; then
            local timestamp=$(date +"%Y%m%d_%H%M%S")
            mv "$log_file" "${log_file}.${timestamp}"
            log_message "INFO" "로그 파일 로테이션 완료: $log_file"
        fi
    fi
}

# 메인 모니터링 루프
main_monitor() {
    local interval=5
    local max_iterations=10
    
    log_message "INFO" "모니터링 시작 (간격: ${interval}초, 최대 반복: ${max_iterations}회)"
    
    for i in $(seq 1 $max_iterations); do
        log_message "INFO" "모니터링 반복 $i/$max_iterations"
        
        # 프로세스 모니터링
        monitor_processes "bash" 10
        
        # 리소스 모니터링
        monitor_resources
        
        # 디스크 모니터링
        monitor_disk
        
        # 네트워크 모니터링
        monitor_network "22" 5
        
        # 로그 로테이션
        rotate_logs "$LOG_FILE"
        
        if [ $i -lt $max_iterations ]; then
            sleep $interval
        fi
    done
    
    log_message "INFO" "모니터링 완료"
}

# 시그널 핸들러
cleanup() {
    log_message "INFO" "스크립트 종료 중..."
    rm -f "$PID_FILE"
    exit 0
}

# 시그널 등록
trap cleanup SIGINT SIGTERM

# PID 파일 생성
echo $$ > "$PID_FILE"

# 메인 실행
main_monitor

# 정리
cleanup
EOF

chmod +x monitoring_logging.sh
./monitoring_logging.sh
```

## 유용한 명령어들

### 1. 고급 텍스트 처리
```bash
# awk 사용
awk '{print $1, $3}' file.txt
awk -F',' '{print $1, $2}' file.csv

# sed 사용
sed 's/old/new/g' file.txt
sed -n '1,10p' file.txt

# sort와 uniq
sort file.txt | uniq
sort -nr file.txt | head -10
```

### 2. 프로세스 관리
```bash
# 백그라운드 실행
nohup command &

# 프로세스 모니터링
ps aux | grep process_name
pgrep process_name
pkill process_name
```

### 3. 파일 처리
```bash
# 파일 검색
find /path -name "*.txt" -type f
find /path -size +100M -type f

# 파일 비교
diff file1.txt file2.txt
cmp file1.txt file2.txt
```

## 주의사항

1. **성능 최적화**
   - 불필요한 명령어 실행 방지
   - 효율적인 반복문 사용
   - 메모리 사용량 고려

2. **에러 처리**
   - 모든 명령어의 종료 코드 확인
   - 파일 존재 여부 확인
   - 권한 확인

3. **보안 고려사항**
   - 사용자 입력 검증
   - 파일 경로 검증
   - 권한 확인

4. **로깅과 모니터링**
   - 적절한 로그 레벨 사용
   - 로그 파일 크기 관리
   - 모니터링 임계값 설정

5. **코드 품질**
   - 함수 모듈화
   - 변수명 명확화
   - 주석 작성