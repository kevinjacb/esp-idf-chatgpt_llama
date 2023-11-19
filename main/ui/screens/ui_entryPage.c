// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_entryPage_screen_init(void)
{
ui_entryPage = lv_obj_create(NULL);
lv_obj_clear_flag( ui_entryPage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_entryPage, lv_color_hex(0x343541), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_entryPage, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_chatgptdecor = lv_label_create(ui_entryPage);
lv_obj_set_width( ui_chatgptdecor, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_chatgptdecor, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_chatgptdecor, -1 );
lv_obj_set_y( ui_chatgptdecor, -48 );
lv_obj_set_align( ui_chatgptdecor, LV_ALIGN_CENTER );
lv_label_set_text(ui_chatgptdecor,"ChatGPT");
lv_obj_set_style_text_color(ui_chatgptdecor, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_chatgptdecor, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_chatgptdecor, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Suggestion2 = lv_label_create(ui_entryPage);
lv_obj_set_width( ui_Suggestion2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Suggestion2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Suggestion2, -75 );
lv_obj_set_y( ui_Suggestion2, 53 );
lv_obj_set_align( ui_Suggestion2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Suggestion2,"Gib me ideas");
lv_obj_add_flag( ui_Suggestion2, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_clear_flag( ui_Suggestion2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_text_font(ui_Suggestion2, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Suggestion2, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Suggestion2, lv_color_hex(0x727272), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Suggestion2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_Suggestion2, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Suggestion2, 28, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Suggestion2, 28, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Suggestion2, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Suggestion2, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Suggestion1 = lv_label_create(ui_entryPage);
lv_obj_set_width( ui_Suggestion1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Suggestion1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Suggestion1, 72 );
lv_obj_set_y( ui_Suggestion1, 53 );
lv_obj_set_align( ui_Suggestion1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Suggestion1,"Write a song");
lv_obj_add_flag( ui_Suggestion1, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_font(ui_Suggestion1, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Suggestion1, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Suggestion1, lv_color_hex(0x727272), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Suggestion1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_Suggestion1, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Suggestion1, 28, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Suggestion1, 28, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Suggestion1, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Suggestion1, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_keyboardPanel1 = lv_obj_create(ui_entryPage);
lv_obj_set_width( ui_keyboardPanel1, 318);
lv_obj_set_height( ui_keyboardPanel1, 245);
lv_obj_set_x( ui_keyboardPanel1, -4 );
lv_obj_set_y( ui_keyboardPanel1, 186 );
lv_obj_set_align( ui_keyboardPanel1, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_keyboardPanel1,LV_FLEX_FLOW_ROW_WRAP_REVERSE);
lv_obj_set_flex_align(ui_keyboardPanel1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_add_state( ui_keyboardPanel1, LV_STATE_FOCUSED );     /// States
lv_obj_clear_flag( ui_keyboardPanel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_keyboardPanel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_keyboardPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_keyboardPanel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_keyboardPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Keyboard1 = lv_keyboard_create(ui_keyboardPanel1);
lv_obj_set_width( ui_Keyboard1, 300);
lv_obj_set_height( ui_Keyboard1, 120);
lv_obj_set_x( ui_Keyboard1, 0 );
lv_obj_set_y( ui_Keyboard1, 69 );
lv_obj_set_align( ui_Keyboard1, LV_ALIGN_CENTER );

ui_keyboardTextArea1 = lv_textarea_create(ui_keyboardPanel1);
lv_obj_set_width( ui_keyboardTextArea1, 295);
lv_obj_set_height( ui_keyboardTextArea1, 34);
lv_obj_set_x( ui_keyboardTextArea1, 1 );
lv_obj_set_y( ui_keyboardTextArea1, 84 );
lv_obj_set_align( ui_keyboardTextArea1, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_keyboardTextArea1,"Send a message");
lv_obj_clear_flag( ui_keyboardTextArea1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags



ui_sendButton1 = lv_btn_create(ui_keyboardTextArea1);
lv_obj_set_width( ui_sendButton1, 38);
lv_obj_set_height( ui_sendButton1, 50);
lv_obj_set_x( ui_sendButton1, 124 );
lv_obj_set_y( ui_sendButton1, 1 );
lv_obj_set_align( ui_sendButton1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_sendButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_sendButton1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_sendButton1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_sendButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_sendButton1, &ui_img_1645855493, LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_img_recolor(ui_sendButton1, lv_color_hex(0xC9CADE), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_recolor_opa(ui_sendButton1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_recolor(ui_sendButton1, lv_color_hex(0xFFFFFF), LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_img_recolor_opa(ui_sendButton1, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_img_recolor(ui_sendButton1, lv_color_hex(0x282626), LV_PART_MAIN| LV_STATE_DISABLED);
lv_obj_set_style_bg_img_recolor_opa(ui_sendButton1, 255, LV_PART_MAIN| LV_STATE_DISABLED);

lv_obj_add_event_cb(ui_Suggestion2, ui_event_Suggestion2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Suggestion1, ui_event_Suggestion1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Keyboard1, ui_event_Keyboard1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_sendButton1, ui_event_sendButton1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_keyboardTextArea1, ui_event_keyboardTextArea1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_keyboardPanel1, ui_event_keyboardPanel1, LV_EVENT_ALL, NULL);

}
