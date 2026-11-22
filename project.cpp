#include "project.hpp"

#include <iostream>

namespace motion
{
    Project::Project(std::string_view name, int width, int height, int fps, int durationSec)
        : m_name{ name }
        , m_width{ width }
        , m_height{ height }
        , m_fps{ fps }
        , m_durationSec{ durationSec }
    {
        if (m_width <= 0 || m_height <= 0 || m_fps <= 0 || m_durationSec <= 0)
        {
            std::cout << "  [Project] ОШИБКА: недопустимые параметры, используются значения по умолчанию\n";
            m_width = DEFAULT_WIDTH;
            m_height = DEFAULT_HEIGHT;
            m_fps = DEFAULT_FPS;
            m_durationSec = DEFAULT_DURATION;
        }

        std::cout << "  [Project] создано: " << m_name << "\n";
    }

    Project::~Project()
    {
        std::cout << "  [Project] УНИЧТОЖЕНО: " << m_name << "\n";
    }

    int Project::FindImage(std::string_view name) const
    {
        for (size_t i = 0; i < m_images.size(); ++i)
        {
            if (m_images[i].GetName() == name)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void Project::AddImage(std::string_view name, const std::shared_ptr<SourceFile>& source, double x, double y)
    {
        m_images.emplace_back(name, source, x, y);
    }

    bool Project::MoveImage(std::string_view name, double dx, double dy)
    {
        const int index = FindImage(name);
        if (index < 0)
        {
            std::cout << "  [Project] изображение не найдено: " << name << "\n";
            return false;
        }

        m_images[index].MoveBy(dx, dy);
        return true;
    }

    bool Project::SetImageOpacity(std::string_view name, double opacity)
    {
        const int index = FindImage(name);
        if (index < 0)
        {
            std::cout << "  [Project] изображение не найдено: " << name << "\n";
            return false;
        }

        return m_images[index].SetOpacity(opacity);
    }

    bool Project::Export() const
    {
        for (const Image& image : m_images)
        {
            if (!image.IsReady())
            {
                std::cout << "  [Project] ЭКСПОРТ ОТКЛОНЕН: исходный файл изображения '" << image.GetName()
                          << "' недоступен\n";
                return false;
            }
        }

        std::cout << "  [Project] экспортировано кадров: " << GetFrameCount() << " (" << m_width << "x" << m_height
                  << ", " << m_fps << " кадров/с)\n";
        return true;
    }

    void Project::Describe() const
    {
        std::cout << "  [Project] " << m_name << " " << m_width << "x" << m_height << ", " << m_fps << " кадров/с, "
                  << m_durationSec << " с, изображений: " << m_images.size() << "\n";

        for (const Image& image : m_images)
        {
            image.Describe();
        }
    }
}
