/**
 * @file app_print.h
 * @author crt0dotS
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 */

#include <mooncake.h>
#include "../../hal/hal.h"
#include "../utils/theme/theme_define.h"
#include "../utils/anim/anim_define.h"
#include "../utils/icon/icon_define.h"

#include "assets/print_big.h"
#include "assets/print_small.h"

namespace MOONCAKE
{
    namespace APPS
    {
        class AppPrint : public APP_BASE
        {
            private:
                struct Data_t
                {
                    HAL::Hal* hal = nullptr;
                };
                Data_t _data;
                void _update_input();
                void _print_demo();
                void _print_init();
                void _print_deinit();

            public:
                void onCreate() override;
                void onResume() override;
                void onRunning() override;
                void onDestroy() override;
        };

        class AppPrint_Packer : public APP_PACKER_BASE
        {
            std::string getAppName() override { return "PRINT"; }
            void* getAppIcon() override { return (void*)(new AppIcon_t(image_data_print_big, image_data_print_small)); }
            void* newApp() override { return new AppPrint; }
            void deleteApp(void *app) override { delete (AppPrint*)app; }
        };
    }
}
