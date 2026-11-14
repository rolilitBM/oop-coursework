#include "image.hpp"

#include <iostream>

namespace motion
{

    Image::Image()
    {
        std::cout << "  [Image] создано по умолчанию: " << m_name << "\n";
    }

    Image::Image(std::string_view name, SourceFile* source, double x, double y)
        : m_name{ name }
        , m_source{ source }
        , m_x{ x }
        , m_y{ y }
    {
        std::cout << "  [Image] создано: " << m_name << "\n";
    }

    Image::~Image()
    {
        std::cout << "  [Image] УНИЧТОЖЕНО: " << m_name << "\n";
    }

    bool Image::IsReady() const
    {
        return m_source != nullptr && m_source->IsAvailable();
    }

    void Image::MoveBy(double dx, double dy)
    {
        m_x += dx;
        m_y += dy;
    }

    bool Image::SetOpacity(double opacity)
    {
        if (opacity < MIN_OPACITY || opacity > MAX_OPACITY)
        {
            std::cout << "  [Image] ОШИБКА: прозрачность " << opacity << " вне диапазона 0..100, отклонено (" << m_name
                << ")\n";
            return false;
        }

        m_opacity = opacity;
        return true;
    }

    void Image::AlignWith(const Image& other)
    {
        m_x = other.m_x;
        m_y = other.m_y;
    }

    void Image::Describe() const
    {
        std::cout << "  [Image] " << m_name << ": x=" << m_x << " y=" << m_y << " прозрачность=" << m_opacity
            << "% источник=" << (m_source != nullptr ? m_source->GetPath() : "<нет>") << "\n";
    }

}