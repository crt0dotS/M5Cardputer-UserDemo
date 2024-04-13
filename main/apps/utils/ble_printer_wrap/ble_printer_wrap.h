/**
 * @file ble_printer_wrap.c
 * @author crt0dotS
 * @brief
 * @version 0.1
 * @date 2024-04-12
 *
 * @copyright Copyright (c) 2024
 *
 * ------------------------------------------------------------
 * "THE BEERWARE LICENSE" (Revision 42):
 * <crt0dotS> wrote this code. As long as you retain this
 * notice, you can do whatever you want with this stuff. If we
 * meet someday, and you think this stuff is worth it, you can
 * buy me a beer in return.
 * ------------------------------------------------------------
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {ALIGN_LEFT=0x30, ALIGN_CENTER=0x31, ALIGN_RIGHT=0x32} prntr_align_t;
typedef enum {BC_TXT_NON=0x0, BC_TXT_ABV=0x1, BC_TXT_BLW=0x2, BC_TXT_BTH=0x3} prntr_bc_txt_pos_t;
typedef enum {BC_UPCA=0, BC_UPCE=0x01, BCE_EAN13=0x02, BCE_EAN8=0x03, BC_CODE93=0x48, BC_CODE128=0x49} prntr_bc_type_t;

void ble_printer_wrap_init(void);
void ble_printer_wrap_deinit(void);
void ble_printer_wrap_print(void);
void ble_printer_escpos_initialize(void);
void ble_printer_escpos_set_align(prntr_align_t align);
void ble_printer_escpos_set_font(uint8_t font, bool wider, bool taller, bool uline, bool bold, bool italic);
void ble_printer_escpos_feed_paper(int lines);
void ble_printer_escpos_print_string(char *prnt_str);
void ble_printer_escpos_println_string(char *prnt_str);
void ble_printer_escpos_print_barcode(prntr_bc_type_t type, int height, prntr_bc_txt_pos_t pos, char *data);
void ble_printer_escpos_print_qrcode(char *qrtext, int qrsize);

#ifdef __cplusplus
}
#endif
