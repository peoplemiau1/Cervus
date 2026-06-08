local ffi = require("ffi")

print("--- Cervus LuaJIT FFI Test ---")

-- Define standard C library, math, and libgui signatures
ffi.cdef[[
    int printf(const char *fmt, ...);
    double sqrt(double x);
    double sin(double x);
    
    // libgui functions
    int gui_init(void);
    void gui_clear(uint32_t color);
    void gui_draw_rect(int x, int y, int w, int h, uint32_t color);
    void gui_flush(void);
    void gui_deinit(void);
]]

-- 1. Test printf (stdout)
ffi.C.printf("Hello from LuaJIT FFI: printf works!\n")

-- 2. Test math functions
local val = ffi.C.sqrt(144.0)
print("Math test (sqrt of 144): " .. tostring(val))
local s = ffi.C.sin(3.141592653589793 / 2.0)
print("Math test (sin of pi/2): " .. tostring(s))

-- 3. Test GUI if possible (in graphics mode)
print("Initializing graphics mode...")
if ffi.C.gui_init() == 0 then
    print("libgui initialized successfully!")
    ffi.C.gui_clear(0xFF202020) -- Dark background
    ffi.C.gui_draw_rect(100, 100, 200, 150, 0xFF00FF00) -- Green rectangle
    ffi.C.gui_draw_rect(150, 130, 100, 90, 0xFFFF0000) -- Red rectangle
    ffi.C.gui_flush()
    print("Drawn rects on screen. Waiting 3 seconds...")
    
    -- Basic busy-wait sleep
    local start = os.clock()
    while os.clock() - start < 3.0 do end
    
    ffi.C.gui_deinit()
    print("libgui deinitialized.")
else
    print("Failed to initialize libgui (might not be in GUI mode).")
end

print("FFI Test Completed!")
