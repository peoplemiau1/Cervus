function add(a, b)
    return a + b
end

-- Call the function 60 times to trigger the hot-spot threshold (50) and execute via JIT!
for i = 1, 60 do
    local r = add(10, 20)
    if i == 50 then
        print("Executing call #50 (triggering JIT)...")
    elseif i == 60 then
        print("Result at call #60: " .. tostring(r))
    end
end
