
#include "GUI.h"
#include "LISTVIEW.h"
#include "BUTTON.h"
#include <string.h>

// 自定义数据结构
typedef struct {
    const char* description; // 描述（可能包含换行）
    const char* value;       // 值
} ListViewData;

// 示例数据
ListViewData listData[] = {
    {"设备状态\n(Status)", "正常"},
    {"温度传感器\n(Temperature Sensor)", "25.5°C"},
    {"电池电压\n(Battery Voltage)", "3.7V"},
    {"网络连接状态\n(Network Connection)", "已连接"},
    {"系统运行时间\n(System Uptime)", "12:34:56"},
    {"内存使用情况\n(Memory Usage)", "45%"},
    {"固件版本\n(Firmware Version)", "V2.1.5"},
    {"信号强度\n(Signal Strength)", "良好"}
};

#define NUM_ROWS (sizeof(listData) / sizeof(listData[0]))
#define COL_WIDTH_DESC 120
#define COL_WIDTH_VALUE 80
#define ROW_HEIGHT 30
#define LISTVIEW_HEIGHT (NUM_ROWS * ROW_HEIGHT)

// 计算换行后的行数
int CountLines(const char* text) {
    if (!text || !*text) return 1;

    int lines = 1;
    while (*text) {
        if (*text++ == '\n') lines++;
    }
    return lines;
}

// 自定义ListView绘制回调函数
void CustomDrawListView(WM_HWIN hWin, int Row, int Col, RECT* pRect, int Sel) {
    if (Row < 0 || Row >= NUM_ROWS) return;

    const char* text;
    if (Col == 0) {
        text = listData[Row].description;
    } else if (Col == 1) {
        text = listData[Row].value;
    } else {
        return;
    }

    int align = (Col == 0) ? GUI_TA_LEFT : GUI_TA_CENTER;

    // 设置文本颜色和背景色
    if (Sel) {
        GUI_SetColor(GUI_WHITE);
        GUI_SetBkColor(GUI_BLUE);
    } else {
        GUI_SetColor(GUI_WHITE);
        GUI_SetBkColor(GUI_DARKGRAY);
    }
    GUI_ClearRectEx(pRect);

    if (Col == 0) {
        // 处理描述列（支持换行）
        int lineHeight = GUI_GetFontSizeY();
        int y = pRect->y0;
        int maxY = pRect->y1;

        const char* start = text;
        const char* end = text;

        while (*end && y < maxY) {
            if (*end == '\n' || *end == '\0') {
                // 绘制当前行
                char temp[50];
                int len = end - start;
                if (len > 0) {
                    len = (len < sizeof(temp)-1) ? len : sizeof(temp)-1;
                    memcpy(temp, start, len);
                    temp[len] = '\0';

                    GUI_DispStringAt(temp, pRect->x0 + 2, y);
                }

                y += lineHeight;
                start = end + 1;
            }
            end++;
        }
    } else {
        // 值列正常绘制
        GUI_DispStringInRect(text, pRect, align | GUI_TA_VCENTER);
    }
}

// 设置ListView行高（根据换行数量调整）
void SetListViewRowHeights(LISTVIEW_Handle hList) {
    for (int i = 0; i < NUM_ROWS; i++) {
        int lines = CountLines(listData[i].description);
        int rowHeight = lines * GUI_GetFontSizeY() + 8; // 基础行高+间距
        LISTVIEW_SetRowHeight(hList, i, rowHeight);
    }
}

int main(void) {
    GUI_Init();
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();

    // 设置字体
    GUI_SetFont(&GUI_FontComic18B_ASCII);
    GUI_SetColor(GUI_WHITE);

    // 创建标题
    GUI_DispStringHCenterAt("设备状态监控面板", 160, 10);

    // 创建ListView
    int listY = 40;
    int listHeight = GUI_MIN(LISTVIEW_HEIGHT, 200);
    LISTVIEW_Handle hList = LISTVIEW_Create(10, listY, 300, listHeight, 0, 0, WM_CF_SHOW, 0);

    // 设置ListView属性
    LISTVIEW_SetGridVis(hList, 1); // 显示网格线
    LISTVIEW_SetBkColor(hList, LISTVIEW_CI_UNSEL, GUI_DARKGRAY);
    LISTVIEW_SetTextColor(hList, LISTVIEW_CI_UNSEL, GUI_WHITE);
    LISTVIEW_SetGridColor(hList, GUI_GRAY);

    // 添加列
    LISTVIEW_AddColumn(hList, COL_WIDTH_DESC, "描述", GUI_TA_CENTER);
    LISTVIEW_AddColumn(hList, COL_WIDTH_VALUE, "值", GUI_TA_CENTER);

    // 添加行（文本内容会在绘制时使用自定义数据）
    for (int i = 0; i < NUM_ROWS; i++) {
        LISTVIEW_AddRow(hList, NULL);
    }

    // 设置自定义绘制回调
    LISTVIEW_SetOwnerDraw(hList, CustomDrawListView);

    // 根据内容设置行高
    SetListViewRowHeights(hList);

    // 创建刷新按钮
    BUTTON_Handle hButton = BUTTON_Create(260, 5, 50, 25, WM_HBKWIN, 0, WM_CF_SHOW, 0);
    BUTTON_SetText(hButton, "刷新");

    // 主循环
    while (1) {
        GUI_Delay(100);

        // 处理按钮点击
        if (WM_GetIdleState() && BUTTON_IsPressed(hButton)) {
            // 更新数据（模拟）
            static int counter = 0;
            counter++;

            // 更新列表中的值
            listData[0].value = (counter % 2) ? "正常" : "警告";
            listData[1].value = (counter % 2) ? "26.2°C" : "28.7°C";
            listData[4].value = (counter % 2) ? "12:45:23" : "13:10:45";

            // 重绘ListView
            WM_InvalidateWindow(hList);
        }
    }

    return 0;
}
