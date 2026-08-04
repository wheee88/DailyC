# 파일과 디렉토리 조작 명령어

## 기본 명령어들

### 1. 현재 위치 확인
```bash
pwd
```

### 2. 디렉토리 내용 보기
```bash
ls                    # 기본 목록
ls -l                 # 상세 정보
ls -la                # 숨김 파일 포함
ls -lh                # 사람이 읽기 쉬운 크기
ls -lt                # 수정 시간 순 정렬
```

### 3. 디렉토리 이동
```bash
cd /home              # 절대 경로로 이동
cd ..                 # 상위 디렉토리로
cd ~                  # 홈 디렉토리로
cd -                  # 이전 디렉토리로
```

### 4. 디렉토리 생성/삭제
```bash
mkdir test_dir         # 디렉토리 생성
mkdir -p path/to/dir   # 중간 디렉토리까지 생성
rmdir test_dir         # 빈 디렉토리 삭제
rm -rf test_dir        # 디렉토리와 내용 모두 삭제
```

### 5. 파일 생성/복사/이동/삭제
```bash
touch file.txt        # 빈 파일 생성
cp file.txt copy.txt  # 파일 복사
cp -r dir1 dir2       # 디렉토리 복사
mv file.txt newname.txt  # 파일 이름 변경/이동
rm file.txt           # 파일 삭제
rm -i file.txt        # 확인 후 삭제
```

## 실습 예제

### 실습 1: 기본 디렉토리 구조 만들기
```bash
# 홈 디렉토리로 이동
cd ~

# 실습용 디렉토리 생성
mkdir linux_practice
cd linux_practice

# 하위 디렉토리들 생성
mkdir {documents,images,scripts,backup}

# 각 디렉토리에 샘플 파일 생성
touch documents/readme.txt
touch images/photo1.jpg
touch scripts/backup.sh
touch backup/old_file.txt

# 구조 확인
tree .  # tree 명령어가 없다면 ls -R 사용
```

### 실습 2: 파일 조작 연습
```bash
# 현재 디렉토리 확인
pwd

# 파일 목록 보기
ls -la

# 파일 복사
cp documents/readme.txt documents/readme_backup.txt

# 파일 이동
mv images/photo1.jpg backup/

# 파일 이름 변경
mv backup/photo1.jpg backup/vacation_photo.jpg

# 결과 확인
ls -la documents/
ls -la backup/
```

### 실습 3: 와일드카드 사용
```bash
# .txt로 끝나는 모든 파일 보기
ls *.txt

# a로 시작하는 파일들 보기
ls a*

# 확장자가 없는 파일들 보기
ls *.

# 숨김 파일들 보기
ls .*
```

## 유용한 옵션들

### ls 명령어 옵션
- `-a`: 숨김 파일 포함
- `-l`: 상세 정보 표시
- `-h`: 사람이 읽기 쉬운 크기
- `-t`: 수정 시간 순 정렬
- `-r`: 역순 정렬
- `-S`: 크기 순 정렬

### find 명령어 (파일 검색)
```bash
find . -name "*.txt"           # 현재 디렉토리에서 .txt 파일 찾기
find /home -type f -name "*.log"  # /home에서 .log 파일 찾기
find . -size +100M             # 100MB 이상 파일 찾기
find . -mtime -7               # 7일 이내 수정된 파일 찾기
```

## 주의사항

1. **절대 경로 vs 상대 경로**
   - 절대 경로: `/home/user/documents/file.txt`
   - 상대 경로: `../documents/file.txt`

2. **파일 삭제 주의**
   - `rm -rf` 명령어는 되돌릴 수 없습니다
   - 중요한 파일은 `rm -i`로 확인 후 삭제

3. **권한 확인**
   - 파일을 조작하기 전에 권한을 확인하세요
   - `ls -l`로 권한 정보를 확인할 수 있습니다