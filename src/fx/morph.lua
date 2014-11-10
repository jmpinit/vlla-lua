WIDTH = 60
HEIGHT = 32

SPEED = 128
BRIGHTNESS = 48

function dist(x1, y1, x2, y2)
    return math.sqrt(math.pow(x2-x1, 2) + math.pow(y2-y1, 2))
end

local t = 0
while true do
    for y = 0, HEIGHT do
        for x = 0, WIDTH do
            local cx = 30 + 30*math.cos(t/SPEED)
            local cy = 16 + 16*math.sin(t/SPEED)
            local d1 = dist(cx, cy, x, y)
            local d2 = dist(30, 16, x, y)

            local cx2 = 30 + 30*math.cos(t/SPEED)
            local cy2 = 16 + 16*math.sin(t/SPEED)
            local d3 = dist(cx2, cy2, x, y)
            local d4 = dist(30, 16, x, y)
            
            local r = 64 + 32*math.sin(d1/4) + 32*math.sin(d2/4)
            local g = 64 + 32*math.sin(d3/6) + 32*math.cos(d4/3)
            --vlla.palette(r/2, g/4, r % 48)
            vlla.palette((r % 48) / BRIGHTNESS, r/2/BRIGHTNESS, g/4/BRIGHTNESS)
            vlla.point(x, y)
        end
    end

    t = t + 1
    vlla.refresh()
end
