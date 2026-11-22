# Курсовая работа / Лабораторная работа № 3: ООП (C# и C++)

**Тема курсовой работы:** Проектирование и разработка графического движка 2D-анимации и интерполяции ключевых кадров.  
**Тема ЛР 3:** Язык программирования с управляемой памятью (C#). Умные указатели (C++).

## Структура проекта

### Часть 1 — C# (`csharp/`)
Перенос классов предметной области (`SourceFile`, `Image`, `Project`) на язык с управляемой памятью C# (.NET 9), а также вспомогательная структура `CanvasPoint` (`struct`) и класс журнала экспорта `ExportLog` (`IDisposable`).
- `csharp/SourceFile.cs` — исходный файл изображения;
- `csharp/CanvasPoint.cs` — структура координат на холсте (тип-значение);
- `csharp/Image.cs` — элемент сцены (агрегация `SourceFile`);
- `csharp/Project.cs` — проект анимации (композиция `Image`);
- `csharp/ExportLog.cs` — ресурс с явным освобождением (`IDisposable`);
- `csharp/Program.cs` — демонстрация сценария предметной области, ссылок и копий (`class` vs `struct`), `using`/`IDisposable` и сборщика мусора (`WeakReference` + `GC.Collect`).

#### Сборка и запуск C# из командной строки
Требуется .NET SDK (версия 9.0 или выше).
```bash
dotnet build csharp
dotnet run --project csharp
```

### Часть 2 — C++ (корень репозитория)
Проект на C++17 в пространстве имён `motion`, переведённый с сырых указателей и `new`/`delete` на умные указатели (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`).
- `source_file.hpp` / `source_file.cpp` — класс `SourceFile`;
- `image.hpp` / `image.cpp` — класс `Image` (агрегация через `std::weak_ptr<SourceFile>`);
- `project.hpp` / `project.cpp` — класс `Project` (композиция по значению `std::vector<Image>`);
- `main.cpp` — демонстрация `std::unique_ptr` (включая `std::move` и массивы), `std::shared_ptr` (`use_count()`) и `std::weak_ptr` (`lock()`).

#### Сборка и запуск C++ из командной строки
Через CMake (MSVC / Visual Studio):
```bash
cmake -S . -B build
cmake --build build
./build/Debug/oop_coursework.exe
```
Или напрямую через `g++`:
```bash
g++ main.cpp image.cpp project.cpp source_file.cpp -std=c++17 -o oop_coursework
./oop_coursework
```
