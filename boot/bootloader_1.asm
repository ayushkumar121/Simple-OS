; For ISO build we don't need to create a first stage boot loader
; Bootloader 446 bytes

;jmp $

; Partition Table 64 bytes (16  * 4) means 4 entries
; A entry contains
;
;  * location of partition
;  * size of partition
;  * type of partition (Bootable or not)


; Magic Number tells the format of Boot loader
; 0xAA55 is for MBR or Master boot Record

; Pad remaing os with 0 

; times 510-($-$$) db 0

; last 2 bytes is magic number
; dw 0xAA55