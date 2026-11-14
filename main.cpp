#include "image.hpp"
#include "project.hpp"
#include "source_file.hpp"
#include <iostream>

int main()
{
    using namespace motion;

    setlocale(LC_ALL, "Russian");

    std::cout << "=== 1. Статические объекты ===\n";
    SourceFile logo{ "logo.png" };
    Image staticImage{ "static_img", &logo, 10, 20 };
    staticImage.Describe();

    std::cout << "\n=== 2. Композиция + агрегация + проверка правил ===\n";
    {
        Project project{ "promo", 1920, 1080, 30, 4 };
        project.AddImage("logo_left", &logo, 0, 0);
        project.AddImage("logo_right", &logo, 960, 0);
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
        logo.MarkMissing();
        project.Export();
        logo.Restore();

        std::cout << "-- выход из блока: проект умирает вместе со своими изображениями\n";
    }
    std::cout << "-- после блока агрегированный объект жив:\n";
    logo.Describe();

    std::cout << "\n=== 3. Динамический объект (new / delete) ===\n";
    Image* dynamicImage = new Image{ "dynamic_img", &logo, 5, 5 };
    dynamicImage->MoveBy(1, 1);
    dynamicImage->Describe();
    Image& imageRef = *dynamicImage;
    imageRef.SetOpacity(70);
    staticImage.AlignWith(imageRef);
    staticImage.Describe();
    delete dynamicImage;

    std::cout << "\n=== 4. Динамический массив объектов (new[]) ===\n";
    Image* array = new Image[2];
    for (int i = 0; i < 2; ++i)
    {
        array[i].SetSource(&logo);
        array[i].MoveBy(i * 10, 0);
        array[i].Describe();
    }
    delete[] array;

    std::cout << "\n=== 5. Массив динамических объектов ===\n";
    Image* pointers[2];
    pointers[0] = new Image{ "ptr_img_0", &logo };
    pointers[1] = new Image{ "ptr_img_1", &logo, 3, 3 };
    for (const Image* pointer : pointers)
    {
        pointer->Describe();
    }
    for (const Image* pointer : pointers)
    {
        delete pointer;
    }

    std::cout << "\n=== Конец main: статические объекты умирают ===\n";
    return 0;
}
