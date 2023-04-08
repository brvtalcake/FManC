#include <assert.h>
#include <stdio.h>
#include <inttypes.h>
#include "test_suite.h"

void test_FMC_getEncoding()
{
    FILE *file1 = fopen("../../plain_text_data/lorem.txt", "rb"); // UTF-8
    FILE *file2 = fopen("../../plain_text_data/empty", "rb"); // EMPTY
    FILE *file3 = fopen("../../plain_text_data/test5_0", "rb"); // UTF-16 BE
    FILE *file4 = fopen("../../plain_text_data/test5_2", "rb"); // UTF-8
    FILE *file5 = fopen("../../plain_text_data/rand_5040", "rb"); // UTF-8 with BOM
    assert(FMC_getEncoding(file1) == utf8);
    assert(FMC_getEncoding(file2) == unknown);
    assert(FMC_getEncoding(file3) == utf16_be);
    assert(FMC_getEncoding(file4) == utf8);
    assert(FMC_getEncoding(file5) == utf8_bom);
    assert(FMC_getEncoding(NULL) == error);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);
    fclose(file5);
}

void test_FMC_checkEncodingFlag()
{
    assert(FMC_checkEncodingFlag(ASCII) == ascii);
    assert(FMC_checkEncodingFlag(UTF8) == utf8);
    assert(FMC_checkEncodingFlag(UTF8_BOM) == utf8_bom);
    assert(FMC_checkEncodingFlag(UTF16_LE) == utf16_le);
    assert(FMC_checkEncodingFlag(UTF16_BE) == utf16_be);
    assert(FMC_checkEncodingFlag(UTF32_LE) == utf32_le);
    assert(FMC_checkEncodingFlag(UTF32_BE) == utf32_be);
    assert(FMC_checkEncodingFlag(UNKNOWN) == unknown);

    assert(FMC_checkEncodingFlag(1) == FMC_checkEncodingFlag(UTF8));
    assert(FMC_checkEncodingFlag(2) == FMC_checkEncodingFlag(UTF8_BOM));
    assert(FMC_checkEncodingFlag(4) == FMC_checkEncodingFlag(UTF16_LE));
    assert(FMC_checkEncodingFlag(8) == FMC_checkEncodingFlag(UTF16_BE));
    assert(FMC_checkEncodingFlag(16) == FMC_checkEncodingFlag(UTF32_LE));
    assert(FMC_checkEncodingFlag(32) == FMC_checkEncodingFlag(UTF32_BE));
    assert(FMC_checkEncodingFlag(64) == FMC_checkEncodingFlag(ASCII));
    assert(FMC_checkEncodingFlag(128) == FMC_checkEncodingFlag(UNKNOWN));
}

void test_FMC_CodePoint()
{
    // 0xE4 0xB8 0xAD
    FMC_Byte bytes[4] = {0xAD, 0xB8, 0xE4, 0x00}; // 中
    FMC_Char* utf8_ch = FMC_allocChar(bytes, utf8, FMC_FALSE, 3);
    FMC_UNREACHABLE_ASSERT(utf8_ch != NULL);
    FMC_CodePoint cp = FMC_codePointFromUTF8(*utf8_ch);
    FMC_freeChar(utf8_ch);
    assert(cp == 0x4E2D); // 中
    
    bytes[0] = 0x4E;
    bytes[1] = 0x2D;
    bytes[2] = 0x00;
    bytes[3] = 0x00;
    FMC_Char* utf16le_ch = FMC_allocChar(bytes, utf16_le, FMC_FALSE, 2);
    FMC_UNREACHABLE_ASSERT(utf16le_ch != NULL);
    cp = FMC_codePointFromUTF16LE(*utf16le_ch);
    FMC_freeChar(utf16le_ch);
    assert(cp == 0x4E2D); // 中

    bytes[0] = 0xDF;
    bytes[1] = 0x62;
    bytes[2] = 0xD8;
    bytes[3] = 0x52;
    utf16le_ch = FMC_allocChar(bytes, utf16_le, FMC_FALSE, 4);
    FMC_UNREACHABLE_ASSERT(utf16le_ch != NULL);
    cp = FMC_codePointFromUTF16LE(*utf16le_ch);
    FMC_freeChar(utf16le_ch);
    assert(cp == 0x24B62);

    // U+24B62 codepoint == 0xD852 0xDF62 in UTF-16 BE
    bytes[0] = 0x62;
    bytes[1] = 0xDF;
    bytes[2] = 0x52;
    bytes[3] = 0xD8;
    FMC_Char* utf16be_ch = FMC_allocChar(bytes, utf16_be, FMC_FALSE, 4);
    FMC_UNREACHABLE_ASSERT(utf16be_ch != NULL);
    cp = FMC_codePointFromUTF16BE(*utf16be_ch);
    FMC_freeChar(utf16be_ch);
    assert(cp == 0x24B62); // One of the examples from <https://en.wikipedia.org/wiki/UTF-16#Examples>

    // U+1F4A9 codepoint == (in UTF32-LE) 0xA9 0xF4 0x01 0x00
    bytes[0] = 0x00;
    bytes[1] = 0x01;
    bytes[2] = 0xF4;
    bytes[3] = 0xA9;
    FMC_Char* utf32le_ch = FMC_allocChar(bytes, utf32_le, FMC_FALSE, 4);
    FMC_UNREACHABLE_ASSERT(utf32le_ch != NULL);
    cp = FMC_codePointFromUTF32LE(*utf32le_ch);
    FMC_freeChar(utf32le_ch);
    assert(cp == 0x1F4A9);

    // U+1F4A9 codepoint == (in UTF32-BE) 0x00 0x01 0xF4 0xA9
    bytes[0] = 0xA9;
    bytes[1] = 0xF4;
    bytes[2] = 0x01;
    bytes[3] = 0x00;
    FMC_Char* utf32be_ch = FMC_allocChar(bytes, utf32_be, FMC_FALSE, 4);
    FMC_UNREACHABLE_ASSERT(utf32be_ch != NULL);
    cp = FMC_codePointFromUTF32BE(*utf32be_ch);
    FMC_freeChar(utf32be_ch);
    assert(cp == 0x1F4A9);

    /* bytes[0] = 'a';
    bytes[1] = 0x00;
    bytes[2] = 0x00;
    bytes[3] = 0x00;
    FMC_Char* ascii_ch = FMC_allocChar(bytes, ascii, FMC_FALSE, 1);
    FMC_UNREACHABLE_ASSERT(ascii_ch != NULL);
    cp = FMC_codePointFromASCII(ascii_ch);
    FMC_freeChar(ascii_ch);
    assert(cp == 'a'); */

    FMC_CharComp utf8_ch_comp = (FMC_CharComp) {.byte0 = 0xAD, .byte1 = 0xB8, .byte2 = 0xE4, .byte3 = 0x00};
    cp = FMC_codePointFromUTF8(utf8_ch_comp);
    assert(cp == 0x4E2D); 

    FMC_CharComp utf16le_ch_comp = (FMC_CharComp) {.byte0 = 0x4E, .byte1 = 0x2D, .byte2 = 0x00, .byte3 = 0x00};
    cp = FMC_codePointFromUTF16LE(utf16le_ch_comp);
    assert(cp == 0x4E2D);

    utf16le_ch_comp = (FMC_CharComp) {.byte0 = 0xDF, .byte1 = 0x62, .byte2 = 0xD8, .byte3 = 0x52};
    cp = FMC_codePointFromUTF16LE(utf16le_ch_comp);
    assert(cp == 0x24B62);

    FMC_CharComp utf16be_ch_comp = (FMC_CharComp) {.byte0 = 0x62, .byte1 = 0xDF, .byte2 = 0x52, .byte3 = 0xD8};
    cp = FMC_codePointFromUTF16BE(utf16be_ch_comp);
    assert(cp == 0x24B62);

    FMC_CharComp utf32le_ch_comp = (FMC_CharComp) {.byte0 = 0x00, .byte1 = 0x01, .byte2 = 0xF4, .byte3 = 0xA9};
    cp = FMC_codePointFromUTF32LE(utf32le_ch_comp);
    assert(cp == 0x1F4A9);

    FMC_CharComp utf32be_ch_comp = (FMC_CharComp) {.byte0 = 0xA9, .byte1 = 0xF4, .byte2 = 0x01, .byte3 = 0x00};
    cp = FMC_codePointFromUTF32BE(utf32be_ch_comp);
    assert(cp == 0x1F4A9);



    uint32_t utf8_raw_ch = 0xE4B8AD;
    cp = FMC_codePointFromUTF8(utf8_raw_ch);
    fprintf(stderr, "cp = %#x\n", cp);
    assert(cp == 0x4E2D);

    uint32_t utf16le_raw_ch = 0x2D4E;
    cp = FMC_codePointFromUTF16LE(utf16le_raw_ch);
    assert(cp == 0x4E2D);

    utf16le_raw_ch = 0x52D862DF;
    cp = FMC_codePointFromUTF16LE(utf16le_raw_ch);
    assert(cp == 0x24B62);

    uint32_t utf16be_raw_ch = 0xD852DF62;
    cp = FMC_codePointFromUTF16BE(utf16be_raw_ch);
    assert(cp == 0x24B62);

    uint32_t utf32le_raw_ch = 0xA9F40100;
    cp = FMC_codePointFromUTF32LE(utf32le_raw_ch);
    assert(cp == 0x1F4A9);

    uint32_t utf32be_raw_ch = FMC_bitSwap(32, utf32le_raw_ch);
    cp = FMC_codePointFromUTF32BE(utf32be_raw_ch);
    assert(cp == 0x1F4A9);

}