using System.Text;

namespace Motion;

public class Project
{
    private const string DefaultName = "untitled";
    private const int DefaultWidth = 1920;
    private const int DefaultHeight = 1080;
    private const int DefaultFps = 30;
    private const int DefaultDurationSec = 4;

    private readonly List<Image> _images = new();

    public string Name { get; }
    public int Width { get; }
    public int Height { get; }
    public int Fps { get; }
    public int DurationSec { get; }

    public int FrameCount
    {
        get { return Fps * DurationSec; }
    }

    public int ImageCount
    {
        get { return _images.Count; }
    }

    public Project(string name, int width, int height, int fps, int durationSec)
    {
        Name = string.IsNullOrWhiteSpace(name) ? DefaultName : name;

        if (width <= 0 || height <= 0 || fps <= 0 || durationSec <= 0)
        {
            Console.WriteLine("  [Project] ОШИБКА: недопустимые параметры, используются значения по умолчанию");
            Width = DefaultWidth;
            Height = DefaultHeight;
            Fps = DefaultFps;
            DurationSec = DefaultDurationSec;
        }
        else
        {
            Width = width;
            Height = height;
            Fps = fps;
            DurationSec = durationSec;
        }

        Console.WriteLine($"  [Project] создано: {Name}");
    }

    private Image? FindImage(string name)
    {
        foreach (Image image in _images)
        {
            if (image.Name == name)
            {
                return image;
            }
        }

        return null;
    }

    public void AddImage(string name, SourceFile? source, double x = 0.0, double y = 0.0)
    {
        _images.Add(new Image(name, source, x, y));
    }

    public bool MoveImage(string name, double dx, double dy)
    {
        Image? image = FindImage(name);
        if (image is null)
        {
            Console.WriteLine($"  [Project] изображение не найдено: {name}");
            return false;
        }

        image.MoveBy(dx, dy);
        return true;
    }

    public bool SetImageOpacity(string name, double opacity)
    {
        Image? image = FindImage(name);
        if (image is null)
        {
            Console.WriteLine($"  [Project] изображение не найдено: {name}");
            return false;
        }

        return image.SetOpacity(opacity);
    }

    public bool Export()
    {
        foreach (Image image in _images)
        {
            if (!image.IsReady)
            {
                Console.WriteLine(
                    $"  [Project] ЭКСПОРТ ОТКЛОНЕН: исходный файл изображения '{image.Name}' недоступен");
                return false;
            }
        }

        Console.WriteLine(
            $"  [Project] экспортировано кадров: {FrameCount} ({Width}x{Height}, {Fps} кадров/с)");
        return true;
    }

    public override string ToString()
    {
        var sb = new StringBuilder();
        sb.Append($"  [Project] {Name} {Width}x{Height}, {Fps} кадров/с, {DurationSec} с, изображений: {_images.Count}");
        foreach (Image image in _images)
        {
            sb.AppendLine();
            sb.Append(image);
        }

        return sb.ToString();
    }
}
