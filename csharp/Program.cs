using System.Runtime.CompilerServices;
using System.Text;
using Motion;

Console.OutputEncoding = Encoding.UTF8;

Console.WriteLine("=== 1. Композиция + агрегация + проверка правил ===");
var logo = new SourceFile("logo.png");
var project = new Project("promo", 1920, 1080, 30, 4);
project.AddImage("logo_left", logo, 0, 0);
project.AddImage("logo_right", logo, 960, 0);
Console.WriteLine(project);

Console.WriteLine("-- работа с частью через целое");
project.MoveImage("logo_left", 100, 50);
project.SetImageOpacity("logo_left", 50);
Console.WriteLine(project);

Console.WriteLine("-- корректное действие");
project.Export();

Console.WriteLine("-- нарушение правила: прозрачность 150");
project.SetImageOpacity("logo_left", 150);

Console.WriteLine("-- нарушение правила: экспорт без исходного файла");
logo.MarkMissing();
project.Export();
logo.Restore();

Console.WriteLine("-- агрегированный объект существует независимо от проекта:");
Console.WriteLine(logo);

Console.WriteLine("\n=== 2. Ссылки и копии (class vs struct) ===");
var firstImage = new Image("banner", logo, 10, 20);
Image secondImage = firstImage;
secondImage.MoveBy(40, 30);
secondImage.SetOpacity(60);
Console.WriteLine($"firstImage  -> {firstImage}");
Console.WriteLine($"secondImage -> {secondImage}");
Console.WriteLine($"ReferenceEquals(firstImage, secondImage) = {ReferenceEquals(firstImage, secondImage)}");

var pointA = new CanvasPoint(10, 20);
CanvasPoint pointB = pointA;
pointB.X = 500;
pointB.Y = 300;
Console.WriteLine($"struct pointA = {pointA} (не изменилась)");
Console.WriteLine($"struct pointB = {pointB} (изменилась только копия)");

Console.WriteLine("\n=== 3. Освобождение ресурса без деструктора (IDisposable + using) ===");
using (var log = new ExportLog(project.Name))
{
    log.Write("Проверка исходных файлов сцены...");
    if (project.Export())
    {
        log.Write($"Сохранено {project.FrameCount} кадров.");
    }
}
Console.WriteLine("  После блока using: ресурс уже освобождён.");

Console.WriteLine("\n=== 4. Сборщик мусора (WeakReference + GC.Collect) ===");
WeakReference<Image> watcher = CreateTemporaryImage(logo);
Console.WriteLine($"После выхода из метода (до GC): объект жив = {IsAlive(watcher)}");
GC.Collect();
GC.WaitForPendingFinalizers();
GC.Collect();
Console.WriteLine($"После GC.Collect():             объект жив = {IsAlive(watcher)}");

[MethodImpl(MethodImplOptions.NoInlining)]
static WeakReference<Image> CreateTemporaryImage(SourceFile source)
{
    var temp = new Image("temp_preview", source, 5, 5);
    return new WeakReference<Image>(temp);
}

[MethodImpl(MethodImplOptions.NoInlining)]
static bool IsAlive(WeakReference<Image> watcher) => watcher.TryGetTarget(out _);
