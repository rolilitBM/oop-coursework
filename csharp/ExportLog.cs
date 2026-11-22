namespace Motion;

public sealed class ExportLog : IDisposable
{
    private readonly string _projectName;
    private bool _disposed;

    public ExportLog(string projectName)
    {
        _projectName = projectName;
        Console.WriteLine($"  [+] журнал экспорта открыт: {_projectName}");
    }

    public void Write(string entry)
    {
        Console.WriteLine($"      {entry}");
    }

    public void Dispose()
    {
        if (_disposed)
        {
            return;
        }

        _disposed = true;
        Console.WriteLine($"  [-] журнал экспорта закрыт: {_projectName}");
    }
}
