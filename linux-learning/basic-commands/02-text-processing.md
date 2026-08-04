# 텍스트 파일 처리 명령어

## 기본 텍스트 명령어들

### 1. 파일 내용 보기
```bash
cat file.txt          # 전체 파일 내용 출력
less file.txt         # 페이지 단위로 보기 (q로 종료)
more file.txt         # 페이지 단위로 보기 (스페이스로 다음 페이지)
head file.txt         # 처음 10줄만 보기
head -n 20 file.txt   # 처음 20줄만 보기
tail file.txt         # 마지막 10줄만 보기
tail -n 20 file.txt   # 마지막 20줄만 보기
tail -f file.txt      # 실시간으로 파일 변화 감시
```

### 2. 텍스트 검색
```bash
grep "pattern" file.txt        # 파일에서 패턴 검색
grep -i "pattern" file.txt     # 대소문자 구분 없이 검색
grep -n "pattern" file.txt     # 줄 번호와 함께 출력
grep -r "pattern" directory/   # 디렉토리에서 재귀적으로 검색
grep -v "pattern" file.txt     # 패턴과 일치하지 않는 줄만 출력
```

### 3. 텍스트 편집
```bash
nano file.txt         # nano 에디터로 편집
vim file.txt          # vim 에디터로 편집
sed 's/old/new/g' file.txt  # 텍스트 치환
```

### 4. 텍스트 정렬 및 필터링
```bash
sort file.txt         # 알파벳 순으로 정렬
sort -n file.txt      # 숫자 순으로 정렬
sort -r file.txt      # 역순으로 정렬
uniq file.txt         # 중복된 줄 제거
sort file.txt | uniq  # 정렬 후 중복 제거
```

### 5. 텍스트 통계
```bash
wc file.txt           # 줄, 단어, 문자 수 출력
wc -l file.txt        # 줄 수만 출력
wc -w file.txt        # 단어 수만 출력
wc -c file.txt        # 문자 수만 출력
```

## 실습 예제

### 실습 1: 로그 파일 분석
```bash
# 샘플 로그 파일 생성
cat > access.log << EOF
192.168.1.1 - - [25/Dec/2023:10:00:01] "GET /index.html HTTP/1.1" 200 1234
192.168.1.2 - - [25/Dec/2023:10:00:02] "GET /about.html HTTP/1.1" 200 5678
192.168.1.1 - - [25/Dec/2023:10:00:03] "POST /login HTTP/1.1" 302 0
192.168.1.3 - - [25/Dec/2023:10:00:04] "GET /index.html HTTP/1.1" 200 1234
192.168.1.2 - - [25/Dec/2023:10:00:05] "GET /contact.html HTTP/1.1" 404 0
EOF

# 로그 파일 내용 확인
cat access.log

# 특정 IP의 요청만 보기
grep "192.168.1.1" access.log

# 에러(404) 요청만 보기
grep "404" access.log

# GET 요청만 보기
grep "GET" access.log

# 로그 파일의 총 줄 수 확인
wc -l access.log
```

### 실습 2: 텍스트 파일 생성 및 처리
```bash
# 샘플 데이터 파일 생성
cat > students.txt << EOF
김철수,90,85,92
이영희,88,91,87
박민수,95,89,93
정수진,87,88,90
최동현,92,94,89
EOF

# 파일 내용 확인
cat students.txt

# 이름만 추출 (첫 번째 필드)
cut -d',' -f1 students.txt

# 평균 점수 계산을 위한 스크립트
cat > calculate_avg.sh << 'EOF'
#!/bin/bash
while IFS=',' read -r name score1 score2 score3; do
    total=$((score1 + score2 + score3))
    avg=$((total / 3))
    echo "$name의 평균: $avg"
done < students.txt
EOF

chmod +x calculate_avg.sh
./calculate_avg.sh
```

### 실습 3: 시스템 정보 수집
```bash
# 시스템 정보를 파일로 저장
uname -a > system_info.txt
date >> system_info.txt
whoami >> system_info.txt
pwd >> system_info.txt

# 파일 내용 확인
cat system_info.txt

# 특정 정보만 추출
grep "Linux" system_info.txt
```

## 고급 텍스트 처리

### 1. awk 사용법
```bash
# CSV 파일의 특정 필드 출력
awk -F',' '{print $1, $2}' students.txt

# 조건에 맞는 데이터만 출력
awk -F',' '$2 > 90 {print $1, $2}' students.txt

# 계산 수행
awk -F',' '{sum=$2+$3+$4; avg=sum/3; print $1, avg}' students.txt
```

### 2. sed 사용법
```bash
# 텍스트 치환
sed 's/김철수/김영수/g' students.txt

# 특정 줄 삭제
sed '2d' students.txt  # 2번째 줄 삭제

# 특정 줄만 출력
sed -n '1,3p' students.txt  # 1-3번째 줄만 출력
```

### 3. 정규표현식 활용
```bash
# 이메일 주소 찾기
grep -E '[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}' file.txt

# 전화번호 찾기 (한국 형식)
grep -E '010-[0-9]{4}-[0-9]{4}' file.txt

# IP 주소 찾기
grep -E '([0-9]{1,3}\.){3}[0-9]{1,3}' file.txt
```

## 파이프라인 활용

### 1. 명령어 연결
```bash
# 로그에서 IP 주소만 추출하고 정렬
grep "GET" access.log | awk '{print $1}' | sort | uniq -c

# 파일에서 빈 줄 제거하고 정렬
grep -v '^$' file.txt | sort

# 특정 디렉토리의 파일들 중에서 특정 패턴 찾기
find . -name "*.log" -exec grep "ERROR" {} \;
```

### 2. 결과를 파일로 저장
```bash
# 명령어 결과를 파일로 저장
ls -la > file_list.txt

# 명령어 결과를 파일에 추가
echo "새로운 정보" >> file_list.txt

# 에러와 출력을 모두 파일로 저장
command > output.txt 2>&1
```

## 유용한 팁

1. **less 명령어 단축키**
   - `q`: 종료
   - `스페이스`: 다음 페이지
   - `b`: 이전 페이지
   - `/pattern`: 검색
   - `n`: 다음 검색 결과

2. **grep 옵션들**
   - `-i`: 대소문자 구분 없음
   - `-v`: 일치하지 않는 줄
   - `-n`: 줄 번호 표시
   - `-c`: 일치하는 줄 수만 출력
   - `-A 3`: 일치하는 줄과 그 다음 3줄
   - `-B 3`: 일치하는 줄과 그 이전 3줄

3. **파이프라인 최적화**
   - 자주 사용되는 패턴을 별칭(alias)으로 등록
   - 복잡한 명령어는 스크립트로 저장
   - 정규표현식을 미리 테스트