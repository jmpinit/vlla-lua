WIDTH = 60
HEIGHT = 32

for y = 0, HEIGHT do
    for x = 0, WIDTH do
        vlla.palette(255, 255, 255)
        vlla.point(x, y)
    end
end

vlla.refresh()
