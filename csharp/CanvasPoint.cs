namespace Motion;

public struct CanvasPoint
{
    public double X { get; set; }
    public double Y { get; set; }

    public CanvasPoint(double x, double y)
    {
        X = x;
        Y = y;
    }

    public override string ToString() => $"({X}, {Y})";
}
