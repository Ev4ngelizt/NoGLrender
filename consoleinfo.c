#include <windows.h>
#include <stdio.h>
void setConsoleFont() {
    CONSOLE_FONT_INFOEX cfi;    
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 4; // largeur du caractère
    cfi.dwFontSize.Y = 4; // hauteur du caractère
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
int main() {
    setConsoleFont();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    while(1){
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
        printf("Console visible: %d x %d\n", cols, rows);
    }
    return 0;
}
