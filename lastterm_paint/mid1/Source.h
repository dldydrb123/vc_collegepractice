#pragma once

#include <windows.h>
#include <cmath>

void DrawRect(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawCircle(HWND hWnd, HDC hdc, int radius, POINT center);

void DrawBonobono(HWND hWnd, HDC hdc, int blink);

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);