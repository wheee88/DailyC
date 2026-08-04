# 리눅스 파일 시스템 구조

## 파일 시스템 계층 구조 (FHS)

리눅스는 모든 것을 파일로 관리하는 유닉스 철학을 따릅니다. 모든 디렉토리와 파일은 루트(`/`)에서 시작하는 트리 구조를 가집니다.

### 주요 디렉토리들

```
/ (root)
├── bin/          # 기본 명령어들
├── boot/         # 부트로더와 커널
├── dev/          # 디바이스 파일들
├── etc/          # 시스템 설정 파일들
├── home/         # 사용자 홈 디렉토리들
├── lib/          # 공유 라이브러리들
├── media/        # 이동식 미디어 마운트점
├── mnt/          # 임시 마운트점
├── opt/          # 추가 소프트웨어
├── proc/         # 프로세스 정보 (가상 파일시스템)
├── root/         # root 사용자 홈 디렉토리
├── run/          # 런타임 데이터
├── sbin/         # 시스템 관리 명령어들
├── srv/          # 서비스 데이터
├── sys/          # 시스템 정보 (가상 파일시스템)
├── tmp/          # 임시 파일들
├── usr/          # 사용자 프로그램들
└── var/          # 가변 데이터 (로그, 캐시 등)
```

## 디렉토리별 상세 설명

### 1. `/bin` - 기본 명령어
```bash
ls /bin/ | head -10
# 주요 명령어들: ls, cp, mv, rm, cat, echo, chmod, chown 등
```

### 2. `/etc` - 시스템 설정
```bash
ls /etc/ | head -10
# 주요 설정 파일들: passwd, group, hosts, fstab, crontab 등
```

### 3. `/home` - 사용자 디렉토리
```bash
ls -la /home/
# 각 사용자의 개인 디렉토리
```

### 4. `/var` - 가변 데이터
```bash
ls /var/
# 로그, 캐시, 임시 파일들이 저장되는 곳
```

### 5. `/proc` - 프로세스 정보
```bash
ls /proc/ | head -10
# 실행 중인 프로세스들의 정보 (가상 파일시스템)
```

## 실습 예제

### 실습 1: 파일 시스템 탐색
```bash
# 루트 디렉토리 구조 확인
ls -la /

# 각 주요 디렉토리의 용도 확인
echo "=== /bin 디렉토리 ==="
ls /bin/ | wc -l
echo "총 $(ls /bin/ | wc -l)개의 기본 명령어"

echo "=== /etc 디렉토리 ==="
ls /etc/ | wc -l
echo "총 $(ls /etc/ | wc -l)개의 설정 파일"

echo "=== /home 디렉토리 ==="
ls -la /home/

echo "=== /var 디렉토리 ==="
du -sh /var/* 2>/dev/null | sort -hr | head -5
```

### 실습 2: 시스템 정보 수집
```bash
# 시스템 정보 수집 스크립트
cat > filesystem_info.sh << 'EOF'
#!/bin/bash

echo "=== 파일 시스템 구조 분석 ==="
echo

echo "1. 루트 디렉토리 구조:"
ls -la / | grep "^d"

echo -e "\n2. 각 디렉토리별 파일 수:"
for dir in bin sbin etc usr var; do
    if [ -d "/$dir" ]; then
        count=$(ls /$dir 2>/dev/null | wc -l)
        echo "  /$dir: $count 개 파일"
    fi
done

echo -e "\n3. 디스크 사용량 (상위 5개):"
du -sh /* 2>/dev/null | sort -hr | head -5

echo -e "\n4. 가장 큰 디렉토리들:"
du -sh /var/* 2>/dev/null | sort -hr | head -5

echo -e "\n5. 현재 사용자 홈 디렉토리:"
echo "  홈 디렉토리: $HOME"
echo "  홈 디렉토리 크기: $(du -sh $HOME | cut -f1)"
EOF

chmod +x filesystem_info.sh
./filesystem_info.sh
```

### 실습 3: 특정 파일 찾기
```bash
# 시스템에서 특정 파일들 찾기
cat > find_files.sh << 'EOF'
#!/bin/bash

echo "=== 시스템 파일 검색 ==="
echo

echo "1. passwd 파일 위치:"
find / -name "passwd" 2>/dev/null

echo -e "\n2. .conf 파일들 (상위 10개):"
find /etc -name "*.conf" 2>/dev/null | head -10

echo -e "\n3. 로그 파일들:"
find /var/log -name "*.log" 2>/dev/null | head -10

echo -e "\n4. 실행 파일들 (bin 디렉토리):"
find /bin /sbin /usr/bin /usr/sbin -type f -executable 2>/dev/null | head -10

echo -e "\n5. 최근 수정된 파일들 (상위 10개):"
find /var/log -type f -mtime -1 2>/dev/null | head -10
EOF

chmod +x find_files.sh
./find_files.sh
```

## 파일 시스템 타입

### 1. 일반적인 파일 시스템 타입
```bash
# 마운트된 파일 시스템 확인
df -T

# 파일 시스템 타입별 정리
df -T | awk 'NR>1 {print $2}' | sort | uniq -c
```

### 2. 주요 파일 시스템 타입
- **ext4**: 리눅스의 기본 파일 시스템
- **xfs**: 고성능 파일 시스템
- **btrfs**: 고급 기능을 제공하는 파일 시스템
- **tmpfs**: 메모리 기반 임시 파일 시스템
- **proc**: 프로세스 정보 가상 파일 시스템
- **sysfs**: 커널 객체 정보 가상 파일 시스템

## 마운트 포인트 관리

### 1. 마운트 정보 확인
```bash
# 마운트된 파일 시스템 목록
mount

# 특정 형식으로 마운트 정보 출력
mount | column -t

# /proc/mounts 파일 확인
cat /proc/mounts
```

### 2. 마운트 포인트 분석
```bash
# 마운트 포인트 분석 스크립트
cat > mount_analysis.sh << 'EOF'
#!/bin/bash

echo "=== 마운트 포인트 분석 ==="
echo

echo "1. 마운트된 파일 시스템 수:"
mount | wc -l

echo -e "\n2. 파일 시스템 타입별 개수:"
mount | awk '{print $5}' | sort | uniq -c

echo -e "\n3. 디스크 사용량:"
df -h

echo -e "\n4. inode 사용량:"
df -i

echo -e "\n5. 특별한 마운트 포인트들:"
mount | grep -E "(tmpfs|proc|sysfs|devpts)"
EOF

chmod +x mount_analysis.sh
./mount_analysis.sh
```

## 심볼릭 링크와 하드 링크

### 1. 링크 이해하기
```bash
# 심볼릭 링크 생성
ln -s /etc/passwd passwd_link

# 하드 링크 생성
ln /etc/passwd passwd_hard

# 링크 정보 확인
ls -li passwd_link passwd_hard /etc/passwd

# 링크 타입 확인
file passwd_link
file passwd_hard
```

### 2. 링크 실습
```bash
# 링크 실습 스크립트
cat > link_practice.sh << 'EOF'
#!/bin/bash

echo "=== 링크 실습 ==="
echo

# 원본 파일 생성
echo "Hello World" > original.txt
echo "원본 파일 생성: original.txt"

# 심볼릭 링크 생성
ln -s original.txt symlink.txt
echo "심볼릭 링크 생성: symlink.txt"

# 하드 링크 생성
ln original.txt hardlink.txt
echo "하드 링크 생성: hardlink.txt"

echo -e "\n=== 파일 정보 비교 ==="
ls -li original.txt symlink.txt hardlink.txt

echo -e "\n=== 파일 내용 확인 ==="
echo "원본: $(cat original.txt)"
echo "심볼릭 링크: $(cat symlink.txt)"
echo "하드 링크: $(cat hardlink.txt)"

echo -e "\n=== 원본 파일 수정 ==="
echo "Modified Content" > original.txt
echo "원본 파일 내용 수정"

echo -e "\n=== 수정 후 내용 확인 ==="
echo "원본: $(cat original.txt)"
echo "심볼릭 링크: $(cat symlink.txt)"
echo "하드 링크: $(cat hardlink.txt)"

# 정리
rm original.txt symlink.txt hardlink.txt
echo -e "\n실습 파일들 정리 완료"
EOF

chmod +x link_practice.sh
./link_practice.sh
```

## 파일 시스템 권한

### 1. 권한 확인
```bash
# 파일 권한 확인
ls -la /etc/passwd

# 디렉토리 권한 확인
ls -ld /home

# 권한 상세 분석
stat /etc/passwd
```

### 2. 권한 실습
```bash
# 권한 실습 스크립트
cat > permission_practice.sh << 'EOF'
#!/bin/bash

echo "=== 파일 권한 실습 ==="
echo

# 테스트 파일 생성
touch test_file.txt
mkdir test_dir

echo "1. 기본 권한 확인:"
ls -la test_file.txt test_dir

echo -e "\n2. 권한 변경 (읽기 전용):"
chmod 444 test_file.txt
ls -la test_file.txt

echo -e "\n3. 권한 변경 (실행 가능):"
chmod 755 test_file.txt
ls -la test_file.txt

echo -e "\n4. 디렉토리 권한 변경:"
chmod 700 test_dir
ls -ld test_dir

echo -e "\n5. 8진법 권한 표시:"
stat -c "%a %n" test_file.txt test_dir

# 정리
rm -rf test_file.txt test_dir
echo -e "\n실습 파일들 정리 완료"
EOF

chmod +x permission_practice.sh
./permission_practice.sh
```

## 유용한 명령어들

### 1. 파일 시스템 정보
```bash
# 파일 시스템 사용량
df -h

# 디렉토리 사용량
du -sh /path/to/directory

# 파일 시스템 타입
blkid

# 마운트 정보
findmnt
```

### 2. 파일 검색
```bash
# 파일 찾기
find /path -name "filename"

# 파일 타입별 검색
find /path -type f -name "*.txt"

# 크기별 검색
find /path -size +100M

# 시간별 검색
find /path -mtime -7  # 7일 이내 수정된 파일
```

### 3. 디스크 관리
```bash
# 디스크 파티션 정보
fdisk -l

# 디스크 사용량 분석
ncdu /path/to/directory

# 파일 시스템 체크
fsck /dev/sda1
```

## 주의사항

1. **시스템 디렉토리 주의**
   - `/etc`, `/bin`, `/sbin` 등은 시스템에 중요
   - 실수로 삭제하거나 수정하지 않도록 주의

2. **권한 관리**
   - 파일 권한을 잘못 설정하면 보안 문제 발생 가능
   - 중요한 파일은 백업 후 수정

3. **디스크 공간 관리**
   - 정기적으로 디스크 사용량 확인
   - 로그 파일이 너무 커지지 않도록 관리

4. **링크 사용**
   - 심볼릭 링크는 원본이 삭제되면 깨짐
   - 하드 링크는 원본과 동일한 inode 공유