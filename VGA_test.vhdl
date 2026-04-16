LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

ENTITY vga_test IS
    PORT (
        clock : IN STD_LOGIC;
        Hsync : OUT STD_LOGIC;
        Vsync : OUT STD_LOGIC;
        vgaRed : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
        vgaGreen : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
        vgaBlue : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
        buttonCenter : IN STD_LOGIC;
        buttonUp : IN STD_LOGIC;
        buttonDown : IN STD_LOGIC;
        buttonLeft : IN STD_LOGIC;
        buttonRight : IN STD_LOGIC
    );
END vga_test;

ARCHITECTURE Behavioral OF vga_test IS

    -- Pixelclock (25 MHz)
    SIGNAL clk25 : STD_LOGIC := '0';

    -- VGA Counter
    SIGNAL h_count : INTEGER RANGE 0 TO 799 := 0;
    SIGNAL v_count : INTEGER RANGE 0 TO 524 := 0;

    -- Flag für sichtbarer Bereich
    SIGNAL visible : STD_LOGIC := '0';
    -- Flag für Änderung des Objekts
    SIGNAL object_toggle : STD_LOGIC := '0';

    -- Farbwechsel
    --SIGNAL color_toggle : STD_LOGIC := '0';
    SIGNAL slow_counter : INTEGER := 0;
    -- Signals for player object
    SIGNAL playerStartX : INTEGER := 320; -- Mitte des Bildschirms
    SIGNAL playerStartY : INTEGER := 240;
    SIGNAL playerSizeX : INTEGER := 50;
    SIGNAL playerSizeY : INTEGER := playerSizeX;

BEGIN

    -- Clock Divider (100 MHz → 25 MHz)
    PROCESS (clock)
    BEGIN
        IF rising_edge(clock) THEN
            clk25 <= NOT clk25;
        END IF;
    END PROCESS;

    -- VGA Timing
    PROCESS (clk25)
    BEGIN
        IF rising_edge(clk25) THEN

            -- Horizontal zählen
            IF h_count = 799 THEN
                h_count <= 0;

                -- Vertikal zählen
                IF v_count = 524 THEN
                    v_count <= 0;
                ELSE
                    v_count <= v_count + 1;
                END IF;

            ELSE
                h_count <= h_count + 1;
            END IF;

        END IF;
    END PROCESS;

    -- Sync-Signale
    Hsync <= '0' WHEN (h_count >= 656 AND h_count < 752) ELSE
        '1';
    Vsync <= '0' WHEN (v_count >= 490 AND v_count < 492) ELSE
        '1';

    -- sichtbarer Bereich
    visible <= '1' WHEN (h_count < 640 AND v_count < 480) ELSE
        '0';

    -- Langsamer Farbwechsel (~1 Hz)
    -- PROCESS (clk25)
    -- BEGIN
    --     IF rising_edge(clk25) THEN
    --         IF slow_counter = 25_000_000 THEN
    --             slow_counter <= 0;
    --             color_toggle <= NOT color_toggle;
    --         ELSE
    --             slow_counter <= slow_counter + 1;
    --         END IF;
    --     END IF;
    -- END PROCESS;

    -- Farbe setzen
    -- PROCESS (visible, color_toggle)
    -- BEGIN
    --     IF visible = '1' THEN
    --         IF color_toggle = '0' THEN
    --             vgaRed <= "1111";
    --             vgaGreen <= "0000";
    --             vgaBlue <= "0000";
    --         ELSE
    --             vgaRed <= "0000";
    --             vgaGreen <= "1111";
    --             vgaBlue <= "0000";
    --         END IF;
    --     ELSE
    --         vgaRed <= "0000";
    --         vgaGreen <= "0000";
    --         vgaBlue <= "0000";
    --     END IF;
    -- END PROCESS;
    process(visible, h_count, v_count, playerStartX, playerStartY, playerSizeX, playerSizeY)
    begin
        if visible = '1' then
            if h_count >= playerStartX and h_count < playerStartX + playerSizeX and
               v_count >= playerStartY and v_count < playerStartY + playerSizeY then
                -- Spielerobjekt zeichnen
                vgaRed <= "1111";
                vgaGreen <= "0000";
                vgaBlue <= "0000";
            else
                -- Hintergrund
                vgaRed <= "1111";
                vgaGreen <= "1111";
                vgaBlue <= "1111";
            end if;
        ELSE
        -- Outside of visible area, set to black
            vgaRed <= "0000";
            vgaGreen <= "0000";
            vgaBlue <= "0000";
        END IF;
    end process;



END Behavioral;