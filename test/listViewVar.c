#include "GUI.h"
#include "LISTVIEW.h"
#include "BUTTON.h"
#include <signal.h>
#include <string.h>

// 自定义数据结构
typedef struct
{
    const char *description; // 描述（可能包含换行）
    const char *value;       // 值
} ListViewData;

// 示例数据 - 包含长描述文本
ListViewData listData[] = {
    { "Device Status Monitor\n(System Status)", "Normal" },
    { "Temperature Sensor\n(Real-time Monitor)", "25.5°C" },
    { "Battery Voltage Monitor\n(Power System)", "3.7V" },
    { "Network Connection Status\n(Network Status)", "Connected" },
    { "System Uptime Statistics\n(Running Time)", "12:34:56" },
    { "Memory Usage Monitor\n(RAM Usage)", "45%" },
    { "Firmware Version Display\n(Version Info)", "V2.1.5" },
    { "Wireless Signal Strength\n(Signal Quality)", "Good" }
};

#define NUM_ROWS (sizeof(listData) / sizeof(listData[0]))
#define COL_WIDTH_DESC 120
#define COL_WIDTH_VALUE 80
#define ROW_HEIGHT 40 // 增加行高以容纳换行文本

void handle_sigint(int sig)
{
    // 可以在这里添加一些资源释放的操作，比如销毁 GUI 组件等
    exit(0); // 退出程序
}
int main(void)
{
    signal(SIGINT, handle_sigint);
    GUI_Init();
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();

    // 设置字体
    GUI_SetFont(&GUI_Font8x16);
    GUI_SetColor(GUI_WHITE);

    // 创建标题
    GUI_DispStringHCenterAt("Device Status Monitor Panel", 160, 10);

    // 创建ListView
    LISTVIEW_Handle hList = LISTVIEW_Create(10, 30, 300, 200,
                                            WM_HBKWIN,  // 父窗口
                                            0,          // 控件ID
                                            WM_CF_SHOW, // 创建标志
                                            0);         // 特殊标志

    // 设置ListView属性
    LISTVIEW_SetGridVis(hList, 1); // 显示网格线
    LISTVIEW_SetBkColor(hList, LISTVIEW_CI_UNSEL, GUI_DARKGRAY);
    LISTVIEW_SetTextColor(hList, LISTVIEW_CI_UNSEL, GUI_WHITE);

    // 添加列
    LISTVIEW_AddColumn(hList, COL_WIDTH_DESC, "Description", GUI_TA_LEFT);
    LISTVIEW_AddColumn(hList, COL_WIDTH_VALUE, "Value", GUI_TA_CENTER);

    // 添加行数据
    for (int i = 0; i < NUM_ROWS; i++)
    {
        const GUI_ConstString rowData[] = {
            listData[i].description,
            listData[i].value
        };
        LISTVIEW_AddRow(hList, rowData);
    }

    // 设置行高
    LISTVIEW_SetRowHeight(hList, ROW_HEIGHT);

    // 创建按钮
    BUTTON_Handle hButton = BUTTON_Create(260, 5, 50, 25,
                                          0,           // 控件ID
                                          WM_CF_SHOW); // 创建标志
    BUTTON_SetText(hButton, "Refresh");

    // 主循环
    while (1)
    {
        GUI_Delay(100);

        // 处理按钮点击
        if (BUTTON_IsPressed(hButton))
        {
            // 更新数据（模拟）
            static int counter = 0;
            counter++;

            // 更新列表中的值
            listData[0].value = (counter % 2) ? "Normal" : "Warning";
            listData[1].value = (counter % 2) ? "26.2°C" : "28.7°C";
            listData[4].value = (counter % 2) ? "12:45:23" : "13:10:45";

            // 重绘ListView
            WM_InvalidateWindow(hList);
        }
    }

    return 0;
}
