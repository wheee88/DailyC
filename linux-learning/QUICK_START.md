# 리눅스 운영 학습 - 빠른 시작 가이드

## 🚀 시작하기

### 1. 학습 환경 시작
```bash
cd linux-learning
./start_learning.sh
```

### 2. 직접 실습하기
```bash
# 기본 명령어 실습
cd basic-commands
chmod +x *.sh
./variable_practice.sh

# 파일 시스템 실습
cd ../file-system
chmod +x *.sh
./filesystem_info.sh

# 프로세스 관리 실습
cd ../process-management
chmod +x *.sh
./process_info.sh

# 권한 관리 실습
cd ../permissions
chmod +x *.sh
./permission_basics.sh

# 쉘 스크립팅 실습
cd ../shell-scripting
chmod +x *.sh
./variable_practice.sh
```

## 📚 학습 순서

### 1단계: 기본 명령어 (basic-commands/)
- **01-file-operations.md** - 파일과 디렉토리 조작
- **02-text-processing.md** - 텍스트 파일 처리
- **03-system-info.md** - 시스템 정보 확인

### 2단계: 파일 시스템 관리 (file-system/)
- **01-filesystem-structure.md** - 파일 시스템 구조 이해
- **02-mount-unmount.md** - 마운트와 언마운트

### 3단계: 프로세스 관리 (process-management/)
- **01-process-basics.md** - 프로세스 기초
- **02-background-jobs.md** - 백그라운드 작업 관리

### 4단계: 권한 관리 (permissions/)
- **01-file-permissions.md** - 파일 권한 관리
- **02-user-group-management.md** - 사용자와 그룹 관리

### 5단계: 쉘 스크립팅 (shell-scripting/)
- **01-bash-basics.md** - Bash 스크립팅 기초
- **02-advanced-scripting.md** - 고급 Bash 스크립팅

## 🛠️ 실습 방법

### 1. 문서 읽기
각 실습 디렉토리의 `.md` 파일을 먼저 읽어보세요.

### 2. 스크립트 실행
```bash
# 스크립트에 실행 권한 부여
chmod +x script_name.sh

# 스크립트 실행
./script_name.sh
```

### 3. 직접 명령어 실행
문서에 나온 명령어들을 터미널에서 직접 실행해보세요.

## 📋 실습 체크리스트

### 기본 명령어
- [ ] 파일과 디렉토리 생성/삭제/이동
- [ ] 텍스트 파일 읽기/쓰기/검색
- [ ] 시스템 정보 확인
- [ ] 프로세스 모니터링

### 파일 시스템
- [ ] 파일 시스템 구조 이해
- [ ] 마운트/언마운트 실습
- [ ] 디스크 사용량 확인
- [ ] 파일 권한 설정

### 프로세스 관리
- [ ] 프로세스 생성/종료
- [ ] 백그라운드 작업 관리
- [ ] 프로세스 모니터링
- [ ] 작업 제어

### 권한 관리
- [ ] 파일 권한 변경
- [ ] 사용자/그룹 생성
- [ ] 권한 설정
- [ ] sudo 사용

### 쉘 스크립팅
- [ ] 변수 사용
- [ ] 조건문/반복문
- [ ] 함수 정의
- [ ] 에러 처리

## 🔧 문제 해결

### 권한 문제
```bash
# 실행 권한 부여
chmod +x script_name.sh

# sudo 권한 확인
sudo -l
```

### 스크립트 실행 오류
```bash
# 스크립트 문법 확인
bash -n script_name.sh

# 디버그 모드로 실행
bash -x script_name.sh
```

### 파일 찾기
```bash
# 특정 파일 찾기
find . -name "*.sh"

# 실행 가능한 파일 찾기
find . -type f -executable
```

## 📖 추가 학습 자료

### 온라인 자료
- [Linux Command Line and Shell Scripting Bible](https://www.amazon.com/Linux-Command-Shell-Scripting-Bible/dp/111898384X)
- [The Linux Documentation Project](https://tldp.org/)
- [Linux Academy](https://linuxacademy.com/)

### 유용한 명령어
```bash
# 도움말 보기
man command_name
info command_name
command_name --help

# 명령어 검색
apropos keyword
whatis command_name
```

### 실습 팁
1. **단계별 학습**: 한 번에 모든 것을 배우려 하지 말고 단계별로 학습하세요.
2. **직접 실행**: 문서를 읽는 것보다 직접 명령어를 실행해보세요.
3. **오류 분석**: 오류가 발생하면 오류 메시지를 자세히 읽어보세요.
4. **정기적 복습**: 배운 내용을 정기적으로 복습하세요.

## 🎯 학습 목표

이 학습 과정을 완료하면 다음을 할 수 있게 됩니다:

- 리눅스 명령어를 자유자재로 사용
- 파일과 디렉토리를 효율적으로 관리
- 프로세스를 모니터링하고 제어
- 사용자와 권한을 관리
- 자동화 스크립트를 작성

## 💡 다음 단계

기본 학습을 완료한 후에는 다음을 고려해보세요:

- **시스템 관리**: 서버 설정, 네트워크 구성
- **보안**: 방화벽, 암호화, 접근 제어
- **모니터링**: 로그 분석, 성능 모니터링
- **자동화**: 고급 스크립팅, 배치 작업
- **컨테이너**: Docker, Kubernetes

---

**Happy Learning! 🐧**