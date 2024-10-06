#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void print_char_to_bin(char c) {
    printf(" ");
    for (int b = 7; b >= 0; b--) {
        int bit = ((c >> b) & 0b00000001);
        printf("%u", bit);
    }
}

void draw_box_line(int box_width) {
    for (int i = 0; i < box_width; i++) {
        printf("─");
    }
}

void draw_box_top(int box_width) {
    printf("┌");
    draw_box_line(box_width);
    printf("┐\n");
}

void draw_box_bot(int box_width) {
    printf("└");
    draw_box_line(box_width);
    printf("┘\n\n");
}

void draw_content_row(const char* label, int box_width_per_char,
                      const char* input, int current_index, int chars_in_box,
                      void (*content_printer)(char)) {
    printf("│%-6s│", label);
    for (int i = 0; i < chars_in_box; i++) {
        printf("  ");
        content_printer(input[current_index + i]);
        printf("│");
    }
    printf("\n");
}

void print_ascii(char c) { printf("%9c", c); }

void print_hex(char c) { printf("%9x", c); }

void print_dec(char c) { printf("%9d", c); }

void print_bin(char c) { print_char_to_bin(c); }

void print_substring(const char* input, int start, int end) {
    putchar('\'');

    for (int i = start; i < end; i++) {
        putchar(input[i]);
    }

    putchar('\'');
    putchar('\n');
}

void print_box(const char* input, int start, int chars_in_box,
               int box_width_per_char, int fixed_width) {
    int current_box_width = chars_in_box * box_width_per_char + fixed_width;

    print_substring(input, start, start + chars_in_box);

    draw_box_top(current_box_width);

    draw_content_row("ASCII", box_width_per_char, input, start, chars_in_box,
                     print_ascii);
    draw_content_row("Hex", box_width_per_char, input, start, chars_in_box,
                     print_hex);
    draw_content_row("Dec", box_width_per_char, input, start, chars_in_box,
                     print_dec);
    draw_content_row("Bin", box_width_per_char, input, start, chars_in_box,
                     print_bin);

    draw_box_bot(current_box_width);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No string input provided!\n");
        return 0;
    }

    char* input = argv[1];
    int length = strlen(input);
    int box_width_per_char = 12;
    int fixed_width = 6;
    int box_width = length * box_width_per_char + fixed_width;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);  // NOTE: Get terminal size

    if (box_width > w.ws_col) {
        int max_chars_per_box = (w.ws_col - fixed_width) / box_width_per_char;
        int current_index = 0;

        while (current_index < length) {
            int chars_in_box = (length - current_index > max_chars_per_box)
                                   ? max_chars_per_box
                                   : (length - current_index);
            print_box(input, current_index, chars_in_box, box_width_per_char,
                      fixed_width);
            current_index += chars_in_box;
        }
    } else {
        print_box(input, 0, length, box_width_per_char, fixed_width);
    }

    return 0;
}
