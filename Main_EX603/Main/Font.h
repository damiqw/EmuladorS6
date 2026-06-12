#pragma once

int ReadFontFile(char* path);
void InitFont();
void ReloadFont();
HFONT FontNormal();
HFONT FontBool();
HFONT FontBig();
HFONT FontFixed();

extern int FontSize;