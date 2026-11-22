#include "source_file.hpp"

#include <iostream>

namespace motion
{
    SourceFile::SourceFile()
    {
        std::cout << "  [SourceFile] создан по умолчанию: " << m_path << "\n";
    }

    SourceFile::SourceFile(std::string_view path, bool available)
        : m_path{ path }
        , m_available{ available }
    {
        std::cout << "  [SourceFile] создано: " << m_path << "\n";
    }

    SourceFile::~SourceFile()
    {
        std::cout << "  [SourceFile] уничтожено: " << m_path << "\n";
    }

    void SourceFile::UpdatePath(std::string_view newPath)
    {
        m_path = newPath;
    }

    void SourceFile::MarkMissing()
    {
        m_available = false;
        std::cout << "  [SourceFile] сейчас недоступно: " << m_path << "\n";
    }

    void SourceFile::Restore()
    {
        m_available = true;
        std::cout << "  [SourceFile] файл восстановлен: " << m_path << "\n";
    }

    void SourceFile::Describe() const
    {
        std::cout << "  [SourceFile] " << m_path << (m_available ? " (доступен)" : " (ОТСУТСТВУЕТ)") << "\n";
    }
}
