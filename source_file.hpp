#pragma once

#include <string>


namespace motion
{
    class SourceFile
    {
    private:
        static constexpr auto TAG = "sourse_file";

        std::string m_path;
        bool m_available{ false };

    public:
        SourceFile();
        SourceFile(std::string_view path, bool available = true);  

        SourceFile(const SourceFile&) = delete;
        SourceFile(SourceFile&&) = delete;
        SourceFile& operator=(const SourceFile&) = delete;
        SourceFile& operator=(SourceFile&&) = delete;
        ~SourceFile();

        [[nodiscard]] bool IsAvailable() const
        {
            return m_available;
        }
        void UpdatePath(std::string_view newPath);

        [[nodiscard]] std::string_view GetPath() const
        {
            return m_path;
        }
        void MarkMissing();

        void Restore();

        void Describe() const;
    };
}
