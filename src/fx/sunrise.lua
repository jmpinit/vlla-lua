WIDTH = 60
HEIGHT = 32

function dist(x1, y1, x2, y2)
    return math.sqrt(math.pow(x2-x1, 2) + math.pow(y2-y1, 2))
end

local t = 0
while true do
    local cx = 30
    local cy = -8 + t/16

    for y = 0, HEIGHT do
        for x = 0, WIDTH do
            local sunpart = 255 - 16 * dist(cx, cy, x, y)
            local ambience = 240 * cy / 32
            local full = sunpart + ambience

            if sunpart < 0 then
                sunpart = 0
            end

            local r = full
            local g = full
            local b = full

            vlla.palette(r, g, b)
            vlla.point(x, y)
        end
    end

    t = t + 1
    vlla.refresh()
end
