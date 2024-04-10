/**
 * @file app_print.cpp
 * @author crt0dotS
 * @brief
 * @version 0.1
 * @date 2024-04-07
 *
 * @copyright Copyright (c) 2024
 */

#include "app_print.h"
#include "spdlog/spdlog.h"
#include "../utils/theme/theme_define.h"

using namespace MOONCAKE::APPS;

#define _canvas _data.hal->canvas()
#define _canvas_update _data.hal->canvas_update
#define _canvas_clear() _canvas->fillScreen(THEME_COLOR_BG)

void AppPrint::_print_demo()
{
    _canvas->print("Print, Cardputer!");
    _canvas_update();
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
    _print_demo();
}

void AppPrint::onRunning()
{
    if (_data.hal->homeButton()->pressed())
    {
        _data.hal->playNextSound();
        spdlog::info("quit print");
        destroyApp();
    }
}

void AppPrint::onDestroy() {
    _canvas->setTextScroll(false);
}
