#pragma once

#include "image.hpp"
#include "source_file.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace motion
{
    class Project
    {
    private:
        static constexpr auto BASE_NAME = "untitled";
        static constexpr int DEFAULT_WIDTH = 1920;
        static constexpr int DEFAULT_HEIGHT = 1080;
        static constexpr int DEFAULT_FPS = 30;
        static constexpr int DEFAULT_DURATION = 4;

        std::string m_name{ BASE_NAME };
        int m_width{ DEFAULT_WIDTH };
        int m_height{ DEFAULT_HEIGHT };
        int m_fps{ DEFAULT_FPS };
        int m_durationSec{ DEFAULT_DURATION };
        std::vector<Image> m_images{};

        [[nodiscard]] int FindImage(std::string_view name) const;

    public:
        Project(std::string_view name, int width, int height, int fps, int durationSec);

        Project() = delete;
        Project(const Project&) = delete;
        Project(Project&&) = delete;
        Project& operator=(const Project&) = delete;
        Project& operator=(Project&&) = delete;
        ~Project();

        [[nodiscard]] int GetFrameCount() const
        {
            return m_fps * m_durationSec;
        }

        void AddImage(std::string_view name, const std::shared_ptr<SourceFile>& source, double x = 0.0, double y = 0.0);

        bool MoveImage(std::string_view name, double dx, double dy);
        bool SetImageOpacity(std::string_view name, double opacity);

        bool Export() const;
        void Describe() const;
    };
}
