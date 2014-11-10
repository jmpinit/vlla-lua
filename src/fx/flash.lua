WIDTH = 60
HEIGHT = 32

offset = 12
brightness = 64

local t = 0
while true do
    for y = 0, HEIGHT do
        for x = 0, WIDTH do
            if t % 2 == 0 then
                vlla.palette(255, 255, 255)
            else
                vlla.palette(0, 0, 0)
            end
            vlla.point(x, y)

            local i = 0
            while i < 16 do
                i = i + 1
            end
        end
    end

    t = t+1
    vlla.refresh()
end
