# Bash 스크립팅 기초

## Bash 스크립트 기본 구조

### 1. 스크립트 기본 형식
```bash
#!/bin/bash
# 스크립트 설명
# 작성자: 이름
# 작성일: 날짜

# 변수 선언
VARIABLE="value"

# 함수 정의
function_name() {
    # 함수 내용
}

# 메인 실행 부분
echo "Hello World"
```

### 2. 스크립트 실행 방법
```bash
# 실행 권한 부여
chmod +x script.sh

# 실행
./script.sh

# bash로 직접 실행
bash script.sh

# 소스로 실행 (현재 쉘에서 실행)
source script.sh
. script.sh
```

## 변수와 데이터 타입

### 1. 변수 선언과 사용
```bash
# 변수 선언 (공백 없이)
NAME="John"
AGE=25
CITY="Seoul"

# 변수 사용
echo $NAME
echo ${NAME}

# 변수 조합
FULL_NAME="${NAME} Doe"
echo $FULL_NAME

# 명령어 결과를 변수에 저장
CURRENT_DATE=$(date)
FILE_COUNT=$(ls | wc -l)

# 환경 변수
echo $HOME
echo $PATH
echo $USER
```

### 2. 변수 타입과 연산
```bash
# 숫자 연산
NUM1=10
NUM2=5

# 산술 연산
echo $((NUM1 + NUM2))  # 15
echo $((NUM1 - NUM2))  # 5
echo $((NUM1 * NUM2))  # 50
echo $((NUM1 / NUM2))  # 2
echo $((NUM1 % NUM2))  # 0

# 증가/감소
((NUM1++))
echo $NUM1  # 11

# 문자열 연산
STR1="Hello"
STR2="World"
COMBINED="${STR1} ${STR2}"
echo $COMBINED
```

## 실습 예제

### 실습 1: 기본 변수 사용
```bash
# 기본 변수 사용 실습
cat > variable_practice.sh << 'EOF'
#!/bin/bash

echo "=== 변수 사용 실습 ==="
echo

# 기본 변수 선언
NAME="홍길동"
AGE=30
CITY="서울"
JOB="개발자"

echo "1. 기본 변수 출력:"
echo "이름: $NAME"
echo "나이: $AGE"
echo "도시: $CITY"
echo "직업: $JOB"

echo -e "\n2. 변수 조합:"
FULL_INFO="${NAME}은(는) ${AGE}세이고, ${CITY}에서 ${JOB}로 일합니다."
echo $FULL_INFO

echo -e "\n3. 명령어 결과를 변수에 저장:"
CURRENT_TIME=$(date +"%Y-%m-%d %H:%M:%S")
SYSTEM_USER=$(whoami)
CURRENT_DIR=$(pwd)

echo "현재 시간: $CURRENT_TIME"
echo "시스템 사용자: $SYSTEM_USER"
echo "현재 디렉토리: $CURRENT_DIR"

echo -e "\n4. 환경 변수 확인:"
echo "홈 디렉토리: $HOME"
echo "PATH: $PATH"
echo "쉘: $SHELL"

echo -e "\n5. 숫자 연산:"
NUM1=100
NUM2=25
echo "$NUM1 + $NUM2 = $((NUM1 + NUM2))"
echo "$NUM1 - $NUM2 = $((NUM1 - NUM2))"
echo "$NUM1 * $NUM2 = $((NUM1 * NUM2))"
echo "$NUM1 / $NUM2 = $((NUM1 / NUM2))"
echo "$NUM1 % $NUM2 = $((NUM1 % NUM2))"

echo -e "\n6. 변수 증가/감소:"
COUNTER=0
echo "초기값: $COUNTER"
((COUNTER++))
echo "증가 후: $COUNTER"
((COUNTER += 5))
echo "5 증가 후: $COUNTER"
((COUNTER--))
echo "1 감소 후: $COUNTER"
EOF

chmod +x variable_practice.sh
./variable_practice.sh
```

### 실습 2: 사용자 입력 처리
```bash
# 사용자 입력 처리 실습
cat > input_practice.sh << 'EOF'
#!/bin/bash

echo "=== 사용자 입력 처리 실습 ==="
echo

echo "1. 기본 입력 받기:"
echo -n "이름을 입력하세요: "
read NAME
echo "안녕하세요, $NAME님!"

echo -e "\n2. 여러 변수 입력:"
echo -n "나이와 도시를 입력하세요 (예: 25 서울): "
read AGE CITY
echo "나이: $AGE, 도시: $CITY"

echo -e "\n3. 기본값이 있는 입력:"
echo -n "직업을 입력하세요 (기본값: 학생): "
read JOB
JOB=${JOB:-학생}
echo "직업: $JOB"

echo -e "\n4. 비밀번호 입력 (숨김):"
echo -n "비밀번호를 입력하세요: "
read -s PASSWORD
echo -e "\n비밀번호가 입력되었습니다."

echo -e "\n5. 배열 입력:"
echo "좋아하는 색깔 3개를 입력하세요:"
read -a COLORS
echo "입력된 색깔들:"
for color in "${COLORS[@]}"; do
    echo "- $color"
done

echo -e "\n6. 파일에서 입력 읽기:"
echo "test_input.txt 파일 생성 중..."
echo "첫 번째 줄
두 번째 줄
세 번째 줄" > test_input.txt

echo "파일 내용 읽기:"
while read line; do
    echo "읽은 줄: $line"
done < test_input.txt

# 정리
rm -f test_input.txt
echo -e "\n임시 파일 정리 완료"
EOF

chmod +x input_practice.sh
./input_practice.sh
```

## 조건문과 반복문

### 1. 조건문 (if-else)
```bash
# 기본 if 문
if [ condition ]; then
    # 실행할 명령어
fi

# if-else 문
if [ condition ]; then
    # 조건이 참일 때
else
    # 조건이 거짓일 때
fi

# if-elif-else 문
if [ condition1 ]; then
    # 조건1이 참일 때
elif [ condition2 ]; then
    # 조건2가 참일 때
else
    # 모든 조건이 거짓일 때
fi
```

### 2. 반복문 (for, while)
```bash
# for 문
for variable in list; do
    # 실행할 명령어
done

# while 문
while [ condition ]; do
    # 실행할 명령어
done

# until 문
until [ condition ]; do
    # 실행할 명령어
done
```

### 3. 조건문과 반복문 실습
```bash
# 조건문과 반복문 실습
cat > control_structures.sh << 'EOF'
#!/bin/bash

echo "=== 조건문과 반복문 실습 ==="
echo

echo "1. 기본 조건문:"
NUMBER=15
if [ $NUMBER -gt 10 ]; then
    echo "$NUMBER은 10보다 큽니다"
else
    echo "$NUMBER은 10보다 작거나 같습니다"
fi

echo -e "\n2. 문자열 비교:"
NAME="홍길동"
if [ "$NAME" = "홍길동" ]; then
    echo "이름이 일치합니다"
else
    echo "이름이 일치하지 않습니다"
fi

echo -e "\n3. 파일 존재 확인:"
if [ -f "test_file.txt" ]; then
    echo "test_file.txt 파일이 존재합니다"
else
    echo "test_file.txt 파일이 존재하지 않습니다"
    touch test_file.txt
    echo "test_file.txt 파일을 생성했습니다"
fi

echo -e "\n4. for 반복문:"
echo "1부터 5까지 출력:"
for i in {1..5}; do
    echo "숫자: $i"
done

echo -e "\n5. 배열과 for 반복문:"
FRUITS=("사과" "바나나" "오렌지" "포도")
echo "과일 목록:"
for fruit in "${FRUITS[@]}"; do
    echo "- $fruit"
done

echo -e "\n6. while 반복문:"
COUNTER=1
echo "while 반복문 (1부터 3까지):"
while [ $COUNTER -le 3 ]; do
    echo "카운터: $COUNTER"
    ((COUNTER++))
done

echo -e "\n7. until 반복문:"
COUNTER=1
echo "until 반복문 (1부터 3까지):"
until [ $COUNTER -gt 3 ]; do
    echo "카운터: $COUNTER"
    ((COUNTER++))
done

echo -e "\n8. 중첩 반복문:"
echo "구구단 2단:"
for i in {1..9}; do
    RESULT=$((2 * i))
    echo "2 x $i = $RESULT"
done

# 정리
rm -f test_file.txt
echo -e "\n임시 파일 정리 완료"
EOF

chmod +x control_structures.sh
./control_structures.sh
```

## 함수 정의와 사용

### 1. 함수 기본 구조
```bash
# 함수 정의
function_name() {
    # 함수 내용
    return value
}

# 함수 호출
function_name argument1 argument2

# 함수 결과 사용
result=$(function_name)
```

### 2. 함수 실습
```bash
# 함수 실습
cat > function_practice.sh << 'EOF'
#!/bin/bash

echo "=== 함수 실습 ==="
echo

# 기본 함수 정의
greet() {
    echo "안녕하세요, $1님!"
}

# 매개변수가 있는 함수
calculate() {
    local num1=$1
    local num2=$2
    local operation=$3
    
    case $operation in
        "add")
            echo $((num1 + num2))
            ;;
        "subtract")
            echo $((num1 - num2))
            ;;
        "multiply")
            echo $((num1 * num2))
            ;;
        "divide")
            if [ $num2 -ne 0 ]; then
                echo $((num1 / num2))
            else
                echo "0으로 나눌 수 없습니다"
            fi
            ;;
        *)
            echo "지원하지 않는 연산입니다"
            ;;
    esac
}

# 반환값이 있는 함수
is_even() {
    local num=$1
    if [ $((num % 2)) -eq 0 ]; then
        return 0  # 짝수
    else
        return 1  # 홀수
    fi
}

# 재귀 함수
factorial() {
    local n=$1
    if [ $n -le 1 ]; then
        echo 1
    else
        local prev=$(factorial $((n - 1)))
        echo $((n * prev))
    fi
}

echo "1. 기본 함수 호출:"
greet "홍길동"
greet "김철수"

echo -e "\n2. 계산 함수 사용:"
echo "10 + 5 = $(calculate 10 5 add)"
echo "10 - 5 = $(calculate 10 5 subtract)"
echo "10 * 5 = $(calculate 10 5 multiply)"
echo "10 / 5 = $(calculate 10 5 divide)"
echo "10 / 0 = $(calculate 10 0 divide)"

echo -e "\n3. 짝수/홀수 판별:"
for num in 1 2 3 4 5; do
    if is_even $num; then
        echo "$num은 짝수입니다"
    else
        echo "$num은 홀수입니다"
    fi
done

echo -e "\n4. 팩토리얼 계산:"
for num in 1 2 3 4 5; do
    echo "$num! = $(factorial $num)"
done

echo -e "\n5. 함수 내 지역 변수:"
test_local() {
    local local_var="지역 변수"
    global_var="전역 변수"
    echo "함수 내: $local_var, $global_var"
}

global_var="초기값"
echo "함수 호출 전: $global_var"
test_local
echo "함수 호출 후: $global_var"
EOF

chmod +x function_practice.sh
./function_practice.sh
```

## 파일 처리와 에러 처리

### 1. 파일 처리
```bash
# 파일 읽기
while read line; do
    echo "읽은 줄: $line"
done < file.txt

# 파일 쓰기
echo "내용" > file.txt
echo "추가 내용" >> file.txt

# 파일 존재 확인
if [ -f "file.txt" ]; then
    echo "파일이 존재합니다"
fi

# 디렉토리 존재 확인
if [ -d "directory" ]; then
    echo "디렉토리가 존재합니다"
fi
```

### 2. 에러 처리
```bash
# 명령어 실행 결과 확인
if command; then
    echo "명령어 실행 성공"
else
    echo "명령어 실행 실패"
fi

# 에러 코드 확인
command
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo "성공 (코드: $exit_code)"
else
    echo "실패 (코드: $exit_code)"
fi
```

### 3. 파일 처리와 에러 처리 실습
```bash
# 파일 처리와 에러 처리 실습
cat > file_error_handling.sh << 'EOF'
#!/bin/bash

echo "=== 파일 처리와 에러 처리 실습 ==="
echo

# 테스트 파일 생성
echo "첫 번째 줄
두 번째 줄
세 번째 줄" > test_file.txt

echo "1. 파일 읽기:"
if [ -f "test_file.txt" ]; then
    echo "파일 내용:"
    while read line; do
        echo "  $line"
    done < test_file.txt
else
    echo "파일이 존재하지 않습니다"
fi

echo -e "\n2. 파일 쓰기:"
echo "새로운 내용" > new_file.txt
echo "추가 내용" >> new_file.txt
echo "new_file.txt 내용:"
cat new_file.txt

echo -e "\n3. 디렉토리 처리:"
if [ -d "test_dir" ]; then
    echo "test_dir 디렉토리가 이미 존재합니다"
else
    mkdir test_dir
    echo "test_dir 디렉토리를 생성했습니다"
fi

echo -e "\n4. 파일 복사와 이동:"
cp test_file.txt test_dir/
echo "파일을 test_dir로 복사했습니다"

mv new_file.txt test_dir/
echo "파일을 test_dir로 이동했습니다"

echo -e "\n5. 디렉토리 내용 확인:"
ls -la test_dir/

echo -e "\n6. 에러 처리:"
# 존재하지 않는 파일 접근
if [ -f "nonexistent_file.txt" ]; then
    echo "파일이 존재합니다"
else
    echo "파일이 존재하지 않습니다 (예상된 결과)"
fi

# 명령어 실행 에러 처리
if ls nonexistent_file.txt 2>/dev/null; then
    echo "파일이 존재합니다"
else
    echo "파일이 존재하지 않습니다 (에러 처리됨)"
fi

echo -e "\n7. 명령어 실행 결과 확인:"
if command -v python3 >/dev/null 2>&1; then
    echo "Python3가 설치되어 있습니다"
    python3 --version
else
    echo "Python3가 설치되어 있지 않습니다"
fi

echo -e "\n8. 정리:"
rm -rf test_file.txt test_dir
echo "임시 파일과 디렉토리 정리 완료"
EOF

chmod +x file_error_handling.sh
./file_error_handling.sh
```

## 유용한 명령어들

### 1. 문자열 처리
```bash
# 문자열 길이
STRING="Hello World"
echo ${#STRING}

# 문자열 자르기
echo ${STRING:0:5}  # 처음 5글자
echo ${STRING:6}    # 6번째부터 끝까지

# 문자열 치환
echo ${STRING/World/Universe}
echo ${STRING//l/L}  # 모든 l을 L로
```

### 2. 배열 처리
```bash
# 배열 선언
ARRAY=("item1" "item2" "item3")

# 배열 요소 접근
echo ${ARRAY[0]}
echo ${ARRAY[@]}  # 모든 요소

# 배열 길이
echo ${#ARRAY[@]}

# 배열에 요소 추가
ARRAY+=("item4")
```

### 3. 정규표현식
```bash
# 정규표현식 매칭
if [[ "hello123" =~ ^[a-z]+[0-9]+$ ]]; then
    echo "패턴이 일치합니다"
fi

# 문자열 추출
STRING="user:john:age:25"
if [[ $STRING =~ user:([^:]+):age:([0-9]+) ]]; then
    echo "사용자: ${BASH_REMATCH[1]}"
    echo "나이: ${BASH_REMATCH[2]}"
fi
```

## 주의사항

1. **변수 사용**
   - 변수명에 공백 사용 금지
   - 문자열 변수는 따옴표로 감싸기
   - 지역 변수는 `local` 키워드 사용

2. **조건문**
   - `[`와 `]` 사이에 공백 필요
   - 문자열 비교 시 따옴표 사용
   - 숫자 비교와 문자열 비교 구분

3. **에러 처리**
   - 명령어 실행 결과 확인
   - 파일 존재 여부 확인
   - 권한 확인

4. **성능 고려사항**
   - 불필요한 명령어 실행 방지
   - 효율적인 반복문 사용
   - 메모리 사용량 고려

5. **보안 고려사항**
   - 사용자 입력 검증
   - 파일 경로 검증
   - 권한 확인