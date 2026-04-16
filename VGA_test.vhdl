library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
 
entity vga_test is
    Port (
        clock : in  STD_LOGIC;
        Hsync    : out STD_LOGIC;
        Vsync    : out STD_LOGIC;
        vgaRed     : out STD_LOGIC_VECTOR (3 downto 0);
        vgaGreen     : out STD_LOGIC_VECTOR (3 downto 0);
        vgaBlue     : out STD_LOGIC_VECTOR (3 downto 0)
    );
end vga_test;
 
architecture Behavioral of vga_test is
 
-- Pixelclock (25 MHz)
signal clk25 : STD_LOGIC := '0';
 
-- VGA Counter
signal h_count : integer range 0 to 799 := 0;
signal v_count : integer range 0 to 524 := 0;
 
-- sichtbarer Bereich
signal visible : STD_LOGIC;
 
-- Farbwechsel
signal color_toggle : STD_LOGIC := '0';
signal slow_counter : integer := 0;
 
begin
 
-- 🔹 Clock Divider (100 MHz → 25 MHz)
process(clock)
begin
    if rising_edge(clock) then
        clk25 <= not clk25;
    end if;
end process;
 
-- 🔹 VGA Timing
process(clk25)
begin
    if rising_edge(clk25) then
 
        -- Horizontal zählen
        if h_count = 799 then
            h_count <= 0;
 
            -- Vertikal zählen
            if v_count = 524 then
                v_count <= 0;
            else
                v_count <= v_count + 1;
            end if;
 
        else
            h_count <= h_count + 1;
        end if;
 
    end if;
end process;
 
-- 🔹 Sync-Signale
Hsync <= '0' when (h_count >= 656 and h_count < 752) else '1';
Vsync <= '0' when (v_count >= 490 and v_count < 492) else '1';
 
-- 🔹 sichtbarer Bereich
visible <= '1' when (h_count < 640 and v_count < 480) else '0';
 
-- 🔹 Langsamer Farbwechsel (~1 Hz)
process(clk25)
begin
    if rising_edge(clk25) then
        if slow_counter = 25_000_000 then
            slow_counter <= 0;
            color_toggle <= not color_toggle;
        else
            slow_counter <= slow_counter + 1;
        end if;
    end if;
end process;
 
-- 🔹 Farbe setzen
process(visible, color_toggle)
begin
    if visible = '1' then
        if color_toggle = '0' then
            vgaRed <= "1111";
            vgaGreen <= "0000";
            vgaBlue <= "0000";
        else
            vgaRed <= "0000";
            vgaGreen <= "1111";
            vgaBlue <= "0000";
        end if;
    else
        vgaRed <= "0000";
        vgaGreen <= "0000";
        vgaBlue <= "0000";
    end if;
end process;
 
end Behavioral;