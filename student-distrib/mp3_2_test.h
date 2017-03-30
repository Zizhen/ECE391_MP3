#ifndef _MP3_2_TEST_H
#define _MP3_2_TEST_H

#include "file_sys.h"
#include "lib.h"
#include "terminal.h"
#include "rtc.h"
#include "i8259.h"
#include "keyboard.h"

extern void test_init();

extern void list_file();

extern void read_file_by_name();

extern void read_file_by_index();

extern void rtc_test();

extern void rtc_test_finished();

#endif
