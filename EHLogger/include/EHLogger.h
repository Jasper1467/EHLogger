#pragma once

#include <Windows.h>
#include <cstdio>
#include <string>

class CEHLogger
{
public:
	enum Type_e : int
	{
		TYPE_ERROR = 0,
		TYPE_INFO,
		TYPE_WARNING,
		TYPE_MAX,
	};

	enum StyleColor_e : int
	{
		STYLE_COLOR_ERROR = 0,
		STYLE_COLOR_INFO,
		STYLE_COLOR_WARNING,
		STYLE_COLOR_MAX,
	};

	struct Style_t
	{
		const char* m_szPrefix[TYPE_MAX];
		WORD m_wColor[STYLE_COLOR_MAX];
	};

	explicit CEHLogger(const Style_t& Style = DefaultStyle()) : m_Style(Style) {}

	static Style_t DefaultStyle()
	{
		Style_t Style{};

		const char* szPrefixes[TYPE_MAX] = { "[ERROR] ", "[INFO] ", "[WARNING] " };
		for (int i = 0; i < TYPE_MAX; i++)
			Style.m_szPrefix[i] = szPrefixes[i];

		constexpr WORD wColors[STYLE_COLOR_MAX] = { 12, 11, 14 };
		for (int i = 0; i < STYLE_COLOR_MAX; i++)
			Style.m_wColor[i] = wColors[i];

		return Style;
	}

	void Initialize(const Style_t& Style)
	{
		m_Style = Style;
	}

	void Log(const Type_e nType, const char* szFormat, ...) const
	{
		char cBuffer[1024];

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GetStyle().m_wColor[nType]);

		va_list va;
		va_start(va, szFormat);
		_vsnprintf_s(cBuffer, sizeof(cBuffer), szFormat, va);
		va_end(va);

		printf_s("%s%s", m_Style.m_szPrefix[nType], cBuffer);
	}

	void Log(const Type_e nType, const wchar_t* wszFormat, ...) const
	{
		wchar_t wcBuffer[1024];

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GetStyle().m_wColor[nType]);

		va_list va;
		va_start(va, wszFormat);
		vswprintf_s(wcBuffer, sizeof(wcBuffer), wszFormat, va);
		va_end(va);

		wprintf_s(L"%hs%s", m_Style.m_szPrefix[nType], wcBuffer);
	}

	Style_t GetStyle() const
	{
		return m_Style;
	}

private:
	Style_t m_Style;
};