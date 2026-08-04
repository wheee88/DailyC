CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2

PROGRAMS = split_bill_calculator unit_price_comparator trip_fuel_calculator \
	discount_calculator date_difference_calculator time_calculator_v2 \
	recipe_scaler budget_calculator unit_converter

.PHONY: all clean test test-split-bill test-unit-price test-trip-fuel \
	test-discount test-date-difference test-time-calculator test-recipe-scaler \
	test-budget test-unit-converter

all: $(PROGRAMS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test: test-split-bill test-unit-price test-trip-fuel test-discount \
	test-date-difference test-time-calculator test-recipe-scaler test-budget \
	test-unit-converter
	@echo 'All tests passed.'

test-split-bill: split_bill_calculator
	@set -e; \
		output=$$(printf '57300\n4\n100\n' | ./split_bill_calculator); \
		echo "$$output" | grep -q '총무 외 3명 송금액: 14,300원'; \
		echo "$$output" | grep -q '총무 최종 부담액: 14,400원'
	@output=$$(printf '40000\n4\n1\n' | ./split_bill_calculator); \
		echo "$$output" | grep -q '모든 사람이 같은 금액을 부담합니다.'
	@if printf '10000\n0\n100\n' | ./split_bill_calculator >/dev/null 2>&1; then \
		echo 'Invalid people count was accepted.' >&2; \
		exit 1; \
	fi
	@output=$$(printf '8000\n1\n100\n' | ./split_bill_calculator); \
		echo "$$output" | grep -q '혼자 결제한 금액입니다.'

test-unit-price: unit_price_comparator
	@set -e; \
		output=$$(printf '10000\n1000\n7800\n600\n' | ./unit_price_comparator); \
		echo "$$output" | grep -q '상품 A 단위가격: 10.00원'; \
		echo "$$output" | grep -q '상품 A가 단위가격 기준 23.08% 저렴합니다.'
	@output=$$(printf '5000\n500\n10000\n1000\n' | ./unit_price_comparator); \
		echo "$$output" | grep -q '두 상품의 단위가격이 같습니다.'
	@output=$$(printf '9000\n600\n10000\n1000\n' | ./unit_price_comparator); \
		echo "$$output" | grep -q '상품 B가 단위가격 기준 33.33% 저렴합니다.'
	@if printf '5000\n0\n10000\n1000\n' | ./unit_price_comparator >/dev/null 2>&1; then \
		echo 'Invalid quantity was accepted.' >&2; \
		exit 1; \
	fi

test-trip-fuel: trip_fuel_calculator
	@set -e; \
		output=$$(printf '300\n15\n1700\n4\n' | ./trip_fuel_calculator); \
		echo "$$output" | grep -q '필요 연료: 20.00L'; \
		echo "$$output" | grep -q '총 예상 연료비: 34000원'; \
		echo "$$output" | grep -q '1인당 예상 비용: 8500원'
	@output=$$(printf '120.5\n12.5\n1650\n1\n' | ./trip_fuel_calculator); \
		echo "$$output" | grep -q '필요 연료: 9.64L'; \
		echo "$$output" | grep -q '1인당 예상 비용: 15906원'
	@if printf '300\n0\n1700\n4\n' | ./trip_fuel_calculator >/dev/null 2>&1; then \
		echo 'Invalid fuel efficiency was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '300\n15\n1700\n2.5\n' | ./trip_fuel_calculator >/dev/null 2>&1; then \
		echo 'Fractional people count was accepted.' >&2; \
		exit 1; \
	fi

test-discount: discount_calculator
	@set -e; \
		output=$$(printf '20000\n15\n5\n' | ./discount_calculator); \
		echo "$$output" | grep -q '할인 전 총액: 100000원'; \
		echo "$$output" | grep -q '총 할인 금액: 15000원'; \
		echo "$$output" | grep -q '할인 후 개당 가격: 17000원'; \
		echo "$$output" | grep -q '최종 결제 금액: 85000원'
	@output=$$(printf '12345\n0\n2\n' | ./discount_calculator); \
		echo "$$output" | grep -q '총 할인 금액: 0원'; \
		echo "$$output" | grep -q '최종 결제 금액: 24690원'
	@output=$$(printf '12345\n100\n2\n' | ./discount_calculator); \
		echo "$$output" | grep -q '최종 결제 금액: 0원'
	@output=$$(printf '10000\n12.5\n2\n' | ./discount_calculator); \
		echo "$$output" | grep -q '총 할인 금액: 2500원'; \
		echo "$$output" | grep -q '할인 후 개당 가격: 8750원'; \
		echo "$$output" | grep -q '최종 결제 금액: 17500원'
	@if printf '10000\n100.1\n1\n' | ./discount_calculator >/dev/null 2>&1; then \
		echo 'Out-of-range discount rate was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '10000\n10\n1.5\n' | ./discount_calculator >/dev/null 2>&1; then \
		echo 'Fractional quantity was accepted.' >&2; \
		exit 1; \
	fi

test-date-difference: date_difference_calculator
	@set -e; \
		output=$$(printf '2024-02-28\n2024-03-01\n' | ./date_difference_calculator); \
		echo "$$output" | grep -q '두 날짜의 차이: 2일'; \
		echo "$$output" | grep -q '시작일과 종료일을 모두 포함한 기간: 3일'; \
		echo "$$output" | grep -q '종료 날짜가 시작 날짜보다 2일 뒤입니다.'
	@output=$$(printf '2026-09-15\n2026-08-04\n' | ./date_difference_calculator); \
		echo "$$output" | grep -q '종료 날짜가 시작 날짜보다 42일 앞입니다.'
	@output=$$(printf '2026-08-04\n2026-08-04\n' | ./date_difference_calculator); \
		echo "$$output" | grep -q '두 날짜의 차이: 0일'; \
		echo "$$output" | grep -q '시작 날짜와 종료 날짜가 같습니다.'
	@if printf '2023-02-29\n2023-03-01\n' | ./date_difference_calculator >/dev/null 2>&1; then \
		echo 'Invalid leap date was accepted.' >&2; \
		exit 1; \
	fi
	@output=$$(printf '2000-02-28\n2000-03-01\n' | ./date_difference_calculator); \
		echo "$$output" | grep -q '두 날짜의 차이: 2일'
	@if printf '1900-02-29\n1900-03-01\n' | ./date_difference_calculator >/dev/null 2>&1; then \
		echo 'Invalid century leap date was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '2026-8-04\n2026-09-01\n' | ./date_difference_calculator >/dev/null 2>&1; then \
		echo 'Malformed date was accepted.' >&2; \
		exit 1; \
	fi

test-time-calculator: time_calculator_v2
	@output=$$(printf '1\n23 30\n1 00\n0\n' | ./time_calculator_v2); \
		echo "$$output" | grep -q '두 시간의 차이: 1시간 30분'
	@output=$$(printf '1\n8 15\n8 15\n0\n' | ./time_calculator_v2); \
		echo "$$output" | grep -q '두 시간의 차이: 0시간 0분'
	@output=$$(printf '2\n23 30\n26 45\n0\n' | ./time_calculator_v2); \
		echo "$$output" | grep -q '더한 결과: 02:15'
	@output=$$(printf '3\n1 00\n26 30\n0\n' | ./time_calculator_v2); \
		echo "$$output" | grep -q '뺀 결과: 22:30'
	@output=$$(printf '1\n24 00\n0\n' | ./time_calculator_v2 2>&1); \
		echo "$$output" | grep -q '시간은 0~23시, 0~59분 범위로 입력하세요.'
	@output=$$(printf 'wrong\n0\n' | ./time_calculator_v2 2>&1); \
		echo "$$output" | grep -q '메뉴 번호는 정수로 입력하세요.'
	@output=$$(printf '2\n10 00\n-1 30\n0\n' | ./time_calculator_v2 2>&1); \
		echo "$$output" | grep -q '기준 시간 또는 기간의 범위를 확인하세요.'

test-recipe-scaler: recipe_scaler
	@set -e; \
		output=$$(printf '2\n5\n2\n쌀\n300\ng\n양념 물\n200\nml\n' | ./recipe_scaler); \
		echo "$$output" | grep -q '배율: 2.50배'; \
		echo "$$output" | grep -q '쌀: 750.00 g'; \
		echo "$$output" | grep -q '양념 물: 500.00 ml'
	@output=$$(printf '2.5\n3\n1\n달걀\n2.5\n개\n' | ./recipe_scaler); \
		echo "$$output" | grep -q '배율: 1.20배'; \
		echo "$$output" | grep -q '달걀: 3.00 개'
	@if printf '0\n4\n1\n쌀\n100\ng\n' | ./recipe_scaler >/dev/null 2>&1; then \
		echo 'Invalid original servings were accepted.' >&2; \
		exit 1; \
	fi
	@if printf '2\n4\n21\n' | ./recipe_scaler >/dev/null 2>&1; then \
		echo 'Too many ingredients were accepted.' >&2; \
		exit 1; \
	fi
	@if printf '2\n4\n1\n\n100\ng\n' | ./recipe_scaler >/dev/null 2>&1; then \
		echo 'Empty ingredient name was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '2\n4\n1\n쌀\n0\ng\n' | ./recipe_scaler >/dev/null 2>&1; then \
		echo 'Invalid ingredient quantity was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '2\n4\n1\nabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl\n100\ng\n' | ./recipe_scaler >/dev/null 2>&1; then \
		echo 'Overlong ingredient name was accepted.' >&2; \
		exit 1; \
	fi

test-budget: budget_calculator
	@set -e; \
		output=$$(printf '3000000\n3\n주거비\n1200000\n식비\n450000\n교통비\n200000\n' | ./budget_calculator); \
		echo "$$output" | grep -q '총 수입: 3000000원'; \
		echo "$$output" | grep -q -- '- 주거비: 1200000원'; \
		echo "$$output" | grep -q '총 지출: 1850000원'; \
		echo "$$output" | grep -q '잔액: 1150000원'; \
		echo "$$output" | grep -q '저축률: 38.33%'
	@output=$$(printf '100000\n2\n식비\n70000\n쇼핑\n50000\n' | ./budget_calculator); \
		echo "$$output" | grep -q '예산 초과액: 20000원'; \
		echo "$$output" | grep -q '예산 초과율: 20.00%'
	@output=$$(printf '50000\n0\n' | ./budget_calculator); \
		echo "$$output" | grep -q '총 지출: 0원'; \
		echo "$$output" | grep -q '저축률: 100.00%'
	@if printf '100000\n21\n' | ./budget_calculator >/dev/null 2>&1; then \
		echo 'Too many expense items were accepted.' >&2; \
		exit 1; \
	fi
	@if printf '100000\n1\n식비\n-1\n' | ./budget_calculator >/dev/null 2>&1; then \
		echo 'Negative expense was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '100000\n1\n\n1000\n' | ./budget_calculator >/dev/null 2>&1; then \
		echo 'Empty expense name was accepted.' >&2; \
		exit 1; \
	fi

test-unit-converter: unit_converter
	@output=$$(printf '1\n100\ncm\nm\n' | ./unit_converter); \
		echo "$$output" | grep -q '변환 결과: 1.0000 m'
	@output=$$(printf '2\n2.5\nkg\nlb\n' | ./unit_converter); \
		echo "$$output" | grep -q '변환 결과: 5.5116 lb'
	@output=$$(printf '3\n32\nF\nC\n' | ./unit_converter); \
		echo "$$output" | grep -q '변환 결과: 0.0000 c'
	@output=$$(printf '3\n-40\nC\nF\n' | ./unit_converter); \
		echo "$$output" | grep -q '변환 결과: -40.0000 f'
	@if printf '4\n' | ./unit_converter >/dev/null 2>&1; then \
		echo 'Invalid category was accepted.' >&2; \
		exit 1; \
	fi
	@if printf '1\n10\nkg\nm\n' | ./unit_converter >/dev/null 2>&1; then \
		echo 'Incompatible units were accepted.' >&2; \
		exit 1; \
	fi
	@if printf '1\n-1\nm\ncm\n' | ./unit_converter >/dev/null 2>&1; then \
		echo 'Negative length was accepted.' >&2; \
		exit 1; \
	fi

clean:
	rm -f $(PROGRAMS)
	rm -rf $(addsuffix .dSYM,$(PROGRAMS))
