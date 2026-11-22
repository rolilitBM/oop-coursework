#include "image.hpp"
#include "project.hpp"
#include "source_file.hpp"

#include <iostream>
#include <memory>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    using namespace motion;

    std::cout << "=== 1. Композиция + агрегация (weak_ptr) + проверка правил ===\n";
    std::shared_ptr<SourceFile> logo = std::make_shared<SourceFile>("logo.png");
    std::cout << "  logo.use_count() = " << logo.use_count() << "\n";
    {
        Project project{ "promo", 1920, 1080, 30, 4 };
        project.AddImage("logo_left", logo, 0, 0);
        project.AddImage("logo_right", logo, 960, 0);
        std::cout << "  После добавления 2 изображений (weak_ptr): logo.use_count() = " << logo.use_count() << "\n";
        project.Describe();

        std::cout << "-- работа с частью через целое\n";
        project.MoveImage("logo_left", 100, 50);
        project.SetImageOpacity("logo_left", 50);
        project.Describe();

        std::cout << "-- корректное действие\n";
        project.Export();

        std::cout << "-- нарушение правила: прозрачность 150\n";
        project.SetImageOpacity("logo_left", 150);

        std::cout << "-- нарушение правила: экспорт без исходного файла\n";
        logo->MarkMissing();
        project.Export();
        logo->Restore();

        std::cout << "-- выход из блока: проект умирает вместе со своими изображениями\n";
    }
    std::cout << "-- после блока агрегированный объект жив:\n";
    logo->Describe();

    std::cout << "\n=== 2. std::unique_ptr: автоматическое удаление и передача владения (std::move) ===\n";
    {
        std::unique_ptr<Image> dynamicImage = std::make_unique<Image>("dynamic_img", logo, 5, 5);
        dynamicImage->MoveBy(1, 1);
        dynamicImage->Describe();

        std::unique_ptr<Image> movedImage = std::move(dynamicImage);
        if (!dynamicImage)
        {
            std::cout << "  dynamicImage пуст после std::move: владение передано movedImage\n";
        }
        movedImage->SetOpacity(70);
        movedImage->Describe();
        std::cout << "-- выход из блока unique_ptr (без delete)\n";
    }

    std::cout << "\n=== 3. Массивы на умных указателях (замена new[] и массива указателей) ===\n";
    {
        std::cout << "-- динамический массив объектов: std::unique_ptr<Image[]>\n";
        std::unique_ptr<Image[]> array = std::make_unique<Image[]>(2);
        for (int i = 0; i < 2; ++i)
        {
            array[i].SetSource(logo);
            array[i].MoveBy(i * 10, 0);
            array[i].Describe();
        }

        std::cout << "-- массив умных указателей: std::unique_ptr<Image>[2]\n";
        std::unique_ptr<Image> pointers[2];
        pointers[0] = std::make_unique<Image>("ptr_img_0", logo);
        pointers[1] = std::make_unique<Image>("ptr_img_1", logo, 3, 3);
        for (const std::unique_ptr<Image>& pointer : pointers)
        {
            pointer->Describe();
        }
        std::cout << "-- выход из блока массивов (автоматическое освобождение)\n";
    }

    std::cout << "\n=== 4. std::shared_ptr: счётчик владельцев (use_count) ===\n";
    {
        std::shared_ptr<SourceFile> sharedBg = std::make_shared<SourceFile>("background.png");
        std::cout << "  sharedBg.use_count() = " << sharedBg.use_count() << "\n";
        {
            std::shared_ptr<SourceFile> secondOwner = sharedBg;
            std::cout << "  после копирования: sharedBg.use_count() = " << sharedBg.use_count() << "\n";
            std::cout << "-- выход из вложенного блока: secondOwner уничтожается\n";
        }
        std::cout << "  после выхода из блока: sharedBg.use_count() = " << sharedBg.use_count() << "\n";
        std::cout << "-- выход из внешнего блока: последний владелец уничтожается\n";
    }

    std::cout << "\n=== 5. std::weak_ptr: наблюдение и проверка через lock() ===\n";
    std::shared_ptr<SourceFile> tempFile = std::make_shared<SourceFile>("temp_icon.png");
    Image observerImg{ "observer_img", tempFile, 15, 25 };
    std::cout << "  до уничтожения владельца: tempFile.use_count() = " << tempFile.use_count()
              << ", IsReady() = " << (observerImg.IsReady() ? "true" : "false") << "\n";
    observerImg.Describe();

    std::cout << "-- сбрасываем последнего владельца tempFile.reset()\n";
    tempFile.reset();
    std::cout << "  после уничтожения владельца: IsReady() = " << (observerImg.IsReady() ? "true" : "false") << "\n";
    observerImg.Describe();

    std::cout << "\n=== Конец main: оставшиеся объекты уничтожаются ===\n";
    return 0;
}
