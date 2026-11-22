namespace Motion;

public class SourceFile
{
    public string Path { get; private set; }
    public bool IsAvailable { get; private set; }

    public SourceFile()
    {
        Path = string.Empty;
        IsAvailable = false;
        Console.WriteLine($"  [SourceFile] создан по умолчанию: {Path}");
    }

    public SourceFile(string path, bool isAvailable = true)
    {
        Path = path;
        IsAvailable = isAvailable;
        Console.WriteLine($"  [SourceFile] создано: {Path}");
    }

    public void UpdatePath(string newPath)
    {
        Path = newPath;
    }

    public void MarkMissing()
    {
        IsAvailable = false;
        Console.WriteLine($"  [SourceFile] сейчас недоступно: {Path}");
    }

    public void Restore()
    {
        IsAvailable = true;
        Console.WriteLine($"  [SourceFile] файл восстановлен: {Path}");
    }

    public override string ToString()
    {
        return $"  [SourceFile] {Path} {(IsAvailable ? "(доступен)" : "(ОТСУТСТВУЕТ)")}";
    }
}
