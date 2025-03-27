#pragma once

// const defs for escape codes
#define ESCAPE '\033'
#define ESCAPE_CLEAR_SCREEN 'c'
#define ESCAPE_RESET "\e[0m"

// init const for header text
#define HEADER_INIT '*'

// blinking 
#define BLINKING "\033[5m"

// constants for colours
#define DARKRED 52
#define RED 1
#define PINKRED 197
#define DARKPINKRED 89
#define PINK 198
#define LIGHTPINK 204
#define LIGHTORANGE 210
#define ORANGE 202
#define LIGHTGOLD 208
#define GOLD 214
#define YELLOW 226
#define DOTWHITE 7

#include "draw.c"
