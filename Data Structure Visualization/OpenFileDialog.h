#pragma once

#include <iostream>
#include <windows.h>
#include <commdlg.h>
#include <string.h>
#include <filesystem>
inline std::string ConvertToNarrowString(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

inline std::string OpenFileDialog() {
    OPENFILENAMEW ofn;
    wchar_t szFile[260];
    HWND hwnd = NULL;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 2;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn) == TRUE) {
        return ConvertToNarrowString(ofn.lpstrFile);
    }

    return "";
}

inline std::string GetNameFileDialog(std::string fileName) {
    std::filesystem::path FileName(fileName);
    std::string ans = FileName.filename().string();
    return ans;
}


inline std::wstring stringToWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

inline std::string getCurrentWorkingDirectory() {
    wchar_t buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    std::wstring wstr(buffer);
    std::string str(wstr.begin(), wstr.end());
    return str;
}

inline void setCurrentWorkingDirectory(const std::string& path) {
    std::wstring wpath = stringToWString(path);
    SetCurrentDirectory(wpath.c_str());
}