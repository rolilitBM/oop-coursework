namespace Motion;

public class Image
{
    private const string DefaultName = "unnamed";
    private const double MinOpacity = 0.0;
    private const double MaxOpacity = 100.0;

    public string Name { get; }
    public SourceFile? Source { get; set; }
    public CanvasPoint Position { get; private set; }
    public double Opacity { get; private set; } = MaxOpacity;

    public double X
    {
        get { return Position.X; }
    }

    public double Y
    {
        get { return Position.Y; }
    }

    public bool IsReady
    {
        get { return Source is not null && Source.IsAvailable; }
    }

    public Image()
    {
        Name = DefaultName;
        Position = new CanvasPoint(0.0, 0.0);
        Console.WriteLine($"  [Image] создано по умолчанию: {Name}");
    }

    public Image(string name, SourceFile? source, double x = 0.0, double y = 0.0)
    {
        Name = name;
        Source = source;
        Position = new CanvasPoint(x, y);
        Console.WriteLine($"  [Image] создано: {Name}");
    }

    public void MoveBy(double dx, double dy)
    {
        Position = new CanvasPoint(Position.X + dx, Position.Y + dy);
    }

    public bool SetOpacity(double opacity)
    {
        if (opacity < MinOpacity || opacity > MaxOpacity)
        {
            Console.WriteLine(
                $"  [Image] ОШИБКА: прозрачность {opacity} вне диапазона {MinOpacity}..{MaxOpacity}, отклонено ({Name})");
            return false;
        }

        Opacity = opacity;
        return true;
    }

    public void AlignWith(Image other)
    {
        Position = other.Position;
    }

    public override string ToString()
    {
        string sourceText = Source is not null ? Source.Path : "<нет>";
        return $"  [Image] {Name}: x={Position.X} y={Position.Y} прозрачность={Opacity}% источник={sourceText}";
    }
}
