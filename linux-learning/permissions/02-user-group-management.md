# 사용자와 그룹 관리

## 사용자와 그룹 개념

리눅스는 다중 사용자 시스템으로, 각 사용자는 고유한 사용자 ID(UID)와 그룹 ID(GID)를 가집니다. 파일과 프로세스는 소유자와 그룹을 가지며, 권한은 이에 따라 결정됩니다.

## 사용자 관리

### 1. 사용자 정보 확인
```bash
# 현재 사용자 정보
whoami
id
groups

# 사용자 상세 정보
finger username
getent passwd username

# 로그인한 사용자들
who
w
last
```

### 2. 사용자 생성과 삭제
```bash
# 사용자 생성
sudo useradd username
sudo useradd -m -s /bin/bash username  # 홈 디렉토리와 쉘 지정
sudo useradd -g groupname username     # 기본 그룹 지정
sudo useradd -G group1,group2 username # 추가 그룹 지정

# 사용자 삭제
sudo userdel username
sudo userdel -r username  # 홈 디렉토리도 함께 삭제

# 사용자 정보 수정
sudo usermod -l newname oldname  # 사용자명 변경
sudo usermod -d /new/home username  # 홈 디렉토리 변경
sudo usermod -s /bin/zsh username  # 쉘 변경
```

### 3. 사용자 비밀번호 관리
```bash
# 비밀번호 설정
sudo passwd username

# 비밀번호 만료 설정
sudo passwd -e username  # 다음 로그인 시 비밀번호 변경 강제
sudo passwd -l username  # 계정 잠금
sudo passwd -u username  # 계정 잠금 해제

# 비밀번호 정책 설정
sudo chage -l username  # 비밀번호 정책 확인
sudo chage -M 90 username  # 최대 사용 기간 90일
sudo chage -m 7 username   # 최소 사용 기간 7일
```

## 실습 예제

### 실습 1: 사용자 정보 확인
```bash
# 사용자 정보 확인 실습
cat > user_info.sh << 'EOF'
#!/bin/bash

echo "=== 사용자 정보 확인 실습 ==="
echo

echo "1. 현재 사용자 정보:"
echo "사용자명: $(whoami)"
echo "UID: $(id -u)"
echo "GID: $(id -g)"
echo "그룹: $(groups)"

echo -e "\n2. 상세 사용자 정보:"
id

echo -e "\n3. 사용자 계정 정보:"
getent passwd $(whoami)

echo -e "\n4. 로그인한 사용자들:"
who

echo -e "\n5. 시스템 사용자들:"
echo "UID 1000 이상의 사용자들:"
getent passwd | awk -F: '$3 >= 1000 {print $1, $3, $5}'

echo -e "\n6. 시스템 계정들:"
echo "UID 1000 미만의 사용자들:"
getent passwd | awk -F: '$3 < 1000 {print $1, $3, $5}' | head -10

echo -e "\n7. 사용자별 홈 디렉토리:"
getent passwd | awk -F: '$3 >= 1000 {print $1, $6}'
EOF

chmod +x user_info.sh
./user_info.sh
```

### 실습 2: 사용자 생성 실습
```bash
# 사용자 생성 실습
cat > user_creation.sh << 'EOF'
#!/bin/bash

echo "=== 사용자 생성 실습 ==="
echo

# 테스트 사용자명
TEST_USER="testuser_$(date +%s)"

echo "1. 테스트 사용자 생성: $TEST_USER"
sudo useradd -m -s /bin/bash $TEST_USER
if [ $? -eq 0 ]; then
    echo "사용자 생성 성공"
else
    echo "사용자 생성 실패"
    exit 1
fi

echo -e "\n2. 생성된 사용자 정보 확인:"
id $TEST_USER
getent passwd $TEST_USER

echo -e "\n3. 홈 디렉토리 확인:"
ls -ld /home/$TEST_USER

echo -e "\n4. 사용자 비밀번호 설정:"
echo "$TEST_USER:testpass123" | sudo chpasswd
echo "비밀번호 설정 완료"

echo -e "\n5. 사용자 그룹 확인:"
groups $TEST_USER

echo -e "\n6. 사용자 삭제:"
sudo userdel -r $TEST_USER
if [ $? -eq 0 ]; then
    echo "사용자 삭제 성공"
else
    echo "사용자 삭제 실패"
fi

echo -e "\n7. 삭제 확인:"
id $TEST_USER 2>/dev/null || echo "사용자가 존재하지 않습니다"
EOF

chmod +x user_creation.sh
./user_creation.sh
```

### 실습 3: 사용자 권한 실습
```bash
# 사용자 권한 실습
cat > user_permissions.sh << 'EOF'
#!/bin/bash

echo "=== 사용자 권한 실습 ==="
echo

# 테스트 사용자 생성
TEST_USER="testuser_$(date +%s)"
sudo useradd -m -s /bin/bash $TEST_USER
echo "$TEST_USER:testpass123" | sudo chpasswd

echo "1. 테스트 파일 생성:"
echo "Hello World" > test_file.txt
chmod 644 test_file.txt
echo "파일 생성 및 권한 설정 완료"

echo -e "\n2. 현재 사용자로 파일 접근:"
cat test_file.txt

echo -e "\n3. 파일 소유자 확인:"
ls -l test_file.txt

echo -e "\n4. 파일 소유자 변경:"
sudo chown $TEST_USER test_file.txt
echo "소유자 변경 후:"
ls -l test_file.txt

echo -e "\n5. 다른 사용자로 파일 접근 시도:"
sudo -u $TEST_USER cat test_file.txt

echo -e "\n6. 파일 권한 변경 (읽기 전용):"
chmod 400 test_file.txt
echo "권한 변경 후:"
ls -l test_file.txt

echo -e "\n7. 다른 사용자로 파일 수정 시도:"
sudo -u $TEST_USER sh -c 'echo "Modified" > test_file.txt' 2>&1 || echo "수정 실패 (권한 없음)"

echo -e "\n8. 파일 권한 복원:"
chmod 644 test_file.txt
sudo chown $(whoami) test_file.txt

echo -e "\n9. 정리:"
sudo userdel -r $TEST_USER
rm -f test_file.txt
echo "정리 완료"
EOF

chmod +x user_permissions.sh
./user_permissions.sh
```

## 그룹 관리

### 1. 그룹 정보 확인
```bash
# 현재 사용자의 그룹
groups
id -Gn

# 그룹 상세 정보
getent group groupname

# 모든 그룹 목록
getent group

# 그룹 멤버 확인
getent group groupname | cut -d: -f4
```

### 2. 그룹 생성과 삭제
```bash
# 그룹 생성
sudo groupadd groupname
sudo groupadd -g 1001 groupname  # GID 지정

# 그룹 삭제
sudo groupdel groupname

# 그룹 정보 수정
sudo groupmod -n newname oldname  # 그룹명 변경
sudo groupmod -g 1002 groupname  # GID 변경
```

### 3. 그룹 멤버 관리
```bash
# 그룹에 사용자 추가
sudo usermod -a -G groupname username
sudo gpasswd -a username groupname

# 그룹에서 사용자 제거
sudo gpasswd -d username groupname

# 그룹 관리자 설정
sudo gpasswd -A username groupname  # 그룹 관리자 설정
sudo gpasswd -M user1,user2 groupname  # 그룹 멤버 설정
```

## 실습 예제

### 실습 4: 그룹 관리 실습
```bash
# 그룹 관리 실습
cat > group_management.sh << 'EOF'
#!/bin/bash

echo "=== 그룹 관리 실습 ==="
echo

# 테스트 그룹명
TEST_GROUP="testgroup_$(date +%s)"
TEST_USER="testuser_$(date +%s)"

echo "1. 테스트 그룹 생성: $TEST_GROUP"
sudo groupadd $TEST_GROUP
if [ $? -eq 0 ]; then
    echo "그룹 생성 성공"
else
    echo "그룹 생성 실패"
    exit 1
fi

echo -e "\n2. 생성된 그룹 정보 확인:"
getent group $TEST_GROUP

echo -e "\n3. 테스트 사용자 생성: $TEST_USER"
sudo useradd -m -s /bin/bash $TEST_USER
echo "$TEST_USER:testpass123" | sudo chpasswd

echo -e "\n4. 사용자를 그룹에 추가:"
sudo usermod -a -G $TEST_GROUP $TEST_USER
echo "사용자 그룹 추가 완료"

echo -e "\n5. 사용자 그룹 확인:"
groups $TEST_USER

echo -e "\n6. 그룹 멤버 확인:"
getent group $TEST_GROUP | cut -d: -f4

echo -e "\n7. 그룹 권한 테스트:"
# 그룹 소유 파일 생성
sudo -u $TEST_USER touch /home/$TEST_USER/group_file.txt
sudo chgrp $TEST_GROUP /home/$TEST_USER/group_file.txt
sudo chmod 664 /home/$TEST_USER/group_file.txt

echo "그룹 소유 파일 생성:"
ls -l /home/$TEST_USER/group_file.txt

echo -e "\n8. 그룹에서 사용자 제거:"
sudo gpasswd -d $TEST_USER $TEST_GROUP
echo "사용자 그룹 제거 완료"

echo -e "\n9. 정리:"
sudo userdel -r $TEST_USER
sudo groupdel $TEST_GROUP
echo "정리 완료"
EOF

chmod +x group_management.sh
./group_management.sh
```

### 실습 5: 그룹 권한 실습
```bash
# 그룹 권한 실습
cat > group_permissions.sh << 'EOF'
#!/bin/bash

echo "=== 그룹 권한 실습 ==="
echo

# 테스트 그룹과 사용자 생성
TEST_GROUP="testgroup_$(date +%s)"
TEST_USER1="testuser1_$(date +%s)"
TEST_USER2="testuser2_$(date +%s)"

sudo groupadd $TEST_GROUP
sudo useradd -m -s /bin/bash $TEST_USER1
sudo useradd -m -s /bin/bash $TEST_USER2
echo "$TEST_USER1:testpass123" | sudo chpasswd
echo "$TEST_USER2:testpass123" | sudo chpasswd

# 사용자들을 그룹에 추가
sudo usermod -a -G $TEST_GROUP $TEST_USER1
sudo usermod -a -G $TEST_GROUP $TEST_USER2

echo "1. 테스트 환경 설정 완료:"
echo "그룹: $TEST_GROUP"
echo "사용자1: $TEST_USER1"
echo "사용자2: $TEST_USER2"

echo -e "\n2. 그룹 소유 파일 생성:"
sudo -u $TEST_USER1 touch /home/$TEST_USER1/shared_file.txt
sudo chgrp $TEST_GROUP /home/$TEST_USER1/shared_file.txt
sudo chmod 664 /home/$TEST_USER1/shared_file.txt

echo "파일 생성 및 권한 설정:"
ls -l /home/$TEST_USER1/shared_file.txt

echo -e "\n3. 사용자1로 파일 수정:"
sudo -u $TEST_USER1 sh -c 'echo "User1 content" > /home/$TEST_USER1/shared_file.txt'
echo "사용자1 파일 수정 완료"

echo -e "\n4. 사용자2로 파일 접근:"
sudo -u $TEST_USER2 cat /home/$TEST_USER1/shared_file.txt

echo -e "\n5. 사용자2로 파일 수정:"
sudo -u $TEST_USER2 sh -c 'echo "User2 content" >> /home/$TEST_USER1/shared_file.txt'
echo "사용자2 파일 수정 완료"

echo -e "\n6. 최종 파일 내용:"
cat /home/$TEST_USER1/shared_file.txt

echo -e "\n7. 그룹 권한 변경 (읽기 전용):"
sudo chmod 644 /home/$TEST_USER1/shared_file.txt
echo "권한 변경 후:"
ls -l /home/$TEST_USER1/shared_file.txt

echo -e "\n8. 사용자2로 파일 수정 시도:"
sudo -u $TEST_USER2 sh -c 'echo "User2 content 2" >> /home/$TEST_USER1/shared_file.txt' 2>&1 || echo "수정 실패 (권한 없음)"

echo -e "\n9. 정리:"
sudo userdel -r $TEST_USER1
sudo userdel -r $TEST_USER2
sudo groupdel $TEST_GROUP
echo "정리 완료"
EOF

chmod +x group_permissions.sh
./group_permissions.sh
```

## sudo 권한 관리

### 1. sudo 설정
```bash
# sudo 설정 파일
sudo visudo

# 사용자에게 sudo 권한 부여
sudo usermod -a -G sudo username

# sudo 권한 확인
sudo -l

# sudo 그룹 확인
getent group sudo
```

### 2. sudo 실습
```bash
# sudo 실습
cat > sudo_practice.sh << 'EOF'
#!/bin/bash

echo "=== sudo 실습 ==="
echo

echo "1. 현재 사용자의 sudo 권한 확인:"
sudo -l

echo -e "\n2. sudo 그룹 멤버 확인:"
getent group sudo | cut -d: -f4

echo -e "\n3. sudo 명령어 실행:"
echo "시스템 정보 확인:"
sudo whoami
sudo id

echo -e "\n4. sudo 환경 변수:"
sudo env | grep -E "(USER|HOME|PATH)"

echo -e "\n5. sudo 로그 확인:"
echo "sudo 명령어 실행 로그:"
sudo grep "sudo" /var/log/auth.log 2>/dev/null | tail -5 || echo "로그 파일 접근 불가"

echo -e "\n6. sudo 설정 파일 확인:"
echo "sudoers 파일 위치:"
ls -l /etc/sudoers

echo -e "\n7. sudo 그룹 권한 확인:"
sudo -l -U $(whoami)
EOF

chmod +x sudo_practice.sh
./sudo_practice.sh
```

## 사용자 세션 관리

### 1. 세션 정보 확인
```bash
# 로그인한 사용자들
who
w
last

# 현재 세션 정보
echo $SSH_CLIENT
echo $SSH_CONNECTION

# 사용자별 프로세스
ps -u username
```

### 2. 세션 관리 실습
```bash
# 세션 관리 실습
cat > session_management.sh << 'EOF'
#!/bin/bash

echo "=== 세션 관리 실습 ==="
echo

echo "1. 현재 로그인한 사용자들:"
who

echo -e "\n2. 상세 사용자 정보:"
w

echo -e "\n3. 최근 로그인 기록:"
last | head -10

echo -e "\n4. 현재 사용자 세션 정보:"
echo "사용자: $(whoami)"
echo "터미널: $(tty)"
echo "로그인 시간: $(who am i | awk '{print $3, $4}')"

echo -e "\n5. SSH 연결 정보:"
if [ -n "$SSH_CLIENT" ]; then
    echo "SSH 클라이언트: $SSH_CLIENT"
    echo "SSH 연결: $SSH_CONNECTION"
else
    echo "로컬 세션"
fi

echo -e "\n6. 사용자별 프로세스 수:"
ps aux | awk '{print $1}' | sort | uniq -c | sort -nr | head -10

echo -e "\n7. 현재 사용자 프로세스:"
ps -u $(whoami) | wc -l
echo "현재 사용자 프로세스 수: $(ps -u $(whoami) | wc -l)"
EOF

chmod +x session_management.sh
./session_management.sh
```

## 유용한 명령어들

### 1. 사용자 관리 명령어
```bash
# 사용자 정보
whoami, id, groups, finger

# 사용자 관리
useradd, userdel, usermod, passwd

# 그룹 관리
groupadd, groupdel, groupmod, gpasswd

# 권한 관리
chown, chgrp, chmod
```

### 2. 세션 관리 명령어
```bash
# 세션 정보
who, w, last, lastlog

# 프로세스 관리
ps, top, htop

# 권한 확인
sudo -l, su
```

## 주의사항

1. **사용자 생성 시 주의**
   - 홈 디렉토리와 쉘 설정 확인
   - 적절한 기본 그룹 지정

2. **그룹 관리**
   - 그룹 멤버십 변경 시 사용자 재로그인 필요
   - 그룹 권한 설정 시 보안 고려

3. **sudo 권한**
   - 최소 권한 원칙 적용
   - 정기적인 sudo 권한 검토

4. **비밀번호 정책**
   - 강력한 비밀번호 정책 설정
   - 정기적인 비밀번호 변경

5. **보안 고려사항**
   - 사용하지 않는 계정 정리
   - 로그인 실패 모니터링
   - 권한 상승 시도 모니터링