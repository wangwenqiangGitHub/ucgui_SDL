/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : FRAMEWIN.c
Purpose     : Implementation of framewindow widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN_Private.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

static unsigned int DEF_ICON_32X32[] = {
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0xb5a810, 0xcfb602, 0xd0b801, 0xd1ba02, 0xd1ba02, 
    0xd1b902, 0xd1b902, 0xd2ba02, 0xd0b603, 0xbaaa15, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0xc8b302, 0xd2b902, 0xd3bb02, 0xd5bc02, 0xd7bc02, 0xd5bc02, 0xd5bc01, 
    0xd5bd02, 0xd5bc02, 0xd7bc02, 0xd6bb01, 0xd3bb01, 0xd1b902, 0xcab602, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xbfaa01, 
    0xd0b901, 0xd3bb02, 0xd6bc01, 0xd6bc01, 0xd5bc01, 0xd4bc01, 0xd6bc01, 0xd6bc01, 
    0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd3bb02, 0xcfb901, 
    0xc2ae02, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcab203, 0xd1bc02, 
    0xd5bd02, 0xd7bd02, 0xd6bc01, 0xd5bc01, 0xd4bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 
    0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 
    0xd1bb02, 0xcbb502, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xcbb205, 0xd4bb02, 0xd6bc01, 
    0xd7bd02, 0xd7bd03, 0xd6bd04, 0xd5bc05, 0xd5bb05, 0xd6bc04, 0xd6bb06, 0xd6bb05, 
    0xd6bb05, 0xd6bb06, 0xd6bc04, 0xd6bb06, 0xd6bb05, 0xd6bc04, 0xd7bb02, 0xd6bb03, 
    0xd6bc01, 0xd3bb01, 0xcbb204, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0xc4b002, 0xd2bb01, 0xd6bc01, 0xd8bc02, 
    0xd6be26, 0xe4dcb3, 0xe2e0c8, 0xe3dfc8, 0xe3dfc8, 0xe3dfc8, 0xe2dfc8, 0xe2dfc8, 
    0xe2dfc8, 0xe2dfc8, 0xe2dfc8, 0xe2dfc8, 0xe2dfc8, 0xe2e0c8, 0xe2dab3, 0xd3bd24, 
    0xd7bc01, 0xd5bc01, 0xd4bc02, 0xc8b102, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0xb7a305, 0xd0ba01, 0xd6bb01, 0xd7bc01, 0xd8bc02, 
    0xd9c75f, 0xe4e6e3, 0xe5e6e4, 0xe5e6e2, 0xe4e4e1, 0xe4e3e1, 0xe3e4e1, 0xe3e3e1, 
    0xe3e4e1, 0xe3e4e1, 0xe3e3e1, 0xe3e4e1, 0xe4e5e3, 0xe5e6e5, 0xe7e6e5, 0xcabd5e, 
    0xd3b902, 0xd6bc01, 0xd6bd01, 0xd1b902, 0xb4a205, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0xcfb604, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd7bb02, 
    0xd8c863, 0xe6e6e4, 0xe6e5e5, 0xb3b0a6, 0x7c715b, 0x7d715b, 0x7f705c, 0x7f705b, 
    0x7e715a, 0x7d715a, 0x7e715a, 0x7d715a, 0xb2b0a3, 0xe5e5e6, 0xe6e6e4, 0xcaba61, 
    0xc6ad03, 0xd2ba03, 0xd4bd01, 0xd5bc01, 0xceb604, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0xbda707, 0xd3bb01, 0xd6bc01, 0xd6bd00, 0xd6bc01, 0xd7bb02, 
    0xd8c863, 0xe6e6e4, 0xe5e6e5, 0xa8a297, 0x7a6e54, 0x7a6e54, 0x7a6e54, 0x7a6e54, 
    0x7a6e54, 0x7a6e54, 0x7a6e54, 0x7a6e54, 0xa9a197, 0xe6e5e6, 0xe6e6e4, 0xcaba61, 
    0xc2ab04, 0xc7ae03, 0xd2ba03, 0xd7bc00, 0xd3bb02, 0xbba904, 0x000000, 0x000000, 
    0x000000, 0x000000, 0xceb604, 0xd5bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd7bb02, 
    0xd8c862, 0xe6e6e4, 0xe5e6e5, 0xa8a297, 0x7a6e54, 0x7a6e54, 0x7a6e54, 0x7a6e54, 
    0x7a6e54, 0x7a6e54, 0x7a6e54, 0x7a6e54, 0xa9a296, 0xe6e5e5, 0xe6e6e4, 0xcabb60, 
    0xc3ab05, 0xc3ac04, 0xc6b002, 0xd5ba02, 0xd5bc02, 0xccb602, 0x000000, 0x000000, 
    0x000000, 0x8c7f0e, 0xd3bb03, 0xd6bc01, 0xd7bc02, 0xd6bc01, 0xd6bc01, 0xd7bc02, 
    0xd8c862, 0xe6e6e4, 0xe5e6e5, 0xa8a297, 0x7a6e54, 0x7a6e54, 0x7a6e54, 0x7a6e54, 
    0x7a6e54, 0x7a6e54, 0x7a6e54, 0x7a6e54, 0xa8a196, 0xe5e5e5, 0xe6e6e4, 0xcabc5f, 
    0xc3ac05, 0xc3ad03, 0xc3ae03, 0xc8b202, 0xd2bb02, 0xd2ba02, 0x897c0c, 0x000000, 
    0x000000, 0xc2a709, 0xd5bc02, 0xd6bc01, 0xd8bb03, 0xd6bc01, 0xd6bc01, 0xd7bc02, 
    0xd8c861, 0xe6e6e4, 0xe5e6e5, 0xa9a399, 0x7a6d55, 0x7a6e55, 0x7a6e55, 0x7a6e55, 
    0x7a6e55, 0x7a6e55, 0x7a6e55, 0x7a6e55, 0xa9a399, 0xe4e5e5, 0xe6e6e4, 0xcbbc60, 
    0xc3ac04, 0xc3ad03, 0xc5ae04, 0xc6b102, 0xcab303, 0xd4ba03, 0xc1a805, 0x000000, 
    0x000000, 0xcdb103, 0xd6bc02, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd7bc01, 
    0xd8c861, 0xe6e6e4, 0xe6e5e5, 0xdddbd8, 0xcbc7c1, 0xcbc8c1, 0xc9c8c2, 0xc9c8c2, 
    0xc9c8c2, 0xc9c8c2, 0xc9c8c1, 0xc9c8c1, 0xdbd9d7, 0xe5e5e5, 0xe6e6e4, 0xcbbc5f, 
    0xc4ad05, 0xc6ae03, 0xc7b002, 0xc8b002, 0xc8b003, 0xcbb404, 0xc4af03, 0x000000, 
    0x000000, 0xccb404, 0xd6bd01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc02, 
    0xd4c03a, 0xe6e2cf, 0xe7e5df, 0xe6e6de, 0xe5e6de, 0xe7e5df, 0xe7e6de, 0xe6e6de, 
    0xe6e5de, 0xe7e6de, 0xe7e6dd, 0xe7e5dd, 0xe6e5dd, 0xe7e5dd, 0xe4e2cd, 0xc5b338, 
    0xc5ae03, 0xc6af03, 0xc6b102, 0xc9b104, 0xc9b202, 0xc9b202, 0xc0aa05, 0x000000, 
    0x000000, 0xc9b304, 0xd6bb03, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd7bc01, 
    0xd8bc04, 0xceb823, 0xc1ae38, 0xbfac38, 0xc1ac39, 0xc1ad3a, 0xc2ae3a, 0xc2ae39, 
    0xc1af38, 0xc2af38, 0xc3b038, 0xc4b138, 0xc5b238, 0xc6b339, 0xc4af26, 0xc5ae04, 
    0xc6ae04, 0xc7af03, 0xc8b103, 0xc9b203, 0xc9b202, 0xcab301, 0xc0ac08, 0x000000, 
    0x000000, 0xc9b303, 0xd6bb03, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd5bd01, 
    0xdecd68, 0xfbf9e6, 0xfefef4, 0xfefdf5, 0xfffdf6, 0xfefef5, 0xfefef5, 0xfefef5, 
    0xfefef4, 0xfefef4, 0xfefef4, 0xfefef4, 0xfffef4, 0xfefdf5, 0xfaf9eb, 0xd4c67b, 
    0xc4ad04, 0xc8b003, 0xc9b103, 0xc9b202, 0xcab302, 0xcbb303, 0xc0ac07, 0x000000, 
    0x000000, 0xc9b203, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc02, 
    0xede6b6, 0xfeffff, 0xfffffe, 0xd9d5ce, 0xb9b2a5, 0xb9b1a2, 0xb9b1a2, 0xb9b1a2, 
    0xb9b1a2, 0xb9b1a2, 0xb9b1a2, 0xb9b1a2, 0xd9d6ce, 0xfffffd, 0xfeffff, 0xe7e1c7, 
    0xbca404, 0xc8b102, 0xc9b202, 0xcab303, 0xcab402, 0xcab402, 0xc1aa07, 0x000000, 
    0x000000, 0xc3ab05, 0xd7bc02, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd4bc08, 
    0xf7f4dc, 0xfeffff, 0xfefefe, 0xa09480, 0x8c7d5f, 0x8a7d5f, 0x8c7d5f, 0x8c7d5f, 
    0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x9f9480, 0xfdfffd, 0xffffff, 0xf6f4e8, 
    0xaf9a12, 0xc7b002, 0xc9b403, 0xccb402, 0xcbb402, 0xcbb303, 0xbca506, 0x000000, 
    0x000000, 0xb09a07, 0xd4bc02, 0xd5bc01, 0xd6bc01, 0xd6bc01, 0xd5bc01, 0xd6c23a, 
    0xfffef7, 0xffffff, 0xf8f6f3, 0x8f8266, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 
    0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8e8167, 0xf7f6f3, 0xffffff, 0xfffdfb, 
    0xb7a959, 0xc3ae02, 0xcab402, 0xccb402, 0xcdb503, 0xccb502, 0xa99408, 0x000000, 
    0x000000, 0x665a04, 0xd0b704, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xe1d384, 
    0xfffffe, 0xffffff, 0xe8e5e0, 0x8b7d5f, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 
    0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8c7d5f, 0x8b7d60, 0xe8e5e1, 0xffffff, 0xfffffe, 
    0xcdc497, 0xbfa903, 0xcab402, 0xcdb502, 0xceb602, 0xc9b204, 0x635805, 0x000000, 
    0x000000, 0x000000, 0xc7ae05, 0xd7bc02, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xece3b3, 
    0xffffff, 0xffffff, 0xd6d3cd, 0x8b7d5e, 0x8b7d5f, 0x8b7d5f, 0x8b7d5f, 0x8b7d5f, 
    0x8b7d5f, 0x8b7d5f, 0x8b7d5f, 0x8b7d5f, 0x8c7d5f, 0xd7d3cc, 0xffffff, 0xffffff, 
    0xe1ddc3, 0xbba404, 0xcbb402, 0xcdb601, 0xcdb602, 0xbfa907, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x9a8a04, 0xd0bb02, 0xd6bc01, 0xd6bc01, 0xd5bb03, 0xf7f2d9, 
    0xffffff, 0xffffff, 0xf5f4f2, 0xd6d2ca, 0xd5d0c9, 0xd4d1c9, 0xd5d0c9, 0xd4d1c9, 
    0xd4d1c9, 0xd5d0c9, 0xd4d1c9, 0xd5d0c9, 0xd5d1ca, 0xf5f5f1, 0xffffff, 0xffffff, 
    0xf3f3e4, 0xb09e0a, 0xccb303, 0xcdb601, 0xcab603, 0x978707, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0xc1ac07, 0xd6bb03, 0xd6bc01, 0xd4bc02, 0xf4f0d1, 
    0xfffefc, 0xfffefc, 0xfefffc, 0xfefefb, 0xfffefc, 0xfffefc, 0xfffefb, 0xfffefb, 
    0xfffefc, 0xfffdfc, 0xfffefc, 0xfffefb, 0xfefefb, 0xfefffb, 0xfffefc, 0xfffffc, 
    0xf2efdc, 0xad9a13, 0xc9b203, 0xcdb601, 0xbca806, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x796b03, 0xceb603, 0xd6bc01, 0xd5bb02, 0xceb722, 
    0xb9ab55, 0xb1a257, 0xb1a356, 0xb1a357, 0xb2a357, 0xb2a457, 0xb2a456, 0xb3a556, 
    0xb3a557, 0xb4a558, 0xb5a657, 0xb5a758, 0xb5a758, 0xb6a759, 0xb7a759, 0xb7a858, 
    0xaa982d, 0xb29f01, 0xcbb403, 0xc7b004, 0x756802, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x9d9006, 0xd1b803, 0xd6bc01, 0xd5bb00, 
    0xcab500, 0xb9a604, 0xb9a304, 0xbaa404, 0xbba504, 0xbca604, 0xbca604, 0xbda704, 
    0xbda704, 0xbea704, 0xbfa903, 0xbfa903, 0xc1aa03, 0xc3ac02, 0xc2ad00, 0xc3ac01, 
    0xc4ad02, 0xc7b202, 0xc9b303, 0x988d05, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x010000, 0xa59206, 0xd0b903, 0xd5bc01, 
    0xd5bc01, 0xd2b904, 0xc6af04, 0xc4ae03, 0xc5af03, 0xc6b004, 0xc6b004, 0xc8b104, 
    0xc9b103, 0xc9b103, 0xc8b403, 0xcab303, 0xccb403, 0xccb502, 0xcbb601, 0xccb503, 
    0xcdb503, 0xcab205, 0xa38f08, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x010000, 0x9a8c07, 0xcdb403, 
    0xd6bc01, 0xd6bc01, 0xd3ba03, 0xc7b101, 0xc8af02, 0xc8b002, 0xc9b103, 0xc9b203, 
    0xc9b202, 0xcab302, 0xcab402, 0xccb402, 0xcdb602, 0xcdb601, 0xcdb601, 0xccb603, 
    0xc6af04, 0x968806, 0x010000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x716201, 
    0xc0a806, 0xd1b904, 0xd5bd01, 0xd3bb01, 0xcbb203, 0xc9b104, 0xc9b202, 0xc9b202, 
    0xc9b302, 0xcbb402, 0xccb402, 0xcbb402, 0xccb602, 0xceb602, 0xcbb405, 0xb9a507, 
    0x6a5e01, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x867c04, 0xbdab04, 0xccb703, 0xd1b902, 0xcbb204, 0xc8b203, 0xcab202, 
    0xccb302, 0xccb401, 0xcdb402, 0xcbb603, 0xc6b003, 0xb8a405, 0x887707, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x473f02, 0x958706, 0xb09d06, 0xb6a008, 0xbaa405, 
    0xbaa405, 0xb7a206, 0xaf9a08, 0x8f8309, 0x433a02, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
};

static unsigned int DEF_ICON_16X16[] = {
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xd0b701, 0xd1b903,
    0xd0b903, 0xd1b802, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0xb9a503, 0xd1b902, 0xd4bb01, 0xd5bc01, 0xd6bc01,
    0xd6bc01, 0xd6bc01, 0xd4bb01, 0xd1ba02, 0xbba905, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0xcbb206, 0xd4bb02, 0xd7bd02, 0xd6bc02, 0xd6bc02, 0xd6bc02,
    0xd6bc02, 0xd6bc02, 0xd6bc02, 0xd6bb01, 0xd3bb01, 0xcbb106, 0x000000, 0x000000,
    0x000000, 0xaa9804, 0xd2ba01, 0xd7bc01, 0xddd29d, 0xe3e2d6, 0xe4e2d6, 0xe3e2d6,
    0xe2e2d6, 0xe3e2d6, 0xe3e2d6, 0xd9cf9e, 0xd5bb01, 0xd3bb01, 0xa99904, 0x000000,
    0x000000, 0xd1b802, 0xd6bc01, 0xd7bc01, 0xdfd8b3, 0xcbc8c4, 0x7a6e55, 0x7b6d55,
    0x7a6e55, 0x7a6e55, 0xcac8c4, 0xd8d1b3, 0xc8b004, 0xd5bc01, 0xcfb803, 0x000000,
    0x0e1100, 0xd4bb02, 0xd6bc01, 0xd7bc01, 0xdfd8b3, 0xc8c6c1, 0x7a6e54, 0x7a6e54,
    0x7a6e54, 0x7a6e54, 0xc8c5c1, 0xd9d2b2, 0xc3ac04, 0xcab302, 0xd2ba02, 0x150f00,
    0xcbae05, 0xd6bc01, 0xd6bc01, 0xd7bc01, 0xdfd8b2, 0xd5d4d1, 0xa9a398, 0xa8a398,
    0xa8a398, 0xa8a398, 0xd4d3d1, 0xd9d2b2, 0xc4ad04, 0xc7b002, 0xccb403, 0xc5ae04,
    0xc9b204, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xd8c673, 0xd5cca7, 0xd5cca7, 0xd5cca7,
    0xd5cda7, 0xd6cda6, 0xd8cea6, 0xcdbf72, 0xc6ae03, 0xc8b103, 0xc9b202, 0xbeaa07,
    0xc7b104, 0xd6bc01, 0xd6bc01, 0xd6bc01, 0xf2eccc, 0xf6f5f0, 0xdedbd2, 0xdedbd1,
    0xdedbd1, 0xdedbd1, 0xf6f5f0, 0xeeead3, 0xc4ad03, 0xc9b203, 0xcab402, 0xbeaa08,
    0xbea507, 0xd5bc01, 0xd6bc01, 0xd5bd15, 0xfdfdf5, 0xd1cdc5, 0x8b7d5f, 0x8c7d5f,
    0x8c7d5f, 0x8c7d5f, 0xd0cdc5, 0xfdfcf9, 0xbca828, 0xcbb402, 0xccb402, 0xb7a007,
    0x0d0600, 0xd2b803, 0xd6bc01, 0xdecc72, 0xffffff, 0xbcb5a9, 0x8c7d5f, 0x8c7d5f,
    0x8c7d5f, 0x8c7d5f, 0xbcb5a9, 0xffffff, 0xcabd80, 0xccb502, 0xcab203, 0x0d0600,
    0x000000, 0xc5b103, 0xd6bc02, 0xe5d89d, 0xfffffe, 0xf3f2ef, 0xeceae6, 0xeceae6,
    0xeceae6, 0xeceae6, 0xf3f2ef, 0xfffffe, 0xd4cca5, 0xccb502, 0xc0ac04, 0x000000,
    0x000000, 0x645803, 0xcfb603, 0xd3ba09, 0xbba936, 0xb4a236, 0xb5a337, 0xb6a436,
    0xb7a537, 0xb9a737, 0xbba838, 0xbda938, 0xbaa60f, 0xc6b003, 0x5f5501, 0x000000,
    0x000000, 0x000000, 0x9b8705, 0xceb503, 0xd5bb02, 0xc9b203, 0xc7b002, 0xc8b103,
    0xc9b203, 0xcab402, 0xcdb502, 0xccb602, 0xc7af04, 0x998507, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x5a4e00, 0xc2ab05, 0xceb802, 0xccb403, 0xc9b202,
    0xcbb402, 0xccb502, 0xc8b203, 0xbca806, 0x554b00, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x080500, 0xa49406, 0xb39d06,
    0xb39e05, 0xa29009, 0x070300, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
};

/******************************************************************
*
*        Config defaults
*
*******************************************************************
*/

/* Support for 3D effects */
#ifndef FRAMEWIN_CLIENTCOLOR_DEFAULT
  #define FRAMEWIN_CLIENTCOLOR_DEFAULT 0xc0c0c0
#endif

/* Default for top frame size */
#ifndef FRAMEWIN_TITLEHEIGHT_DEFAULT
  #define FRAMEWIN_TITLEHEIGHT_DEFAULT 0
#endif

/* Default for left/right/top/bottom frame size */
#ifndef FRAMEWIN_BORDER_DEFAULT
  #define FRAMEWIN_BORDER_DEFAULT 3
#endif

/* Default for inner frame size */
#ifndef FRAMEWIN_IBORDER_DEFAULT
  #define FRAMEWIN_IBORDER_DEFAULT 1
#endif

/* Default font */
#ifndef FRAMEWIN_DEFAULT_FONT
  #define FRAMEWIN_DEFAULT_FONT &GUI_Font8_1
#endif

/* Default barcolor when framewin is active */
#ifndef FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT
  #define FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT 0xFF0000
#endif

/* Default barcolor when framewin is inactive */
#ifndef FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT
  #define FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT 0x404040
#endif

/* Default framecolor */
#ifndef FRAMEWIN_FRAMECOLOR_DEFAULT
  #define FRAMEWIN_FRAMECOLOR_DEFAULT 0xAAAAAA
#endif

/* Default textcolor when framewin is active */
#ifndef FRAMEWIN_TEXTCOLOR0_DEFAULT
  #define FRAMEWIN_TEXTCOLOR0_DEFAULT GUI_WHITE
#endif

/* Default textcolor when framewin is inactive */
#ifndef FRAMEWIN_TEXTCOLOR1_DEFAULT
  #define FRAMEWIN_TEXTCOLOR1_DEFAULT GUI_WHITE
#endif

/*********************************************************************
*
*       public data, defaults (internal use only)
*
**********************************************************************
*/

FRAMEWIN_PROPS FRAMEWIN__DefaultProps = {
  FRAMEWIN_DEFAULT_FONT,
  FRAMEWIN_BARCOLOR_INACTIVE_DEFAULT,
  FRAMEWIN_BARCOLOR_ACTIVE_DEFAULT,
  FRAMEWIN_TEXTCOLOR0_DEFAULT,
  FRAMEWIN_TEXTCOLOR1_DEFAULT,
  FRAMEWIN_CLIENTCOLOR_DEFAULT,
  FRAMEWIN_TITLEHEIGHT_DEFAULT,
  FRAMEWIN_BORDER_DEFAULT,
  FRAMEWIN_IBORDER_DEFAULT
};

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static I16 FRAMEWIN__MinVisibility = 5;

/*********************************************************************
*
*           Static routines
*
**********************************************************************
*/

/*********************************************************************
*
*       _SetActive
*/
static void _SetActive(FRAMEWIN_Handle hObj, int State) {
  FRAMEWIN_Obj* pObj;
  pObj = FRAMEWIN_H2P(hObj);
  if        (State && !(pObj->Flags & FRAMEWIN_SF_ACTIVE)) {
    pObj->Flags |= FRAMEWIN_CF_ACTIVE;
    FRAMEWIN_Invalidate(hObj);
  } else if (!State && (pObj->Flags & FRAMEWIN_SF_ACTIVE)) {
    pObj->Flags &= ~FRAMEWIN_CF_ACTIVE;
    FRAMEWIN_Invalidate(hObj);
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(FRAMEWIN_Handle hWin, FRAMEWIN_Obj* pObj, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState;
  pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      if (!(pObj->Flags & FRAMEWIN_SF_ACTIVE)) {
        WM_SetFocus(hWin);
      }
      WM_BringToTop(hWin);
      if (pObj->Flags & FRAMEWIN_SF_MOVEABLE) {
        WM_SetCaptureMove(hWin, pState, FRAMEWIN__MinVisibility);
      }
    }
  }
}

/*********************************************************************
*
*       _Paint  (Frame)
*
*/
static void _Paint(FRAMEWIN_Obj* pObj) {
  WM_HWIN hWin = WM_GetActiveWindow();
  const char* pText = NULL;
  int xsize = WM_GetWindowSizeX(hWin);
  int ysize = WM_GetWindowSizeY(hWin);
  int BorderSize = pObj->Props.BorderSize;
  int y0, Index;
  POSITIONS Pos;
  GUI_RECT r, rText;

  /* Perform computations */
  FRAMEWIN__CalcPositions(pObj, &Pos);
  Index = (pObj->Flags & FRAMEWIN_SF_ACTIVE) ? 1 : 0;

  if (pObj->hText) {
    pText = (const char*) GUI_ALLOC_h2p(pObj->hText);
  }
  r.x0 = Pos.rClient.x0;
  r.x1 = Pos.rClient.x1;
  r.y0 = Pos.rTitleText.y0;
  r.y1 = Pos.rTitleText.y1;
  Pos.rTitleText.y0++;
  Pos.rTitleText.x0++;
  Pos.rTitleText.x1--;
  GUI_SetFont(pObj->Props.pFont);
  GUI__CalcTextRect(pText, &Pos.rTitleText, &rText, pObj->TextAlign);
  y0 = Pos.TitleHeight + BorderSize;

  /* Perform drawing operations */
  WM_ITERATE_START(NULL) {
    /* Draw Title */
    LCD_SetBkColor(pObj->Props.aBarColor[Index]);
    LCD_SetColor(pObj->Props.aTextColor[Index]);
    WIDGET__FillStringInRect(pText, &r, &Pos.rTitleText, &rText);
    /* Draw Frame */
    LCD_SetColor(FRAMEWIN_FRAMECOLOR_DEFAULT);
    GUI_FillRect(0, 0, xsize-1, BorderSize-1);
	  GUI_FillRect(0, 0, Pos.rClient.x0-1, ysize-1);
	  GUI_FillRect(Pos.rClient.x1+1, 0, xsize-1, ysize-1);
    GUI_FillRect(0, Pos.rClient.y1+1, xsize-1, ysize-1);
    GUI_FillRect(0, y0, xsize - 1, y0 + pObj->Props.IBorderSize - 1);
    /* Draw the 3D effect (if configured) */
    if (pObj->Props.BorderSize >= 2) {
      WIDGET_EFFECT_3D_DrawUp();  /* pObj->Widget.pEffect->pfDrawUp(); */
    }
    if (pObj->Flags & FRAMEWIN_SF_ICON16) {
      int x = 0;
      int y = 0;
      int idx = 0;
      unsigned int v = 0;

      for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
          v = DEF_ICON_16X16[idx++];
          if (v) {
            GUI_SetColor(v);
            GUI_DrawPixel(x + BorderSize + 1, y + BorderSize + 1);
          }
        }
      }
    }

  } WM_ITERATE_END();


}

/*********************************************************************
*
*       _OnChildHasFocus
*
* Function:
*   A child has received or lost the focus.
*   The basic idea is to make sure the framewindow is active if a
*   descendant has the focus.
*   If the focus travels from one desc. to an other, there is no need
*   to make the framewindow inactive and active again.
*   Avoiding this complicates the code a litlle, but avoids flicker
*   and waste of CPU load.
*   
*/
static void _OnChildHasFocus(FRAMEWIN_Handle hWin, FRAMEWIN_Obj* pObj, WM_MESSAGE *pMsg) {
  if (pMsg->Data.p) {
    const WM_NOTIFY_CHILD_HAS_FOCUS_INFO * pInfo = (const WM_NOTIFY_CHILD_HAS_FOCUS_INFO *)pMsg->Data.p;
    int IsDesc = WM__IsAncestorOrSelf(pInfo->hNew, hWin);
    if (IsDesc) {                         /* A child has received the focus, Framewindow needs to be activated */
      _SetActive(hWin, 1);
    } else {                  /* A child has lost the focus, we need to deactivate */
      _SetActive(hWin, 0);
      /* Remember the child which had the focus so we can reactive this child */
      if (WM__IsAncestor(pInfo->hOld, hWin)) {
        pObj->hFocussedChild = pInfo->hOld;
      }
    }
  }
}

/*********************************************************************
*
*       Framewin Callback
*/
static void _FRAMEWIN_Callback (WM_MESSAGE *pMsg) {
  FRAMEWIN_Handle hWin = (FRAMEWIN_Handle)(pMsg->hWin);
  FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hWin);
  GUI_RECT* pRect = (GUI_RECT*)(pMsg->Data.p);
  POSITIONS Pos;
  GUI_HOOK* pHook;
  /* Call hook functions */
  for (pHook = pObj->pFirstHook; pHook; pHook = pHook->pNext) {
    int r;
    r = (*pHook->pHookFunc)(pMsg);
    if (r) {
      return;   /* Message handled */
    }
  }
  switch (pMsg->MsgId) {
  case WM_HANDLE_DIALOG_STATUS:
    if (pMsg->Data.p) {                           /* set pointer to Dialog status */
      pObj->pDialogStatus = (WM_DIALOG_STATUS*)pMsg->Data.p;
    } else {                                      /* return pointer to Dialog status */
      pMsg->Data.p = pObj->pDialogStatus;      
    }
    return;
  case WM_PAINT:
    _Paint(pObj);
    break;
  case WM_TOUCH:
    _OnTouch(hWin, pObj, pMsg);
    return;                       /* Return here ... Message handled */
  case WM_GET_INSIDE_RECT:
    FRAMEWIN__CalcPositions(pObj, &Pos);
		*pRect = Pos.rClient;
    return;                       /* Return here ... Message handled */
  case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
    pMsg->Data.v = (int)pObj->hClient;
    return;                       /* Return here ... Message handled */
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
      WM_MESSAGE Msg;
      Msg.hWinSrc = hWin;
      Msg.Data    = pMsg->Data;
      Msg.MsgId   = WM_NOTIFY_PARENT_REFLECTION;
      WM_SendMessage(pMsg->hWinSrc, &Msg);
    }
    return;
  case WM_SET_FOCUS:                 /* We have received or lost focus */
    if (pMsg->Data.v == 1) {
      if (WM_IsWindow(pObj->hFocussedChild)) {
        WM_SetFocus(pObj->hFocussedChild);
      } else {
        pObj->hFocussedChild = WM_SetFocusOnNextChild(pObj->hClient);
      }
      FRAMEWIN_SetActive(hWin, 1);
      pMsg->Data.v = 0;              /* Focus could be accepted */
    } else {
      FRAMEWIN_SetActive(hWin, 0);
    }
    return;
  case WM_TOUCH_CHILD:
    /* If a child of this framewindow has been touched and the frame window was not active,
       the framewindow will receive the focus.
     */
    if (!(pObj->Flags & FRAMEWIN_SF_ACTIVE)) {
      const WM_MESSAGE * pMsgOrg;
      const GUI_PID_STATE * pState;
      pMsgOrg = (const WM_MESSAGE*)pMsg->Data.p;      /* The original touch message */
      pState = (const GUI_PID_STATE*)pMsgOrg->Data.p;
      if (pState) {          /* Message may not have a valid pointer (moved out) ! */
        if (pState->Pressed) {
          WM_SetFocus(hWin);
        }
      }
    }
    break;
  case WM_NOTIFY_CHILD_HAS_FOCUS:
    _OnChildHasFocus(hWin, pObj, pMsg);
    break;
  case WM_DELETE:
    GUI_DEBUG_LOG("FRAMEWIN: _FRAMEWIN_Callback(WM_DELETE)\n");
    GUI_ALLOC_FreePtr(&pObj->hText);
    break;
  }
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hWin, pMsg) == 0) {
    return;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Client Callback
*/
static void FRAMEWIN__cbClient(WM_MESSAGE* pMsg) {
  WM_HWIN hWin    = pMsg->hWin;
  WM_HWIN hParent = WM_GetParent(pMsg->hWin);
  FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hParent);
  WM_CALLBACK* cb = pObj->cb;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    if (pObj->Props.ClientColor != GUI_INVALID_COLOR) {
      LCD_SetBkColor(pObj->Props.ClientColor);
      GUI_Clear();
    }
    /* Give the user callback  a chance to draw.
     * Note that we can not run into the bottom part, as this passes the parents handle
     */
    if (cb) {
	    WM_MESSAGE Msg;
      Msg      = *pMsg;
      Msg.hWin = hWin;
      (*cb)(&Msg);
    }
    return;
  case WM_SET_FOCUS:
    if (pMsg->Data.v) {     /* Focus received */
      if (pObj->hFocussedChild && (pObj->hFocussedChild != hWin)) {
        WM_SetFocus(pObj->hFocussedChild);
      } else {
        pObj->hFocussedChild = WM_SetFocusOnNextChild(hWin);
      }
      pMsg->Data.v = 0;     /* Focus change accepted */
    }
    return;
  case WM_GET_ACCEPT_FOCUS:
    WIDGET_HandleActive(hParent, pMsg);
    return;
  case WM_KEY:
    if (((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt > 0) {
      int Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
      switch (Key) {
      case GUI_KEY_TAB:
        pObj->hFocussedChild = WM_SetFocusOnNextChild(hWin);
        return;
      }
    }
    break;	                       /* Send to parent by not doing anything */
  case WM_GET_BKCOLOR:
    pMsg->Data.Color = pObj->Props.ClientColor;
    return;                       /* Message handled */
  case WM_GET_INSIDE_RECT:        /* This should not be passed to parent ... (We do not want parents coordinates)*/
  case WM_GET_ID:                 /* This should not be passed to parent ... (Possible recursion problem)*/
  case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
    WM_DefaultProc(pMsg);
    return;                       /* We are done ! */
  }
  /* Call user callback. Note that the user callback gets the handle of the Framewindow itself, NOT the Client. */
  if (cb) {
    pMsg->hWin = hParent;
    (*cb)(pMsg);
  } else {
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*        Exported module-internal routines:
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN__CalcTitleHeight
*/
int FRAMEWIN__CalcTitleHeight(FRAMEWIN_Obj* pObj) {
  int r = 0;
  if (pObj->Widget.State & FRAMEWIN_SF_TITLEVIS) {
    r = pObj->Props.TitleHeight;
    if (r == 0) {
      r = 2 + GUI_GetYSizeOfFont(pObj->Props.pFont);
    }
  }
  return r;
}

/*********************************************************************
*
*       FRAMEWIN__CalcPositions
*/
void FRAMEWIN__CalcPositions(FRAMEWIN_Obj* pObj, POSITIONS* pPos) {
  WM_HWIN hChild;
  WM_Obj* pChild;
  int TitleHeight;
  int MenuHeight = 0;
  int IBorderSize = 0;
  int BorderSize;
  int xsize, ysize;
  int x0, x1, y0;
  BorderSize = pObj->Props.BorderSize;
  xsize = WM__GetWindowSizeX(&pObj->Widget.Win);
  ysize = WM__GetWindowSizeY(&pObj->Widget.Win);
  if (pObj->Widget.State & FRAMEWIN_SF_TITLEVIS) {
    IBorderSize = pObj->Props.IBorderSize;
  }
  TitleHeight = FRAMEWIN__CalcTitleHeight(pObj);
  if (pObj->hMenu) {
    MenuHeight = WM_GetWindowSizeY(pObj->hMenu);
  }
  pPos->TitleHeight = TitleHeight;
  pPos->MenuHeight  = MenuHeight;
  /* Set object properties accordingly */
  pPos->rClient.x0  =         BorderSize;
  pPos->rClient.x1  = xsize - BorderSize - 1;
  pPos->rClient.y0  =         BorderSize + IBorderSize + TitleHeight + MenuHeight;
  pPos->rClient.y1  = ysize - BorderSize - 1;
  /* Calculate title rect */
  pPos->rTitleText.x0 =         BorderSize;
  pPos->rTitleText.x1 = xsize - BorderSize - 1;
  pPos->rTitleText.y0 =         BorderSize;
  pPos->rTitleText.y1 =         BorderSize + TitleHeight - 1;
  /* Iterate over all children */
  for (hChild = pObj->Widget.Win.hFirstChild; hChild; hChild = pChild->hNext) {
    pChild = WM_H2P(hChild);
    x0 = pChild->Rect.x0 - pObj->Widget.Win.Rect.x0;
    x1 = pChild->Rect.x1 - pObj->Widget.Win.Rect.x0;
    y0 = pChild->Rect.y0 - pObj->Widget.Win.Rect.y0;
    if (y0 == BorderSize) {
      if (pChild->Status & WM_SF_ANCHOR_RIGHT) {
        if (x0 <= pPos->rTitleText.x1) {
          pPos->rTitleText.x1 = x0 - 1;
        }
      } else {
        if (x1 >= pPos->rTitleText.x0) {
          pPos->rTitleText.x0 = x1 + 1;
        }
      }
    }
  }

  if (pObj->Flags & FRAMEWIN_SF_ICON16) {
    pPos->rTitleText.x0 += 16 + 2;
  }
}

/*********************************************************************
*
*       FRAMEWIN__UpdatePositions
*/
void FRAMEWIN__UpdatePositions(FRAMEWIN_Obj* pObj) {
  /* Move client window accordingly */
  if (pObj->hClient || pObj->hMenu) {
    POSITIONS Pos;
    FRAMEWIN__CalcPositions(pObj, &Pos);
    if (pObj->hClient) {
      WM_MoveChildTo(pObj->hClient, Pos.rClient.x0, Pos.rClient.y0);
      WM_SetSize(pObj->hClient, 
                 Pos.rClient.x1 - Pos.rClient.x0 + 1, 
                 Pos.rClient.y1 - Pos.rClient.y0 + 1);
    }
    if (pObj->hMenu) {
      WM_MoveChildTo(pObj->hMenu, Pos.rClient.x0, Pos.rClient.y0 - Pos.MenuHeight);
    }
  }
}

/*********************************************************************
*
*        Exported API routines:  Create
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_CreateEx
*/
FRAMEWIN_Handle FRAMEWIN_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                  int WinFlags, int ExFlags, int Id, const char* pTitle, WM_CALLBACK* cb)
{
  FRAMEWIN_Handle hObj;
  /* Create the window */
  WinFlags |= WM_CF_LATE_CLIP;    /* Always use late clipping since widget is optimized for it. */
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _FRAMEWIN_Callback,
                                sizeof(FRAMEWIN_Obj) - sizeof(WM_Obj));

  if (WinFlags & FRAMEWIN_SF_ICON16) {
    ExFlags |= FRAMEWIN_SF_ICON16;
  }
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    POSITIONS Pos;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE | FRAMEWIN_SF_TITLEVIS);
    /* init member variables */
    pObj->Props = FRAMEWIN__DefaultProps;
    pObj->TextAlign      = GUI_TA_LEFT;
    pObj->cb             = cb;
    pObj->Flags          = ExFlags;
    pObj->hFocussedChild = 0;
    pObj->hMenu          = 0;
    pObj->pFirstHook     = NULL;
    FRAMEWIN__CalcPositions(pObj, &Pos);
    pObj->hClient = WM_CreateWindowAsChild(Pos.rClient.x0,Pos.rClient.y0,
                                           Pos.rClient.x1 - Pos.rClient.x0 +1,
                                           Pos.rClient.y1 - Pos.rClient.y0 +1,
                                           hObj, 
                                           WM_CF_ANCHOR_RIGHT | WM_CF_ANCHOR_LEFT | WM_CF_ANCHOR_TOP | WM_CF_ANCHOR_BOTTOM | WM_CF_SHOW | WM_CF_LATE_CLIP, 
                                           FRAMEWIN__cbClient, 0);
    /* Normally we disable memory devices for the frame window:
     * The frame window does not flicker, and not using memory devices is usually faster.
     * You can still use memory by explicitly specifying the flag
     */
    if ((WinFlags & (WM_CF_MEMDEV | (WM_CF_MEMDEV_ON_REDRAW))) == 0) {
      WM_DisableMemdev(hObj);
    }
    FRAMEWIN_SetText(hObj, pTitle);
    GUI_UNLOCK();
  }
  return hObj;
}

/*********************************************************************
*
*        Exported routines:  Set Properties
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_SetText
*/
void FRAMEWIN_SetText(FRAMEWIN_Handle hObj, const char* s) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (GUI__SetText(&pObj->hText, s)) {
      FRAMEWIN_Invalidate(hObj);
    }
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_SetTextAlign
*/
void FRAMEWIN_SetTextAlign(FRAMEWIN_Handle hObj, int Align) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (pObj->TextAlign != Align) {
      pObj->TextAlign = Align;
      FRAMEWIN_Invalidate(hObj);
    }
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_SetMoveable
*/
void FRAMEWIN_SetMoveable(FRAMEWIN_Handle hObj, int State) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (State) {
      pObj->Flags |= FRAMEWIN_CF_MOVEABLE;
    } else {
      pObj->Flags &= ~FRAMEWIN_CF_MOVEABLE;
    }
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_SetActive
*/
void FRAMEWIN_SetActive(FRAMEWIN_Handle hObj, int State) {
  if (hObj) {
    WM_LOCK();
    _SetActive(hObj, State);
    WM_UNLOCK();
  }
}

#else
  void WIDGET_FrameWin(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
