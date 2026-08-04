# 파일 권한 관리

## 파일 권한 개념

리눅스에서 모든 파일과 디렉토리는 소유자(owner), 그룹(group), 기타 사용자(others)에 대한 읽기(r), 쓰기(w), 실행(x) 권한을 가집니다.

## 권한 표시 방법

### 1. 권한 표시 형식
```bash
# 파일 권한 확인
ls -l file.txt

# 출력 예시: -rw-r--r-- 1 user group 1024 Dec 25 10:00 file.txt
#           ^^^^^^^^^ ^   ^     ^     ^
#           권한      링크 소유자 그룹 크기
```

### 2. 권한 문자 의미
```bash
# 권한 문자 설명
# r (read): 읽기 권한 (4)
# w (write): 쓰기 권한 (2)
# x (execute): 실행 권한 (1)

# 파일 타입
# -: 일반 파일
# d: 디렉토리
# l: 심볼릭 링크
# c: 문자 디바이스
# b: 블록 디바이스
```

### 3. 8진법 권한 표시
```bash
# 8진법 권한 계산
# rwx = 4+2+1 = 7
# rw- = 4+2+0 = 6
# r-- = 4+0+0 = 4
# --- = 0+0+0 = 0

# 예시
# 755 = rwxr-xr-x
# 644 = rw-r--r--
# 600 = rw-------
```

## 실습 예제

### 실습 1: 기본 권한 확인
```bash
# 기본 권한 확인 실습
cat > permission_basics.sh << 'EOF'
#!/bin/bash

echo "=== 파일 권한 기본 실습 ==="
echo

# 테스트 파일 생성
echo "Hello World" > test_file.txt
mkdir test_dir

echo "1. 파일 권한 확인:"
ls -l test_file.txt

echo -e "\n2. 디렉토리 권한 확인:"
ls -ld test_dir

echo -e "\n3. 권한 상세 분석:"
echo "파일 권한:"
stat -c "%a %n" test_file.txt
stat -c "%A %n" test_file.txt

echo -e "\n디렉토리 권한:"
stat -c "%a %n" test_dir
stat -c "%A %n" test_dir

echo -e "\n4. 8진법 권한 설명:"
echo "755 = rwxr-xr-x (소유자: 읽기/쓰기/실행, 그룹/기타: 읽기/실행)"
echo "644 = rw-r--r-- (소유자: 읽기/쓰기, 그룹/기타: 읽기)"
echo "600 = rw------- (소유자: 읽기/쓰기, 그룹/기타: 권한 없음)"

# 정리
rm -rf test_file.txt test_dir
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x permission_basics.sh
./permission_basics.sh
```

### 실습 2: 권한 변경 실습
```bash
# 권한 변경 실습
cat > permission_change.sh << 'EOF'
#!/bin/bash

echo "=== 권한 변경 실습 ==="
echo

# 테스트 파일 생성
echo "Test Content" > test_file.txt
mkdir test_dir

echo "1. 기본 권한 확인:"
ls -l test_file.txt test_dir

echo -e "\n2. 8진법으로 권한 변경:"
chmod 755 test_file.txt
echo "파일 권한을 755로 변경:"
ls -l test_file.txt

chmod 700 test_dir
echo -e "\n디렉토리 권한을 700으로 변경:"
ls -ld test_dir

echo -e "\n3. 문자로 권한 변경:"
chmod u+x test_file.txt
echo "소유자에게 실행 권한 추가:"
ls -l test_file.txt

chmod g-w test_file.txt
echo -e "\n그룹에서 쓰기 권한 제거:"
ls -l test_file.txt

chmod o+r test_file.txt
echo -e "\n기타 사용자에게 읽기 권한 추가:"
ls -l test_file.txt

echo -e "\n4. 복합 권한 변경:"
chmod u+rwx,g+rx,o+r test_file.txt
echo "복합 권한 설정:"
ls -l test_file.txt

echo -e "\n5. 권한 제거:"
chmod a-w test_file.txt
echo "모든 사용자에서 쓰기 권한 제거:"
ls -l test_file.txt

echo -e "\n6. 권한 복원:"
chmod 644 test_file.txt
echo "권한을 644로 복원:"
ls -l test_file.txt

# 정리
rm -rf test_file.txt test_dir
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x permission_change.sh
./permission_change.sh
```

### 실습 3: 디렉토리 권한 실습
```bash
# 디렉토리 권한 실습
cat > directory_permissions.sh << 'EOF'
#!/bin/bash

echo "=== 디렉토리 권한 실습 ==="
echo

# 테스트 디렉토리 생성
mkdir -p test_dir/sub_dir
echo "Test File" > test_dir/file.txt
echo "Sub File" > test_dir/sub_dir/sub_file.txt

echo "1. 디렉토리 구조 생성:"
tree test_dir 2>/dev/null || find test_dir -type d -exec echo "디렉토리: {}" \;

echo -e "\n2. 기본 권한 확인:"
ls -la test_dir/
ls -la test_dir/sub_dir/

echo -e "\n3. 디렉토리 권한 변경 실습:"
echo "디렉토리 권한을 755로 변경:"
chmod 755 test_dir
ls -ld test_dir

echo -e "\n디렉토리 권한을 700으로 변경:"
chmod 700 test_dir
ls -ld test_dir

echo -e "\n4. 디렉토리 접근 테스트:"
echo "디렉토리 내용 보기:"
ls -la test_dir/ 2>/dev/null || echo "접근 권한 없음"

echo -e "\n5. 디렉토리 권한 복원:"
chmod 755 test_dir
echo "권한 복원 후 접근 테스트:"
ls -la test_dir/

echo -e "\n6. 하위 디렉토리 권한 변경:"
chmod 700 test_dir/sub_dir
echo "하위 디렉토리 권한을 700으로 변경:"
ls -ld test_dir/sub_dir

echo -e "\n7. 재귀적 권한 변경:"
chmod -R 755 test_dir
echo "재귀적으로 권한을 755로 변경:"
find test_dir -type d -exec ls -ld {} \;

# 정리
rm -rf test_dir
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x directory_permissions.sh
./directory_permissions.sh
```

## 특수 권한

### 1. SUID, SGID, Sticky Bit
```bash
# 특수 권한 설명
cat > special_permissions.sh << 'EOF'
#!/bin/bash

echo "=== 특수 권한 설명 ==="
echo

echo "1. SUID (Set User ID):"
echo "   - 파일 실행 시 소유자 권한으로 실행"
echo "   - 8진법: 4000"
echo "   - 문자: s (소유자 실행 권한 위치)"

echo -e "\n2. SGID (Set Group ID):"
echo "   - 파일 실행 시 그룹 권한으로 실행"
echo "   - 디렉토리에 설정 시 새 파일이 그룹 소유"
echo "   - 8진법: 2000"
echo "   - 문자: s (그룹 실행 권한 위치)"

echo -e "\n3. Sticky Bit:"
echo "   - 디렉토리에 설정 시 소유자만 파일 삭제 가능"
echo "   - 8진법: 1000"
echo "   - 문자: t (기타 사용자 실행 권한 위치)"

echo -e "\n4. 특수 권한 예시:"
echo "   - /usr/bin/passwd: SUID 설정 (root 권한으로 실행)"
echo "   - /tmp: Sticky Bit 설정 (소유자만 삭제 가능)"
echo "   - /var/mail: SGID 설정 (메일 파일이 mail 그룹 소유)"
EOF

chmod +x special_permissions.sh
./special_permissions.sh
```

### 2. 특수 권한 실습
```bash
# 특수 권한 실습
cat > special_permissions_practice.sh << 'EOF'
#!/bin/bash

echo "=== 특수 권한 실습 ==="
echo

# 테스트 파일 생성
echo "#!/bin/bash" > test_script.sh
echo "echo 'Hello from test script'" >> test_script.sh
echo "whoami" >> test_script.sh
chmod +x test_script.sh

echo "1. 기본 스크립트 실행:"
./test_script.sh

echo -e "\n2. SUID 권한 설정:"
chmod u+s test_script.sh
echo "SUID 권한 설정 후 권한 확인:"
ls -l test_script.sh

echo -e "\n3. SGID 권한 설정:"
chmod g+s test_script.sh
echo "SGID 권한 설정 후 권한 확인:"
ls -l test_script.sh

echo -e "\n4. Sticky Bit 설정 (디렉토리):"
mkdir test_sticky_dir
chmod +t test_sticky_dir
echo "Sticky Bit 설정 후 권한 확인:"
ls -ld test_sticky_dir

echo -e "\n5. 8진법으로 특수 권한 설정:"
chmod 4755 test_script.sh
echo "4755 (SUID + 755) 설정:"
ls -l test_script.sh

chmod 2755 test_script.sh
echo -e "\n2755 (SGID + 755) 설정:"
ls -l test_script.sh

chmod 1755 test_sticky_dir
echo -e "\n1755 (Sticky + 755) 설정:"
ls -ld test_sticky_dir

echo -e "\n6. 특수 권한 제거:"
chmod u-s test_script.sh
chmod g-s test_script.sh
chmod t- test_sticky_dir
echo "특수 권한 제거 완료"

# 정리
rm -rf test_script.sh test_sticky_dir
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x special_permissions_practice.sh
./special_permissions_practice.sh
```

## umask 설정

### 1. umask 개념
```bash
# umask 설명
cat > umask_explanation.sh << 'EOF'
#!/bin/bash

echo "=== umask 설명 ==="
echo

echo "1. 현재 umask 값:"
umask

echo -e "\n2. umask 의미:"
echo "umask는 새로 생성되는 파일/디렉토리의 기본 권한에서 제외할 권한"
echo "기본 권한: 파일 666, 디렉토리 777"
echo "실제 권한 = 기본 권한 - umask"

echo -e "\n3. umask 값별 권한:"
echo "umask 022: 파일 644, 디렉토리 755"
echo "umask 027: 파일 640, 디렉토리 750"
echo "umask 077: 파일 600, 디렉토리 700"

echo -e "\n4. umask 설정 방법:"
echo "umask 022          # 현재 세션에서만"
echo "echo 'umask 022' >> ~/.bashrc  # 영구 설정"
EOF

chmod +x umask_explanation.sh
./umask_explanation.sh
```

### 2. umask 실습
```bash
# umask 실습
cat > umask_practice.sh << 'EOF'
#!/bin/bash

echo "=== umask 실습 ==="
echo

echo "1. 현재 umask 값:"
CURRENT_UMASK=$(umask)
echo "현재 umask: $CURRENT_UMASK"

echo -e "\n2. 기본 권한으로 파일/디렉토리 생성:"
echo "Hello" > file1.txt
mkdir dir1
echo "기본 권한:"
ls -l file1.txt
ls -ld dir1

echo -e "\n3. umask 022로 변경:"
umask 022
echo "Hello" > file2.txt
mkdir dir2
echo "umask 022 권한:"
ls -l file2.txt
ls -ld dir2

echo -e "\n4. umask 027로 변경:"
umask 027
echo "Hello" > file3.txt
mkdir dir3
echo "umask 027 권한:"
ls -l file3.txt
ls -ld dir3

echo -e "\n5. umask 077로 변경:"
umask 077
echo "Hello" > file4.txt
mkdir dir4
echo "umask 077 권한:"
ls -l file4.txt
ls -ld dir4

echo -e "\n6. umask 복원:"
umask $CURRENT_UMASK
echo "umask 복원: $(umask)"

# 정리
rm -rf file*.txt dir*
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x umask_practice.sh
./umask_practice.sh
```

## 권한 검색과 필터링

### 1. 권한별 파일 검색
```bash
# 권한별 파일 검색
cat > permission_search.sh << 'EOF'
#!/bin/bash

echo "=== 권한별 파일 검색 ==="
echo

# 테스트 파일들 생성
mkdir -p test_search
echo "file1" > test_search/file1.txt
echo "file2" > test_search/file2.txt
echo "file3" > test_search/file3.txt

chmod 644 test_search/file1.txt
chmod 755 test_search/file2.txt
chmod 600 test_search/file3.txt

echo "1. 생성된 파일들:"
ls -l test_search/

echo -e "\n2. 실행 가능한 파일 검색:"
find test_search -type f -executable

echo -e "\n3. 쓰기 권한이 있는 파일 검색:"
find test_search -type f -writable

echo -e "\n4. 읽기 권한이 있는 파일 검색:"
find test_search -type f -readable

echo -e "\n5. 특정 권한으로 검색 (644):"
find test_search -type f -perm 644

echo -e "\n6. 특정 권한 이상으로 검색 (600 이상):"
find test_search -type f -perm -600

echo -e "\n7. SUID 권한이 있는 파일 검색:"
find test_search -type f -perm -4000

echo -e "\n8. SGID 권한이 있는 파일 검색:"
find test_search -type f -perm -2000

echo -e "\n9. Sticky Bit가 있는 디렉토리 검색:"
find test_search -type d -perm -1000

# 정리
rm -rf test_search
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x permission_search.sh
./permission_search.sh
```

## 권한 문제 해결

### 1. 권한 문제 진단
```bash
# 권한 문제 진단
cat > permission_troubleshoot.sh << 'EOF'
#!/bin/bash

echo "=== 권한 문제 진단 ==="
echo

# 테스트 파일 생성
echo "Test Content" > test_file.txt
chmod 000 test_file.txt

echo "1. 권한 없는 파일 접근 시도:"
cat test_file.txt 2>&1 || echo "접근 거부됨"

echo -e "\n2. 파일 권한 확인:"
ls -l test_file.txt

echo -e "\n3. 파일 소유자 확인:"
ls -l test_file.txt | awk '{print $3, $4}'

echo -e "\n4. 현재 사용자 확인:"
whoami

echo -e "\n5. 그룹 확인:"
groups

echo -e "\n6. 권한 복원:"
chmod 644 test_file.txt
echo "권한 복원 후 접근:"
cat test_file.txt

echo -e "\n7. 권한 문제 해결 방법:"
echo "- 파일 소유자 확인: ls -l"
echo "- 권한 확인: ls -l"
echo "- 소유자 변경: sudo chown user:group file"
echo "- 권한 변경: chmod permissions file"
echo "- 그룹 변경: sudo chgrp group file"

# 정리
rm -f test_file.txt
echo -e "\n실습 파일 정리 완료"
EOF

chmod +x permission_troubleshoot.sh
./permission_troubleshoot.sh
```

## 유용한 명령어들

### 1. 권한 관련 명령어
```bash
# 권한 확인
ls -l, stat, find -perm

# 권한 변경
chmod, chown, chgrp

# 특수 권한
chmod +s, chmod +t

# umask 설정
umask
```

### 2. 권한 모니터링
```bash
# 권한 변경 모니터링
inotifywait -m -e attrib /path/to/directory

# 특수 권한 파일 검색
find / -type f -perm -4000 2>/dev/null  # SUID
find / -type f -perm -2000 2>/dev/null  # SGID
find / -type d -perm -1000 2>/dev/null  # Sticky Bit
```

## 주의사항

1. **권한 설정 주의**
   - 실행 권한을 잘못 설정하면 보안 위험
   - 중요한 파일은 적절한 권한 설정

2. **특수 권한 사용**
   - SUID/SGID는 필요한 경우에만 사용
   - Sticky Bit는 공유 디렉토리에 유용

3. **umask 설정**
   - 시스템 전체에 영향을 주는 설정
   - 보안을 고려한 적절한 값 설정

4. **권한 문제 해결**
   - 문제 발생 시 단계별로 진단
   - 백업 후 권한 변경

5. **보안 고려사항**
   - 정기적인 권한 검사
   - 불필요한 실행 권한 제거
   - 특수 권한 파일 모니터링