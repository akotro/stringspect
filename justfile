# Color codes
GREEN := "\\e[32m"
RED := "\\e[31m"
PURPLE := "\\e[35m"
RESET := "\\e[0m"

@test: build
    echo -e "{{PURPLE}}Testing{{RESET}}"

    ./target/tests

    echo ""

build:
    @echo -e "{{PURPLE}}Building{{RESET}}"

    @ mkdir -p target
    gcc -Wall -O3 -o target/stringspect src/stringspect.c
    gcc -Wall -o target/tests src/tests.c src/unity.c src/stringspect.c -I./src/ -DUNIT_TEST

    @echo ""

@validate: build
    echo -e "{{PURPLE}}Validating{{RESET}}"

    @valgrind --track-origins=yes ./target/stringspect 'test string'

    echo ""
