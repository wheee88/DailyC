# 마운트와 언마운트

## 마운트 개념

리눅스에서 마운트(mount)는 파일 시스템을 특정 디렉토리에 연결하는 과정입니다. 모든 파일 시스템은 마운트되어야 사용할 수 있습니다.

## 기본 마운트 명령어

### 1. 마운트 정보 확인
```bash
# 마운트된 파일 시스템 목록
mount

# 특정 형식으로 출력
mount | column -t

# /proc/mounts 파일 확인
cat /proc/mounts

# 마운트 포인트만 확인
findmnt
```

### 2. 기본 마운트 명령어
```bash
# 기본 마운트 (자동 감지)
sudo mount /dev/sda1 /mnt

# 파일 시스템 타입 지정
sudo mount -t ext4 /dev/sda1 /mnt

# 읽기 전용 마운트
sudo mount -o ro /dev/sda1 /mnt

# 옵션과 함께 마운트
sudo mount -o rw,noexec,nosuid /dev/sda1 /mnt
```

### 3. 언마운트 명령어
```bash
# 디바이스로 언마운트
sudo umount /dev/sda1

# 마운트 포인트로 언마운트
sudo umount /mnt

# 강제 언마운트
sudo umount -f /mnt

# 지연 언마운트 (사용 중인 파일이 있으면 대기)
sudo umount -l /mnt
```

## 실습 예제

### 실습 1: 마운트 정보 분석
```bash
# 마운트 정보 분석 스크립트
cat > mount_analysis.sh << 'EOF'
#!/bin/bash

echo "=== 마운트 정보 분석 ==="
echo

echo "1. 전체 마운트 정보:"
mount | wc -l
echo "총 $(mount | wc -l)개의 마운트된 파일 시스템"

echo -e "\n2. 파일 시스템 타입별 분류:"
mount | awk '{print $5}' | sort | uniq -c | sort -nr

echo -e "\n3. 디스크 사용량:"
df -h

echo -e "\n4. inode 사용량:"
df -i

echo -e "\n5. 특별한 마운트 포인트들:"
echo "가상 파일 시스템:"
mount | grep -E "(tmpfs|proc|sysfs|devpts|devtmpfs)"

echo -e "\n네트워크 파일 시스템:"
mount | grep -E "(nfs|cifs|fuse)"

echo -e "\n6. 마운트 옵션 분석:"
mount | awk '{for(i=6;i<=NF;i++) print $i}' | sort | uniq -c | sort -nr
EOF

chmod +x mount_analysis.sh
./mount_analysis.sh
```

### 실습 2: USB 디바이스 마운트
```bash
# USB 디바이스 마운트 실습
cat > usb_mount_practice.sh << 'EOF'
#!/bin/bash

echo "=== USB 디바이스 마운트 실습 ==="
echo

echo "1. 현재 연결된 USB 디바이스 확인:"
lsblk | grep -E "(sd|usb)"

echo -e "\n2. 사용 가능한 블록 디바이스:"
lsblk

echo -e "\n3. 마운트 포인트 생성:"
sudo mkdir -p /mnt/usb_test
echo "마운트 포인트 생성: /mnt/usb_test"

echo -e "\n4. 마운트 가능한 파일 시스템 확인:"
sudo blkid

echo -e "\n5. 마운트 예제 (실제 디바이스가 있을 때):"
echo "# USB 디바이스 마운트 예제:"
echo "# sudo mount /dev/sdb1 /mnt/usb_test"
echo "# 마운트 후 확인:"
echo "# ls -la /mnt/usb_test"
echo "# 언마운트:"
echo "# sudo umount /mnt/usb_test"

# 정리
sudo rmdir /mnt/usb_test 2>/dev/null
echo -e "\n마운트 포인트 정리 완료"
EOF

chmod +x usb_mount_practice.sh
./usb_mount_practice.sh
```

### 실습 3: 임시 파일 시스템 마운트
```bash
# tmpfs 마운트 실습
cat > tmpfs_practice.sh << 'EOF'
#!/bin/bash

echo "=== tmpfs 마운트 실습 ==="
echo

echo "1. tmpfs 마운트 포인트 생성:"
sudo mkdir -p /mnt/tmpfs_test
echo "마운트 포인트 생성: /mnt/tmpfs_test"

echo -e "\n2. tmpfs 마운트 (100MB 제한):"
sudo mount -t tmpfs -o size=100M tmpfs /mnt/tmpfs_test
echo "tmpfs 마운트 완료"

echo -e "\n3. 마운트 확인:"
mount | grep tmpfs

echo -e "\n4. 디스크 사용량 확인:"
df -h | grep tmpfs

echo -e "\n5. 테스트 파일 생성:"
echo "Hello tmpfs" > /mnt/tmpfs_test/test.txt
ls -la /mnt/tmpfs_test/

echo -e "\n6. 파일 내용 확인:"
cat /mnt/tmpfs_test/test.txt

echo -e "\n7. tmpfs 언마운트:"
sudo umount /mnt/tmpfs_test
echo "tmpfs 언마운트 완료"

echo -e "\n8. 마운트 포인트 정리:"
sudo rmdir /mnt/tmpfs_test
echo "마운트 포인트 정리 완료"
EOF

chmod +x tmpfs_practice.sh
./tmpfs_practice.sh
```

## /etc/fstab 파일 관리

### 1. fstab 파일 이해
```bash
# fstab 파일 내용 확인
cat /etc/fstab

# fstab 파일 형식 설명
cat > fstab_explanation.sh << 'EOF'
#!/bin/bash

echo "=== /etc/fstab 파일 분석 ==="
echo

echo "fstab 파일 형식:"
echo "디바이스명 마운트포인트 파일시스템타입 옵션 dump pass"
echo

echo "현재 fstab 내용:"
cat /etc/fstab | grep -v '^#' | grep -v '^$'

echo -e "\n각 필드 설명:"
echo "1. 디바이스명: /dev/sda1 또는 UUID"
echo "2. 마운트포인트: /, /home, /var 등"
echo "3. 파일시스템타입: ext4, xfs, tmpfs 등"
echo "4. 옵션: defaults, ro, rw, noexec 등"
echo "5. dump: 백업용 (0 또는 1)"
echo "6. pass: 파일시스템 체크 순서 (0, 1, 2)"
EOF

chmod +x fstab_explanation.sh
./fstab_explanation.sh
```

### 2. fstab 실습
```bash
# fstab 실습 스크립트
cat > fstab_practice.sh << 'EOF'
#!/bin/bash

echo "=== fstab 실습 ==="
echo

echo "1. 현재 fstab 백업:"
sudo cp /etc/fstab /etc/fstab.backup
echo "fstab 백업 완료: /etc/fstab.backup"

echo -e "\n2. 현재 마운트된 파일 시스템들:"
df -h

echo -e "\n3. UUID 확인:"
sudo blkid

echo -e "\n4. fstab에 추가할 수 있는 예제:"
echo "# USB 디바이스 자동 마운트 예제:"
echo "# UUID=12345678-1234-1234-1234-123456789abc /mnt/usb ext4 defaults,user,noauto 0 0"
echo "# noauto: 자동 마운트 안함"
echo "# user: 일반 사용자도 마운트 가능"

echo -e "\n5. 마운트 테스트:"
echo "fstab 파일의 항목을 테스트하려면:"
echo "sudo mount -a"

echo -e "\n6. 특정 항목만 마운트:"
echo "sudo mount /mnt/usb"
EOF

chmod +x fstab_practice.sh
./fstab_practice.sh
```

## 네트워크 파일 시스템

### 1. NFS 마운트
```bash
# NFS 마운트 실습
cat > nfs_practice.sh << 'EOF'
#!/bin/bash

echo "=== NFS 마운트 실습 ==="
echo

echo "1. NFS 클라이언트 도구 설치:"
echo "sudo apt update"
echo "sudo apt install nfs-common"

echo -e "\n2. NFS 서버 확인:"
echo "showmount -e nfs_server_ip"

echo -e "\n3. NFS 마운트:"
echo "sudo mkdir -p /mnt/nfs_share"
echo "sudo mount -t nfs nfs_server_ip:/path/to/share /mnt/nfs_share"

echo -e "\n4. NFS 마운트 옵션:"
echo "-o rw: 읽기/쓰기"
echo "-o ro: 읽기 전용"
echo "-o hard: 하드 마운트 (네트워크 문제 시 대기)"
echo "-o soft: 소프트 마운트 (네트워크 문제 시 에러)"
echo "-o intr: 인터럽트 가능"

echo -e "\n5. NFS 언마운트:"
echo "sudo umount /mnt/nfs_share"
EOF

chmod +x nfs_practice.sh
./nfs_practice.sh
```

### 2. CIFS/SMB 마운트
```bash
# CIFS 마운트 실습
cat > cifs_practice.sh << 'EOF'
#!/bin/bash

echo "=== CIFS/SMB 마운트 실습 ==="
echo

echo "1. CIFS 도구 설치:"
echo "sudo apt update"
echo "sudo apt install cifs-utils"

echo -e "\n2. CIFS 마운트:"
echo "sudo mkdir -p /mnt/smb_share"
echo "sudo mount -t cifs //server_ip/share_name /mnt/smb_share -o username=user,password=pass"

echo -e "\n3. 자격증명 파일 사용:"
echo "echo 'username=user' > ~/.smbcredentials"
echo "echo 'password=pass' >> ~/.smbcredentials"
echo "chmod 600 ~/.smbcredentials"
echo "sudo mount -t cifs //server_ip/share_name /mnt/smb_share -o credentials=~/.smbcredentials"

echo -e "\n4. CIFS 언마운트:"
echo "sudo umount /mnt/smb_share"
EOF

chmod +x cifs_practice.sh
./cifs_practice.sh
```

## 마운트 옵션들

### 1. 주요 마운트 옵션
```bash
# 마운트 옵션 설명
cat > mount_options.sh << 'EOF'
#!/bin/bash

echo "=== 마운트 옵션 설명 ==="
echo

echo "기본 옵션들:"
echo "rw        : 읽기/쓰기 (기본값)"
echo "ro        : 읽기 전용"
echo "noexec    : 실행 파일 실행 금지"
echo "nosuid    : SUID 비트 무시"
echo "nodev     : 디바이스 파일 무시"
echo "noatime   : 접근 시간 업데이트 안함"
echo "nodiratime: 디렉토리 접근 시간 업데이트 안함"
echo "relatime  : 상대적 접근 시간 (기본값)"
echo "sync      : 동기식 쓰기"
echo "async     : 비동기식 쓰기 (기본값)"
echo "user      : 일반 사용자 마운트 허용"
echo "users     : 여러 사용자 마운트 허용"
echo "owner     : 소유자만 마운트 허용"
echo "noauto    : 자동 마운트 안함"
echo "defaults  : 기본 옵션들 사용"

echo -e "\n보안 옵션들:"
echo "noexec    : 실행 파일 실행 금지"
echo "nosuid    : SUID/SGID 비트 무시"
echo "nodev     : 디바이스 파일 무시"
echo "noatime   : 접근 시간 업데이트 안함"

echo -e "\n성능 옵션들:"
echo "noatime   : 접근 시간 업데이트 안함"
echo "nodiratime: 디렉토리 접근 시간 업데이트 안함"
echo "relatime  : 상대적 접근 시간"
echo "sync      : 동기식 쓰기"
echo "async     : 비동기식 쓰기"
EOF

chmod +x mount_options.sh
./mount_options.sh
```

## 마운트 문제 해결

### 1. 마운트 문제 진단
```bash
# 마운트 문제 해결 스크립트
cat > mount_troubleshoot.sh << 'EOF'
#!/bin/bash

echo "=== 마운트 문제 해결 ==="
echo

echo "1. 마운트 상태 확인:"
mount | grep -E "(error|failed|busy)"

echo -e "\n2. 사용 중인 마운트 포인트 확인:"
lsof +D /mnt 2>/dev/null || echo "lsof 명령어가 없습니다"

echo -e "\n3. 마운트된 파일 시스템 확인:"
df -h

echo -e "\n4. 블록 디바이스 상태 확인:"
lsblk

echo -e "\n5. 파일 시스템 체크:"
echo "sudo fsck /dev/sda1"

echo -e "\n6. 강제 언마운트:"
echo "sudo umount -f /mnt"
echo "sudo umount -l /mnt  # 지연 언마운트"

echo -e "\n7. 마운트 로그 확인:"
echo "sudo dmesg | grep -i mount"
echo "sudo journalctl | grep -i mount"
EOF

chmod +x mount_troubleshoot.sh
./mount_troubleshoot.sh
```

## 자동 마운트 설정

### 1. systemd 자동 마운트
```bash
# systemd 자동 마운트 설정
cat > auto_mount_setup.sh << 'EOF'
#!/bin/bash

echo "=== systemd 자동 마운트 설정 ==="
echo

echo "1. 마운트 유닛 파일 생성 예제:"
echo "sudo systemctl edit --full mnt-usb.mount"
echo
echo "[Unit]"
echo "Description=USB Drive"
echo "What=/dev/sdb1"
echo "Where=/mnt/usb"
echo "Type=ext4"
echo "Options=defaults,user,noauto"
echo
echo "[Install]"
echo "WantedBy=multi-user.target"

echo -e "\n2. 마운트 유닛 활성화:"
echo "sudo systemctl enable mnt-usb.mount"

echo -e "\n3. 마운트 유닛 시작:"
echo "sudo systemctl start mnt-usb.mount"

echo -e "\n4. 마운트 유닛 상태 확인:"
echo "sudo systemctl status mnt-usb.mount"
EOF

chmod +x auto_mount_setup.sh
./auto_mount_setup.sh
```

## 유용한 명령어들

### 1. 마운트 관련 명령어
```bash
# 마운트 정보 확인
mount
findmnt
df -h

# 블록 디바이스 정보
lsblk
blkid
fdisk -l

# 파일 시스템 체크
fsck
e2fsck
xfs_repair
```

### 2. 마운트 모니터링
```bash
# 마운트 이벤트 모니터링
sudo dmesg -w | grep -i mount

# 시스템 로그에서 마운트 정보
sudo journalctl -f | grep -i mount
```

## 주의사항

1. **마운트 포인트 준비**
   - 마운트하기 전에 디렉토리가 존재하는지 확인
   - 적절한 권한 설정

2. **언마운트 주의**
   - 사용 중인 파일이 있으면 언마운트 실패
   - `lsof` 명령어로 사용 중인 프로세스 확인

3. **fstab 파일 백업**
   - fstab 수정 전에 반드시 백업
   - 잘못된 설정으로 부팅 실패 가능

4. **네트워크 파일 시스템**
   - 네트워크 연결 상태 확인
   - 적절한 타임아웃 설정

5. **보안 고려사항**
   - 불필요한 실행 권한 제거 (`noexec`)
   - SUID 비트 비활성화 (`nosuid`)
   - 디바이스 파일 제한 (`nodev`)