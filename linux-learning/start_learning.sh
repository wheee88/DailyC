#!/bin/bash

echo "=========================================="
echo "    리눅스 운영 학습 환경 시작하기"
echo "=========================================="
echo

# 색상 정의
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 함수 정의
print_header() {
    echo -e "${BLUE}=== $1 ===${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

# 메인 메뉴
show_menu() {
    echo
    print_header "학습 메뉴"
    echo "1. 기본 명령어 실습"
    echo "2. 파일 시스템 관리 실습"
    echo "3. 프로세스 관리 실습"
    echo "4. 권한 관리 실습"
    echo "5. 쉘 스크립팅 실습"
    echo "6. 전체 실습 실행"
    echo "7. 학습 진도 확인"
    echo "8. 도움말"
    echo "9. 종료"
    echo
}

# 기본 명령어 실습
basic_commands() {
    print_header "기본 명령어 실습"
    echo "실행할 실습을 선택하세요:"
    echo "1. 파일과 디렉토리 조작"
    echo "2. 텍스트 파일 처리"
    echo "3. 시스템 정보 확인"
    echo "4. 모든 기본 명령어 실습"
    echo "5. 돌아가기"
    
    read -p "선택 (1-5): " choice
    
    case $choice in
        1)
            cd basic-commands
            chmod +x *.sh
            ./01-file-operations.md
            ;;
        2)
            cd basic-commands
            chmod +x *.sh
            ./02-text-processing.md
            ;;
        3)
            cd basic-commands
            chmod +x *.sh
            ./03-system-info.md
            ;;
        4)
            cd basic-commands
            chmod +x *.sh
            for script in *.sh; do
                echo "실행 중: $script"
                ./"$script"
                echo
            done
            ;;
        5)
            return
            ;;
        *)
            print_error "잘못된 선택입니다."
            ;;
    esac
}

# 파일 시스템 실습
file_system() {
    print_header "파일 시스템 관리 실습"
    echo "실행할 실습을 선택하세요:"
    echo "1. 파일 시스템 구조"
    echo "2. 마운트와 언마운트"
    echo "3. 모든 파일 시스템 실습"
    echo "4. 돌아가기"
    
    read -p "선택 (1-4): " choice
    
    case $choice in
        1)
            cd file-system
            chmod +x *.sh
            ./01-filesystem-structure.md
            ;;
        2)
            cd file-system
            chmod +x *.sh
            ./02-mount-unmount.md
            ;;
        3)
            cd file-system
            chmod +x *.sh
            for script in *.sh; do
                echo "실행 중: $script"
                ./"$script"
                echo
            done
            ;;
        4)
            return
            ;;
        *)
            print_error "잘못된 선택입니다."
            ;;
    esac
}

# 프로세스 관리 실습
process_management() {
    print_header "프로세스 관리 실습"
    echo "실행할 실습을 선택하세요:"
    echo "1. 프로세스 기초"
    echo "2. 백그라운드 작업 관리"
    echo "3. 모든 프로세스 관리 실습"
    echo "4. 돌아가기"
    
    read -p "선택 (1-4): " choice
    
    case $choice in
        1)
            cd process-management
            chmod +x *.sh
            ./01-process-basics.md
            ;;
        2)
            cd process-management
            chmod +x *.sh
            ./02-background-jobs.md
            ;;
        3)
            cd process-management
            chmod +x *.sh
            for script in *.sh; do
                echo "실행 중: $script"
                ./"$script"
                echo
            done
            ;;
        4)
            return
            ;;
        *)
            print_error "잘못된 선택입니다."
            ;;
    esac
}

# 권한 관리 실습
permissions() {
    print_header "권한 관리 실습"
    echo "실행할 실습을 선택하세요:"
    echo "1. 파일 권한 관리"
    echo "2. 사용자와 그룹 관리"
    echo "3. 모든 권한 관리 실습"
    echo "4. 돌아가기"
    
    read -p "선택 (1-4): " choice
    
    case $choice in
        1)
            cd permissions
            chmod +x *.sh
            ./01-file-permissions.md
            ;;
        2)
            cd permissions
            chmod +x *.sh
            ./02-user-group-management.md
            ;;
        3)
            cd permissions
            chmod +x *.sh
            for script in *.sh; do
                echo "실행 중: $script"
                ./"$script"
                echo
            done
            ;;
        4)
            return
            ;;
        *)
            print_error "잘못된 선택입니다."
            ;;
    esac
}

# 쉘 스크립팅 실습
shell_scripting() {
    print_header "쉘 스크립팅 실습"
    echo "실행할 실습을 선택하세요:"
    echo "1. Bash 스크립팅 기초"
    echo "2. 고급 Bash 스크립팅"
    echo "3. 모든 쉘 스크립팅 실습"
    echo "4. 돌아가기"
    
    read -p "선택 (1-4): " choice
    
    case $choice in
        1)
            cd shell-scripting
            chmod +x *.sh
            ./01-bash-basics.md
            ;;
        2)
            cd shell-scripting
            chmod +x *.sh
            ./02-advanced-scripting.md
            ;;
        3)
            cd shell-scripting
            chmod +x *.sh
            for script in *.sh; do
                echo "실행 중: $script"
                ./"$script"
                echo
            done
            ;;
        4)
            return
            ;;
        *)
            print_error "잘못된 선택입니다."
            ;;
    esac
}

# 전체 실습 실행
run_all() {
    print_header "전체 실습 실행"
    echo "모든 실습을 순서대로 실행합니다."
    echo "계속하시겠습니까? (y/N)"
    read -p "선택: " confirm
    
    if [[ $confirm =~ ^[Yy]$ ]]; then
        echo
        print_header "기본 명령어 실습"
        basic_commands
        
        echo
        print_header "파일 시스템 관리 실습"
        file_system
        
        echo
        print_header "프로세스 관리 실습"
        process_management
        
        echo
        print_header "권한 관리 실습"
        permissions
        
        echo
        print_header "쉘 스크립팅 실습"
        shell_scripting
        
        print_success "모든 실습이 완료되었습니다!"
    else
        print_warning "실습이 취소되었습니다."
    fi
}

# 학습 진도 확인
check_progress() {
    print_header "학습 진도 확인"
    echo
    
    # 디렉토리별 파일 수 확인
    echo "학습 자료 현황:"
    for dir in basic-commands file-system process-management permissions shell-scripting; do
        if [ -d "$dir" ]; then
            file_count=$(find "$dir" -name "*.md" | wc -l)
            script_count=$(find "$dir" -name "*.sh" | wc -l)
            echo "  $dir: $file_count개 문서, $script_count개 스크립트"
        else
            echo "  $dir: 디렉토리 없음"
        fi
    done
    
    echo
    echo "실행 가능한 스크립트:"
    for dir in basic-commands file-system process-management permissions shell-scripting; do
        if [ -d "$dir" ]; then
            echo "  $dir:"
            find "$dir" -name "*.sh" -exec basename {} \; | sed 's/^/    /'
        fi
    done
}

# 도움말
show_help() {
    print_header "도움말"
    echo
    echo "이 학습 환경은 리눅스 운영체제를 체계적으로 학습하기 위해 만들어졌습니다."
    echo
    echo "학습 순서:"
    echo "1. 기본 명령어 - 리눅스의 기본 명령어들을 익힙니다"
    echo "2. 파일 시스템 관리 - 파일과 디렉토리를 관리합니다"
    echo "3. 프로세스 관리 - 실행 중인 프로그램들을 관리합니다"
    echo "4. 권한 관리 - 파일과 사용자 권한을 관리합니다"
    echo "5. 쉘 스크립팅 - 자동화 스크립트를 작성합니다"
    echo
    echo "각 실습은 .md 파일(설명)과 .sh 파일(실행 스크립트)로 구성되어 있습니다."
    echo "실습을 진행하기 전에 .md 파일을 읽어보시기 바랍니다."
    echo
    echo "추가 도움말:"
    echo "- 각 실습 디렉토리의 README.md 파일을 참고하세요"
    echo "- 실습 중 문제가 있으면 스크립트를 직접 실행해보세요"
    echo "- 터미널에서 'man 명령어명'으로 명령어 도움말을 볼 수 있습니다"
}

# 메인 루프
main() {
    # 현재 디렉토리를 linux-learning으로 변경
    cd "$(dirname "$0")"
    
    while true; do
        show_menu
        read -p "선택 (1-9): " choice
        
        case $choice in
            1)
                basic_commands
                ;;
            2)
                file_system
                ;;
            3)
                process_management
                ;;
            4)
                permissions
                ;;
            5)
                shell_scripting
                ;;
            6)
                run_all
                ;;
            7)
                check_progress
                ;;
            8)
                show_help
                ;;
            9)
                print_success "학습을 종료합니다. 수고하셨습니다!"
                exit 0
                ;;
            *)
                print_error "잘못된 선택입니다. 1-9 사이의 숫자를 입력하세요."
                ;;
        esac
        
        echo
        read -p "계속하려면 Enter를 누르세요..."
    done
}

# 스크립트 시작
main