#include <string.h>
#include <stdio.h>
#include "lcd.h"
#include "delay.h"

unsigned int book_count = 0, pen_count = 0;
int price_book = 50, price_pen = 10;
extern unsigned char mode;

char tag1_id[] = "060067D961D9";
char tag2_id[] = "060067836E8C";

void display_product_count(const char* product, unsigned int count) {
    char buf[20];
    lcd_command(0xC0);
    snprintf(buf, sizeof(buf), "Count: %d", count);
    lcd_str((unsigned char*)buf);
}

void display_tag_and_price(char* id) {
    if (strcmp(id, tag1_id) == 0) {
        lcd_command(0x80);
        lcd_str("Book 50 Rs");
        lcd_command(0xC0);
        lcd_str((unsigned char*)id);
    } else if (strcmp(id, tag2_id) == 0) {
        lcd_command(0x80);
        lcd_str("Pen 10 Rs");
        lcd_command(0xC0);
        lcd_str((unsigned char*)id);
    } else {
        lcd_command(0x80);
        lcd_str("Unknown Tag");
        lcd_command(0xC0);
        lcd_str((unsigned char*)id);
    }
}

void process_rfid(char* id) {
    if (mode == 1) {
        if (strcmp(id, tag1_id) == 0) {
            book_count++;
            lcd_command(0x80);
            lcd_str("Book Added");
            display_product_count("Book", book_count);
        } else if (strcmp(id, tag2_id) == 0) {
            pen_count++;
            lcd_command(0x80);
            lcd_str("Pen Added");
            display_product_count("Pen", pen_count);
        }
    } else if (mode == 2) {
        if (strcmp(id, tag1_id) == 0 && book_count > 0) {
            book_count--;
            lcd_command(0x80);
            lcd_str("Book removed");
            display_product_count("Book", book_count);
        } else if (strcmp(id, tag2_id) == 0 && pen_count > 0) {
            pen_count--;
            lcd_command(0x80);
            lcd_str("Pen removed");
            display_product_count("Pen", pen_count);
        }
    }
}

void show_total(void) {
    int total = (book_count * price_book) + (pen_count * price_pen);
    char buf[20];

    lcd_command(0x01);
    lcd_command(0x80);
    snprintf(buf, sizeof(buf), "B:%d P:%d", book_count, pen_count);
    lcd_str((unsigned char*)buf);

    lcd_command(0xC0);
    snprintf(buf, sizeof(buf), "Total:%d Rs", total);
    lcd_str((unsigned char*)buf);
    delay_ms(2000);

    lcd_command(0x01);
    lcd_command(0x80);
    lcd_str("Thanks for");
    lcd_command(0xC0);
    lcd_str("Purchasing");
    delay_ms(5000);

    book_count = 0;
    pen_count = 0;
    mode = 0;
}

