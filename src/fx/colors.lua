WIDTH = 60
HEIGHT = 32

for y = 0, HEIGHT do
    for x = 0, WIDTH do
        local c = (y*WIDTH+x)

        c = c % 256

        vlla.palette(0, c, 0)
        vlla.point(x, y)
    end
end

vlla.refresh()
