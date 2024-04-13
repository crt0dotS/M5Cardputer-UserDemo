/**
 * @file app_print.cpp
 * @author crt0dotS
 * @brief
 * @version 0.1
 * @date 2024-04-13
 *
 * @copyright Copyright (c) 2024
 */

#include "app_print.h"
#include "spdlog/spdlog.h"
#include "../utils/theme/theme_define.h"
#include "../utils/ble_printer_wrap/ble_printer_wrap.h"

using namespace MOONCAKE::APPS;

#define _canvas _data.hal->canvas()
#define _canvas_update _data.hal->canvas_update
#define _canvas_clear() _canvas->fillScreen(THEME_COLOR_BG)
#define _keyboard _data.hal->keyboard()

void AppPrint::_print_demo()
{
    _canvas->print("Printing demo...\n");
    _canvas_update();
    ble_printer_wrap_print();
    _canvas->print("Finished!\n");
    _canvas_update();
}

void AppPrint::_print_init()
{
    _canvas->print("Connecting to printer...\n");
    _canvas_update();
    ble_printer_wrap_init();
    _canvas->print("Connected!\n");
    _canvas_update();
}

void AppPrint::_print_deinit()
{
    _canvas->print("Disconnecting  printer...\n");
    _canvas_update();
    ble_printer_wrap_deinit();
    _canvas->print("Disconnected!\n");
    _canvas_update();
}

void AppPrint::_update_input()
{
    if (_keyboard->keyList().size() != 0)
    {
        _keyboard->updateKeysState();

        if (_keyboard->keysState().enter)
        {
            _print_init();
        }
        else if (_keyboard->keysState().space)
        {
            _print_demo();
        }
    }
}

void AppPrint::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Get hal
    _data.hal = mcAppGetDatabase()->Get("HAL")->value<HAL::Hal *>();
}

void AppPrint::onResume()
{
    spdlog::info("{} onResume", getAppName());

    ANIM_APP_OPEN();

    _canvas_clear();
    _canvas->setTextScroll(true);
    _canvas->setBaseColor(THEME_COLOR_BG);
    _canvas->setTextColor(THEME_COLOR_REPL_TEXT, THEME_COLOR_BG);
    _canvas->setFont(FONT_REPL);
    _canvas->setTextSize(FONT_SIZE_REPL);

    // Avoid input panel
    _canvas->setCursor(0, 0);
    //run function once
    _canvas->print("BLE Printer test\nPress <enter> to connect\nPress <space> to print demo\n");
    _canvas_update();
}

void AppPrint::onRunning()
{
    _update_input();
    if (_data.hal->homeButton()->pressed())
    {
        _data.hal->playNextSound();
        spdlog::info("quit print");
        destroyApp();
    }
}

void AppPrint::onDestroy()
{
    _print_deinit();
    _canvas->setTextScroll(false);
}
