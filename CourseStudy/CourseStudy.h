
// CourseStudy.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCourseStudyApp:
// Сведения о реализации этого класса: CourseStudy.cpp
//

class CCourseStudyApp : public CWinApp
{
public:
	CCourseStudyApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCourseStudyApp theApp;
