#pragma once
#include <iostream>

// ������������ ���� ����������� ���������� (���������� ��� ���������)
namespace graphics_lib_pro
{
	// ����� ��� ���������
	class ICanvas
	{
	public:
		virtual void SetColor(uint32_t rgbColor) = 0;
		// ������ "����" � ����� x, y
		virtual void MoveTo(int x, int y) = 0;
		// ������ ����� � ������� �������, ���������� ���� � ����� x,y 
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

	// ���������� ������ ��� ���������
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(uint32_t rgbColor) override
		{
			std::cout << "SetColor (#" << rgbColor << ")" << std::endl;
			// TODO: ������� � output ���� � ���� ������ SetColor (#RRGGBB)
		}
		void MoveTo(int x, int y) override
		{
			std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
		}
		void LineTo(int x, int y) override
		{
			std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
		}
	};
}