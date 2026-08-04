# 시스템 정보 확인 명령어

## 시스템 기본 정보

### 1. 시스템 정보
```bash
uname -a              # 전체 시스템 정보
uname -s              # 운영체제 이름
uname -r              # 커널 버전
uname -m              # 하드웨어 아키텍처
hostname              # 호스트 이름
hostnamectl           # 상세 호스트 정보 (systemd)
```

### 2. 시스템 시간
```bash
date                  # 현재 날짜와 시간
date +"%Y-%m-%d"      # 특정 형식으로 날짜 출력
date +"%H:%M:%S"      # 시간만 출력
timedatectl           # 시간대 설정 확인
```

### 3. 사용자 정보
```bash
whoami                # 현재 사용자
who                   # 로그인한 사용자들
w                     # 사용자와 실행 중인 프로세스
id                    # 사용자 ID와 그룹 정보
last                  # 최근 로그인 기록
```

## 하드웨어 정보

### 1. CPU 정보
```bash
lscpu                 # CPU 상세 정보
cat /proc/cpuinfo     # CPU 정보 (원시 데이터)
nproc                 # CPU 코어 수
```

### 2. 메모리 정보
```bash
free -h               # 메모리 사용량 (사람이 읽기 쉬운 형식)
free -m               # 메모리 사용량 (MB 단위)
cat /proc/meminfo     # 메모리 상세 정보
vmstat                # 가상 메모리 통계
```

### 3. 디스크 정보
```bash
df -h                 # 디스크 사용량
du -h                 # 디렉토리별 사용량
du -sh *              # 현재 디렉토리의 각 항목별 사용량
lsblk                 # 블록 디바이스 목록
fdisk -l              # 디스크 파티션 정보
```

### 4. 네트워크 정보
```bash
ip addr               # 네트워크 인터페이스 정보
ip route              # 라우팅 테이블
ifconfig              # 네트워크 인터페이스 (legacy)
netstat -tuln         # 열린 포트 목록
ss -tuln              # 열린 포트 목록 (modern)
```

## 실습 예제

### 실습 1: 시스템 상태 점검
```bash
# 시스템 정보 수집 스크립트
cat > system_check.sh << 'EOF'
#!/bin/bash

echo "=== 시스템 정보 ==="
echo "호스트명: $(hostname)"
echo "운영체제: $(uname -s)"
echo "커널 버전: $(uname -r)"
echo "아키텍처: $(uname -m)"
echo "현재 시간: $(date)"
echo

echo "=== CPU 정보 ==="
echo "CPU 코어 수: $(nproc)"
lscpu | grep "Model name"
echo

echo "=== 메모리 정보 ==="
free -h
echo

echo "=== 디스크 사용량 ==="
df -h
echo

echo "=== 로그인한 사용자 ==="
who
echo

echo "=== 시스템 부팅 시간 ==="
uptime
EOF

chmod +x system_check.sh
./system_check.sh
```

### 실습 2: 디스크 사용량 모니터링
```bash
# 디스크 사용량 상세 분석
cat > disk_analysis.sh << 'EOF'
#!/bin/bash

echo "=== 전체 디스크 사용량 ==="
df -h

echo -e "\n=== 홈 디렉토리 사용량 ==="
du -sh ~

echo -e "\n=== 홈 디렉토리 하위 폴더별 사용량 ==="
du -sh ~/* 2>/dev/null | sort -hr

echo -e "\n=== 현재 디렉토리 사용량 ==="
du -sh .

echo -e "\n=== 현재 디렉토리 하위 폴더별 사용량 =="
du -sh */ 2>/dev/null | sort -hr
EOF

chmod +x disk_analysis.sh
./disk_analysis.sh
```

### 실습 3: 네트워크 상태 확인
```bash
# 네트워크 상태 확인 스크립트
cat > network_check.sh << 'EOF'
#!/bin/bash

echo "=== 네트워크 인터페이스 ==="
ip addr show

echo -e "\n=== 라우팅 테이블 ==="
ip route show

echo -e "\n=== 열린 포트 ==="
ss -tuln

echo -e "\n=== 네트워크 연결 상태 ==="
ss -tuln | grep LISTEN
EOF

chmod +x network_check.sh
./network_check.sh
```

## 프로세스 관리

### 1. 프로세스 확인
```bash
ps aux                # 모든 프로세스 상세 정보
ps -ef                # 프로세스 목록 (다른 형식)
top                   # 실시간 프로세스 모니터
htop                  # 향상된 top (설치 필요)
pgrep process_name    # 특정 프로세스 PID 찾기
```

### 2. 프로세스 제어
```bash
kill PID              # 프로세스 종료
kill -9 PID           # 강제 종료
killall process_name  # 프로세스 이름으로 종료
pkill pattern         # 패턴으로 프로세스 종료
```

### 3. 백그라운드 작업
```bash
command &             # 백그라운드에서 실행
nohup command &       # 터미널 종료 후에도 계속 실행
jobs                  # 백그라운드 작업 목록
fg %1                 # 백그라운드 작업을 포그라운드로
bg %1                 # 중단된 작업을 백그라운드로
```

## 실시간 모니터링

### 1. 시스템 모니터링
```bash
# 실시간 시스템 모니터링
cat > monitor.sh << 'EOF'
#!/bin/bash

while true; do
    clear
    echo "=== 시스템 모니터링 $(date) ==="
    echo
    
    echo "=== CPU 사용률 ==="
    top -bn1 | grep "Cpu(s)"
    echo
    
    echo "=== 메모리 사용량 ==="
    free -h
    echo
    
    echo "=== 디스크 사용량 ==="
    df -h | head -5
    echo
    
    echo "=== 상위 5개 프로세스 (CPU 사용률) ==="
    ps aux --sort=-%cpu | head -6
    echo
    
    echo "=== 네트워크 연결 수 ==="
    ss -tuln | wc -l
    echo
    
    sleep 5
done
EOF

chmod +x monitor.sh
# 실행하려면: ./monitor.sh
```

### 2. 로그 모니터링
```bash
# 실시간 로그 모니터링
tail -f /var/log/syslog        # 시스템 로그
tail -f /var/log/auth.log      # 인증 로그
journalctl -f                  # systemd 저널 (실시간)
```

## 시스템 성능 분석

### 1. CPU 성능
```bash
# CPU 사용률 확인
top -bn1 | grep "Cpu(s)"
vmstat 1 5                    # 1초마다 5번 샘플링
iostat -c 1 5                 # CPU 통계 (sysstat 패키지 필요)
```

### 2. 메모리 성능
```bash
# 메모리 사용 패턴 분석
cat /proc/meminfo | grep -E "(MemTotal|MemFree|MemAvailable|Buffers|Cached)"
vmstat -s                     # 메모리 통계
```

### 3. 디스크 성능
```bash
# 디스크 I/O 모니터링
iostat -x 1 5                 # 디스크 I/O 통계
iotop                         # 실시간 디스크 I/O (설치 필요)
```

## 유용한 시스템 명령어들

### 1. 시스템 서비스
```bash
systemctl status service_name  # 서비스 상태 확인
systemctl start service_name   # 서비스 시작
systemctl stop service_name    # 서비스 중지
systemctl restart service_name # 서비스 재시작
systemctl enable service_name  # 부팅 시 자동 시작
systemctl disable service_name # 부팅 시 자동 시작 해제
```

### 2. 패키지 관리
```bash
# Ubuntu/Debian
apt list --installed          # 설치된 패키지 목록
apt search package_name       # 패키지 검색
apt show package_name         # 패키지 정보

# CentOS/RHEL
yum list installed            # 설치된 패키지 목록
yum search package_name       # 패키지 검색
yum info package_name         # 패키지 정보
```

### 3. 환경 변수
```bash
env                          # 모든 환경 변수
echo $PATH                   # PATH 변수
echo $HOME                   # 홈 디렉토리
export VAR=value             # 환경 변수 설정
```

## 모니터링 도구 설치

### 1. htop 설치 (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install htop
```

### 2. iotop 설치
```bash
sudo apt install iotop
```

### 3. sysstat 설치 (iostat 등)
```bash
sudo apt install sysstat
```

## 주의사항

1. **시스템 리소스 모니터링**
   - CPU 사용률이 80% 이상 지속되면 주의
   - 메모리 사용률이 90% 이상이면 스왑 사용 확인
   - 디스크 사용률이 90% 이상이면 정리 필요

2. **프로세스 관리**
   - `kill -9`는 최후의 수단으로만 사용
   - 중요한 프로세스 종료 전에 의존성 확인

3. **로그 파일 관리**
   - 로그 파일이 너무 커지지 않도록 로테이션 설정
   - 중요한 로그는 백업 보관