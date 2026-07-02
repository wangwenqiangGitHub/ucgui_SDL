# LISTVIEW 可变行高功能实现

## 概述

本实现为uC/GUI的LISTVIEW控件添加了可变行高支持，允许每一行都有不同的行高，特别适用于需要显示多行文本或不同内容高度的场景。

## 主要特性

1. **每行独立行高**：可以为每一行设置不同的行高
2. **自动行高计算**：支持根据内容自动计算行高
3. **默认行高设置**：可以设置全局默认行高
4. **动态行高调整**：运行时可以动态调整行高
5. **向后兼容**：保持与原有API的兼容性

## 新增API函数

### 1. LISTVIEW_SetRowHeightEx
```c
void LISTVIEW_SetRowHeightEx(LISTVIEW_Handle hObj, unsigned RowIndex, unsigned RowHeight);
```
设置指定行的行高。

**参数：**
- `hObj`: LISTVIEW句柄
- `RowIndex`: 行索引（从0开始）
- `RowHeight`: 行高（像素）

**示例：**
```c
// 设置第0行行高为30像素
LISTVIEW_SetRowHeightEx(hList, 0, 30);
```

### 2. LISTVIEW_GetRowHeight
```c
unsigned LISTVIEW_GetRowHeight(LISTVIEW_Handle hObj, unsigned RowIndex);
```
获取指定行的行高。

**参数：**
- `hObj`: LISTVIEW句柄
- `RowIndex`: 行索引（从0开始）

**返回值：** 行高（像素）

**示例：**
```c
// 获取第0行行高
unsigned height = LISTVIEW_GetRowHeight(hList, 0);
```

### 3. LISTVIEW_SetDefaultRowHeight
```c
void LISTVIEW_SetDefaultRowHeight(LISTVIEW_Handle hObj, unsigned DefaultHeight);
```
设置默认行高，当某行没有设置特定行高时使用。

**参数：**
- `hObj`: LISTVIEW句柄
- `DefaultHeight`: 默认行高（像素）

**示例：**
```c
// 设置默认行高为20像素
LISTVIEW_SetDefaultRowHeight(hList, 20);
```

## 使用示例

### 基本用法

```c
#include "GUI.h"
#include "LISTVIEW.h"

int main(void)
{
    GUI_Init();
    
    // 创建LISTVIEW
    LISTVIEW_Handle hList = LISTVIEW_CreateEx(10, 10, 200, 150, 0, WM_CF_SHOW, 0, 0);
    
    // 设置默认行高
    LISTVIEW_SetDefaultRowHeight(hList, 20);
    
    // 添加列
    LISTVIEW_AddColumn(hList, 100, "Name", GUI_TA_LEFT);
    LISTVIEW_AddColumn(hList, 100, "Value", GUI_TA_CENTER);
    
    // 添加行
    const GUI_ConstString row1[] = {"Short Text", "Value1"};
    const GUI_ConstString row2[] = {"Long Text\nSecond Line", "Value2"};
    const GUI_ConstString row3[] = {"Very Long Text\nSecond Line\nThird Line", "Value3"};
    
    LISTVIEW_AddRow(hList, row1);
    LISTVIEW_AddRow(hList, row2);
    LISTVIEW_AddRow(hList, row3);
    
    // 设置每行的自定义行高
    LISTVIEW_SetRowHeightEx(hList, 0, 20);   // 第0行：20像素
    LISTVIEW_SetRowHeightEx(hList, 1, 35);   // 第1行：35像素（2行文本）
    LISTVIEW_SetRowHeightEx(hList, 2, 50);   // 第2行：50像素（3行文本）
    
    // 主循环
    while (1) {
        GUI_Delay(100);
    }
    
    return 0;
}
```

### 动态调整行高

```c
// 根据内容动态计算行高
int CalculateRowHeight(const char* text)
{
    int lines = 1;
    while (*text) {
        if (*text == '\n') lines++;
        text++;
    }
    return lines * 16 + 8; // 每行16像素 + 8像素边距
}

// 在添加行后设置行高
for (int i = 0; i < numRows; i++) {
    LISTVIEW_AddRow(hList, rowData[i]);
    
    // 计算并设置行高
    int height = CalculateRowHeight(rowData[i][0]); // 假设第一列是文本
    LISTVIEW_SetRowHeightEx(hList, i, height);
}
```

### 运行时修改行高

```c
// 响应按钮点击，增加行高
if (BUTTON_IsPressed(hBtnIncrease)) {
    for (int i = 0; i < LISTVIEW_GetNumRows(hList); i++) {
        unsigned currentHeight = LISTVIEW_GetRowHeight(hList, i);
        LISTVIEW_SetRowHeightEx(hList, i, currentHeight + 5);
    }
    WM_InvalidateWindow(hList);
}
```

## 实现原理

### 数据结构

在`LISTVIEW_Obj`结构体中添加了：
- `GUI_ARRAY RowHeightArray`: 存储每行的行高
- `unsigned DefaultRowHeight`: 默认行高

### 核心算法

1. **行高存储**：每行在`RowHeightArray`中存储一个`unsigned`值表示行高
2. **行高获取**：`LISTVIEW__GetRowDistY`函数根据行索引返回对应行高
3. **绘制计算**：在`_Paint`函数中，每行使用自己的行高进行绘制
4. **坐标计算**：在`_SetSelFromPos`函数中，根据像素位置和每行行高计算行索引

### 兼容性处理

- 如果某行没有设置行高，使用默认行高
- 如果没有设置默认行高，使用字体高度
- 保持原有的`RowDistY`机制作为备选方案

## 注意事项

1. **内存管理**：行高数组会在LISTVIEW删除时自动释放
2. **性能考虑**：可变行高会增加一些计算开销，但影响很小
3. **滚动条**：滚动条仍然按行滚动，每行视为一个项目
4. **网格线**：网格线绘制会考虑每行的实际行高

## 编译要求

- uC/GUI 3.0或更高版本
- 支持GUI_ARRAY功能
- 支持WM（窗口管理器）功能

## 测试

使用提供的测试文件`test/listViewVarHeight.c`来验证功能：

```bash
# 编译测试程序
gcc -o test_listview test/listViewVarHeight.c -I./GUI/Widget -L./ -lucgui

# 运行测试程序
./test_listview
```

## 故障排除

### 常见问题

1. **行高不生效**：确保在添加行后调用`LISTVIEW_SetRowHeightEx`
2. **显示异常**：检查行高值是否合理（建议在10-100像素之间）
3. **内存错误**：确保LISTVIEW句柄有效

### 调试技巧

- 使用`LISTVIEW_GetRowHeight`检查行高设置
- 在状态栏显示当前行高信息
- 使用`WM_InvalidateWindow`强制重绘

## 扩展功能

可以考虑的进一步改进：

1. **自动行高计算**：根据文本内容自动计算最佳行高
2. **行高动画**：支持行高的平滑过渡动画
3. **批量行高设置**：一次性设置多行的行高
4. **行高模板**：预定义的行高样式模板

## 许可证

本实现基于uC/GUI的许可证，请遵守相关条款。
