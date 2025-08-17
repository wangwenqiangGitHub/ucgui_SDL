# depens
```
sudo apt install libsdl1.2-dev

```

# test
```
cd test && mkdir build && cd build && make -j4
```

# build sigle file
```
gcc listViewVar.c -o listnew libucgui.a -IGUI_X -IGUI/Core -IGUI/Widget -IGUI/WM -lSDL
```

# uC/GUI代码结构
### 以LISTVIEW.c为例
uC/GUI的代码采用“模块化+面向对象模拟”设计，核心模拟包括:窗口管理(WM), 控件(WIDGET),绘图(LCD/GUI),字体/颜色等。以LISTVIEW.c为例，可看到典型的控件实现结构:
1. 数据结构设计
- 控件对象(LISTVIEW\_Obj):存储控件的所有属性和状态，如:
    - 视觉字体:字体(Props.pFont),颜色(Props.aBkColor),网格开关(ShowGrid);
    - 数据属性:行数据(RowArray),选中行(Sel),滚动状态(ScrollStateV/H);
    - 子控件关联:表头(hHeader).
    - (修改后新增)动态行高存储(RowHeights).
- 回掉函数(\_LISTVIEW\_Callback):处理窗口消息(如WM\_PAINT，WM\_TOUCH,WM\_KEY),是控件的"大脑"，决定如何响应用户操作和系统事件。

2.核心函数分工
- 创建函数(LISTVIEW\_CreateEx):初始化控件对象, 分配内存，设置默认属性(如默认字体，颜色)，关联子控件(如表头HEADER)
- 绘制函数（_Paint）：根据控件状态绘制外观，包括背景、文本、网格线等，是视觉呈现的核心。
事件处理函数：如 _OnTouch（处理触摸事件）、_AddKey（处理键盘事件），实现用户交互。
辅助函数：如 LISTVIEW__UpdateScrollParas（更新滚动参数）、LISTVIEW__InvalidateRow（刷新行区域），处理布局和刷新逻辑。
二、uC/GUI 的核心设计思想
1. “轻量化”：为嵌入式系统量身定制
按需裁剪：通过宏定义（如 GUI_WINSUPPORT 控制窗口支持，LISTVIEW_FONT_DEFAULT 定义默认字体）可关闭不需要的功能，减少内存占用。
高效绘图：绘图函数（如 GUI_DispStringInRect、LCD_FillRect）直接操作底层 LCD 驱动，避免冗余计算，适合 CPU 性能有限的场景。
小内存占用：控件对象仅存储必要属性，数据结构紧凑（如用数组 GUI_ARRAY 存储行数据，而非复杂链表）。
2. “硬件无关”：跨平台移植性
抽象层设计：绘图操作不直接依赖硬件，而是通过 LCD_xxx 函数（如 LCD_SetColor、LCD_FillRect）封装，移植时只需实现底层 LCD 驱动接口，上层代码无需修改。
窗口管理（WM）：将所有控件视为 “窗口（WM_HWIN）”，通过窗口句柄管理层级和消息，与具体硬件无关。
3. “控件化”：复用与扩展
基础控件封装：将常用 UI 元素（如按钮、列表、文本框）封装为独立控件，每个控件有自己的创建、绘制、事件处理函数，便于复用。
继承与组合：通过 “子窗口” 实现控件组合（如 LISTVIEW 包含 HEADER 作为表头），通过 WIDGET 结构体实现基础属性（如焦点、状态）的复用，类似面向对象的 “继承”。
4. “消息驱动”：事件响应机制
所有交互（触摸、键盘、刷新）通过 “消息（WM_MESSAGE）” 传递，控件通过回调函数处理消息（如 WM_PAINT 触发重绘，WM_TOUCH 触发选择行）。
这种机制使控件逻辑清晰，输入（消息）与输出（绘制）分离，便于扩展新事件（如自定义消息）。
三、从 LISTVIEW.c 看嵌入式 GUI 的实用思想
“够用就好” 的绘图逻辑：
绘制时先计算裁剪区域（ClipRect），只绘制可见部分（如 if (Rect.y1 < ClipRect.y0) continue），避免无效绘图浪费 CPU 资源 —— 这在嵌入式系统中至关重要。
滚动的 “懒计算”：
滚动参数（如可见行数、总高度）在需要时（LISTVIEW__UpdateScrollParas）才计算，而非实时更新，减少不必要的运算。
数据与显示分离：
行数据存储在 RowArray 中，绘制时从数组取数据，修改数据后只需刷新对应区域（LISTVIEW__InvalidateRow），而非重绘整个控件 —— 这是 GUI 性能优化的核心。
总结
uC/GUI 的代码本质是 “用 C 语言模拟面向对象”，通过结构体封装状态，用函数实现方法，以消息驱动交互，同时极致优化内存和性能，适应嵌入式系统的限制。理解它的设计，不仅能学会改控件（如动态行高），更能掌握 “在资源受限环境下做复杂 UI” 的核心思路：精简、分层、按需计算。
