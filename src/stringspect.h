#ifndef STRINGSPECT_H
#define STRINGSPECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Prints the binary representation of a character (with a leading space).
void print_char_to_bin(char c);

// Draws a horizontal line using the box-drawing character.
void draw_box_line(int box_width);

// Draws the top of the box.
void draw_box_top(int box_width);

// Draws the bottom of the box.
void draw_box_bot(int box_width);

// Prints a row within the box for a given label and content.
// The content_printer function pointer specifies how to print each character.
void draw_content_row(const char* label, int box_width_per_char,
                      const char* input, int current_index, int chars_in_box,
                      void (*content_printer)(char));

// Prints the character in ASCII format.
void print_ascii(char c);

// Prints the character in hexadecimal format.
void print_hex(char c);

// Prints the character in octal format.
void print_oct(char c);

// Prints the character in decimal format.
void print_dec(char c);

// Prints the character in binary format.
void print_bin(char c);

// Prints a substring of the input string between start and end indices.
void print_substring(const char* input, int start, int end);

// Prints the entire box given the input string and formatting parameters.
void print_box(const char* input, int start, int chars_in_box,
               int box_width_per_char, int fixed_width);

#ifdef __cplusplus
}
#endif

#endif  // STRINGSPECT_H
