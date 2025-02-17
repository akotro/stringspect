#include <stdio.h>

#include "stringspect.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_print_char_to_bin(void) {
    char buffer[50] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_char_to_bin('A');
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING(" 01000001", buffer);
}

void test_draw_box_line(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    draw_box_line(3);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("───", buffer);
}

void test_draw_box_top(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    draw_box_top(3);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("┌───┐\n", buffer);
}

void test_draw_box_bot(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    draw_box_bot(3);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("└───┘\n\n", buffer);
}

void test_print_ascii(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_ascii('A');
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("        A", buffer);
}

void test_print_hex(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_hex('A');
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("       41", buffer);
}

void test_print_oct(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_oct('A');
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("      101", buffer);
}

void test_print_dec(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_dec('A');
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("       65", buffer);
}

void test_print_bin(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_bin('A');
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING(" 01000001", buffer);
}

void test_draw_content_row_ascii(void) {
    char buffer[200] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    const char *input = "AB";
    draw_content_row("ASCII", 12, input, 0, 2, print_ascii);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("│ASCII │          A│          B│\n", buffer);
}

void test_draw_content_row_dec(void) {
    char buffer[200] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    const char *input = "AB";
    draw_content_row("Dec", 12, input, 0, 2, print_dec);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("│Dec   │         65│         66│\n", buffer);
}

void test_print_substring(void) {
    char buffer[20] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_substring("Hello", 1, 3);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    TEST_ASSERT_EQUAL_STRING("'el'\n", buffer);
}

void test_print_box_single_char(void) {
    const char *input = "A";
    char buffer[500] = {0};
    FILE *fp = fmemopen(buffer, sizeof(buffer), "w");

    TEST_ASSERT_NOT_NULL(fp);

    FILE *original_stdout = stdout;
    stdout = fp;
    print_box(input, 0, 1, 12, 6);
    fflush(stdout);
    stdout = original_stdout;
    fclose(fp);

    const char *expected =
        "'A'\n"
        "┌──────────────────┐\n"
        "│ASCII │          A│\n"
        "│Dec   │         65│\n"
        "│Hex   │         41│\n"
        "│Oct   │        101│\n"
        "│Bin   │   01000001│\n"
        "└──────────────────┘\n\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_print_char_to_bin);
    RUN_TEST(test_draw_box_line);
    RUN_TEST(test_draw_box_top);
    RUN_TEST(test_draw_box_bot);
    RUN_TEST(test_print_ascii);
    RUN_TEST(test_print_hex);
    RUN_TEST(test_print_oct);
    RUN_TEST(test_print_dec);
    RUN_TEST(test_print_bin);
    RUN_TEST(test_draw_content_row_ascii);
    RUN_TEST(test_draw_content_row_dec);
    RUN_TEST(test_print_substring);
    RUN_TEST(test_print_box_single_char);

    return UNITY_END();
}
