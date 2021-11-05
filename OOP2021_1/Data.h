#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Borland.h"
using namespace std;

static void saveMapdata(const char* data,int sz)
{
    string dt="";
    dt.append(data);
    char from = '\xdb';
    char to = '1';
    replace(dt.begin(), dt.end(), from, to);
    from = ' ';
    to = '0';
    replace(dt.begin(), dt.end(), from, to);

    dt.resize(sz);

    const char* result = dt.c_str();
    
    ofstream fout;

    fout.open("mapdata.txt");

    fout << result << endl;

    fout.close();
}

static const char* loadMapdata()
{
    char* result = new char[200];

    ifstream fin("mapdata.txt");//입력스트림을 관리하기 위한 객체를 선언 및 파일 열기

    if (fin.fail()) {
        Borland::gotoxy(2, 30);
        cout << "파일 오픈에 실패했습니다." << endl;
        return nullptr;
    }

    fin >> result;


    for (int i = 0; i < 200; i++)
    {
        if (result[i] == '0') result[i] = ' ';
        else if (result[i] == '1') result[i] = '\xdb';
    }

    return result;
}

