#ifndef KEYMAP_H
#define KEYMAP_H

#include "def.h"

enum KEY_CTL
{
    BACKSPACE = 0x81,
    TAB,
    ENTER,
    PAD_ENTER,
    CTRL_L,
    SHIFT_L,
    PAD_SLASH,
    SHIFT_R,
    CAPS_LOCK
};

#define MAP_COL 3


uint8_t keymap[]= {
// shift  !shift   0xe0
    0,      0,      0,
    0,      0,      0,
    '1',    '!',    0,
    '2',    '@',    0,
    '3',    '#',    0,
    '4',    '$',    0,
    '5',    '%',    0,
    '6',    '^',    0,
    '7',    '&',    0,
    '8',    '*',    0,
    '9',    '(',    0,
    '0',    ')',    0,
    '-',    '_',    0,
    '=',    '+',    0,
    BACKSPACE, BACKSPACE, 0,    //0x0e
    TAB,    TAB,    0,          //0x0f
    'q',    'Q',    0,
    'w',    'W',    0,
    'e',    'E',    0,
    'r',    'R',    0,
    't',    'T',    0,
    'y',    'Y',    0,
    'u',    'U',    0,
    'i',    'I',    0,
    'o',    'O',    0,
    'p',    'P',    0,
    '[',    '{',    0,
    ']',    '}',    0,
    ENTER,  ENTER,  PAD_ENTER,      //0x1c
    CTRL_L, CTRL_L, CTRL_L,         //0x1d
    'a',    'A',    0,
    's',    'S',    0,
    'd',    'D',    0,
    'f',    'F',    0,
    'g',    'G',    0,
    'h',    'H',    0,
    'j',    'J',    0,
    'k',    'K',    0,
    'l',    'L',    0,
    ';',    ':',    0,
    '\'',    '\"',  0,
    '`',    '~',    0,
    SHIFT_L, SHIFT_L, SHIFT_L,      //0x2a
    '\\',   '|',    0,
    'z',    'Z',    0,
    'x',    'X',    0,
    'c',    'C',    0,
    'v',    'V',    0,
    'b',    'B',    0,
    'n',    'N',    0,
    'm',    'M',    0,
    ',',    '<',    0,
    '.',    '>',    0,
    '/',    '?',    PAD_SLASH,
    SHIFT_R, SHIFT_R, 0,            //0x36
    '*',    '*',    0,
    0,      0,      0,
    ' ',    ' ',     0,
    CAPS_LOCK, CAPS_LOCK, CAPS_LOCK //0x3a

};

#endif