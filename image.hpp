#pragma once

#include "source_file.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace motion
{
    class Image
    {
    private:
        static constexpr auto BASE_NAME = "unnamed";
        static constexpr double MIN_OPACITY = 0.0;
        static constexpr double MAX_OPACITY = 100.0;

        std::string m_name{ BASE_NAME };
        std::weak_ptr<SourceFile> m_source{};
        double m_x{ 0.0 };
        double m_y{ 0.0 };
        double m_opacity{ MAX_OPACITY };

    public:
        Image();
        Image(std::string_view name, const std::shared_ptr<SourceFile>& source, double x = 0.0, double y = 0.0);

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        Image(Image&&) noexcept = default;
        Image& operator=(Image&&) noexcept = default;

        ~Image();

        [[nodiscard]] std::string_view GetName() const
        {
            return m_name;
        }

        [[nodiscard]] double GetOpacity() const
        {
            return m_opacity;
        }

        void SetSource(const std::shared_ptr<SourceFile>& source)
        {
            m_source = source;
        }

        [[nodiscard]] bool IsReady() const;

        void MoveBy(double dx, double dy);
        bool SetOpacity(double opacity);
        void AlignWith(const Image& other);
        void Describe() const;
    };
}
