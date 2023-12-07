#pragma once

// 미리 컴파일 된 헤더
#include <Windows.h>
#include <iostream>

#include <map>
using std::map;

#include <string>
using std::string;
using std::wstring;

#include <vector>
using std::vector;

#include <math.h>
#include <assert.h>

// 라이브러리 참조 CPlayer.cpp 내에 TransparentBlt함수 구현부 참조
# pragma comment(lib, "Msimg32.lib")

#include "Resource.h"
#include "define.h"
#include "struct.h"
#include "func.h"