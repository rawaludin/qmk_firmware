SRC += side.c rf.c sleep.c rf_driver.c user_kb.c side_driver.c

UART_DRIVER_REQUIRED = yes

CAPS_WORD_ENABLE = yes

mkfile_dir := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(mkfile_dir)/keymaps/$(KEYMAP)/qmk-vim/rules.mk
