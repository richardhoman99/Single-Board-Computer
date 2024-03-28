-- MCD SBC Project
-- Richard Homan
-- 03/18/2023
-- AddressDecoder_Bench.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Test bench file for AddressDecoder.vhd
-- dependencies:
--		none

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity AddressDecoder_Bench is
end AddressDecoder_Bench;

architecture behavior of AddressDecoder_Bench is  
component AddressDecoder port(
    o_oe          : out  std_logic;
    o_we          : out  std_logic;
    o_duart_rw    : out  std_logic;

    o_cs_roml     : out  std_logic;
    o_cs_romh     : out  std_logic;
    o_cs_raml     : out  std_logic;
    o_cs_ramh     : out  std_logic;
    o_cs_duart    : out  std_logic;

    o_dtack       : out std_logic;
    i_rw          :  in  std_logic;
    i_lds         :  in  std_logic;
    i_uds         :  in  std_logic;
    i_as          :  in  std_logic;

    i_duart_dtack :  in  std_logic;

    i_addr        :  in  std_logic_vector(7 downto 0);

    o_berr        : out  std_logic
    );
end component;

-- input value instantiations
signal i_duart_dtack : std_logic := '1';
signal i_rw          : std_logic := '1';
signal i_lds         : std_logic := '1';
signal i_uds         : std_logic := '1';
signal i_as          : std_logic := '1';
signal i_addr        : std_logic_vector(7 downto 0) := (others => '0');

signal o_oe          : std_logic;
signal o_we          : std_logic;
signal o_duart_rw    : std_logic;
signal o_cs_roml     : std_logic;
signal o_cs_romh     : std_logic;
signal o_cs_raml     : std_logic;
signal o_cs_ramh     : std_logic;
signal o_cs_duart    : std_logic;
signal o_dtack       : std_logic;
signal o_berr        : std_logic;

signal test_clk      : std_logic;
constant test_clk_period : time := 10 ns;

signal s_in          : unsigned(4 downto 0) := (others=>'0');
signal s_out         : std_logic_vector(5 downto 0);

begin

-- Instantiate the Unit Under Test (UUT)
uut: AddressDecoder port map (
    o_oe => o_oe,
    o_we => o_we,
    o_duart_rw => o_duart_rw,
    o_cs_roml => o_cs_roml,
    o_cs_romh => o_cs_romh,
    o_cs_raml => o_cs_raml,
    o_cs_ramh => o_cs_ramh,
    o_cs_duart => o_cs_duart,
    i_duart_dtack => i_duart_dtack,
    i_rw => i_rw,
    i_lds => i_lds,
    i_uds => i_uds,
    i_as => i_as,
    i_addr => i_addr,
    o_dtack => o_dtack,
    o_berr => o_berr
    );

test_clk_proc :process
begin
	--test_clk <= '0';
	--wait for test_clk_period/2;
	--test_clk <= '1';
	--wait for test_clk_period/2;
	wait;
    end process;

-- Stimulus process
stim_proc: process
begin
    while not(s_in = "11111") loop
    wait for test_clk_period/4;
    i_as <= '0';
    wait for test_clk_period/4;
    -- ==========  BEGIN AS TESTS  ==========
    -- test chip select lines
    if    s_in = "00101" then -- ram low write
        assert (s_out = "111101") report "ram low write" severity error;
    elsif s_in = "00110" then -- ram high write
        assert (s_out = "111011") report "ram high write" severity error;
    elsif s_in = "01001" then -- duart write
        assert (s_out = "111110") report "duart write" severity error;
    elsif s_in = "10001" then -- rom low read
        assert (s_out = "110111") report "rom low read" severity error;
    elsif s_in = "10010" then -- rom high read
        assert (s_out = "101111") report "rom high read" severity error;
    elsif s_in = "10101" then -- ram low read
        assert (s_out = "111101") report "ram low read" severity error;
    elsif s_in = "10110" then -- ram high read
        assert (s_out = "111011") report "ram high read" severity error;
    elsif s_in = "11001" then -- duart read
        assert (s_out = "111110") report "duart read" severity error;
    elsif s_in = "00011" then -- rom write no selection
        assert (s_out = "111111")
        report "rom write no selection" severity error;
    elsif s_in = "00111" then -- ram write no selection
        assert (s_out = "111111")
        report "ram write no selection" severity error;
    elsif s_in = "01011" then -- duart write no selection
        assert (s_out = "111111")
        report "duart write no selection" severity error;
    elsif s_in = "01111" then -- addr out of range write no selection
        assert (s_out = "111111")
        report "inv addr read no selection" severity error;
    elsif s_in = "10011" then -- rom read no selection
        assert (s_out = "111111")
        report "rom read no selection" severity error;
    elsif s_in = "10111" then -- ram read no selection
        assert (s_out = "111111")
        report "ram read no selection" severity error;
    elsif s_in = "11011" then -- duart read no selection
        assert (s_out = "111111")
        report "duart read no selection" severity error;
    elsif s_in = "11111" then -- addr out of range read no selection
         assert (s_out = "111111")
        report "inv addr read no selection" severity error;   
    else 
        assert (o_berr = '0') report "did not reject" severity error;
    end if;

    -- verity dtack floating when duart selected, otherwise assert
    if o_cs_duart = '0' then
        assert (o_dtack = 'Z') report "dtack not floating" severity error;
    else
        if o_berr = '1' then
            if (i_uds and i_lds) = '1' then -- if neither is asserted
                assert (o_dtack = '1')
                report "dtack is asserted" severity error;
            else -- uds or lds is asserted
                assert (o_dtack = '0')
                report "dtack not asserted" severity error;
            end if;
        else
            assert (o_dtack = '1') report "dtack asserted" severity error;
        end if;
    end if;

    -- verify rw lines
    if i_rw = '0' then -- asserted
        assert (o_duart_rw = '0')
            report "duart read/write not asserted" severity error;
        assert  (o_we = '0') report "write enable not asserted" severity error;
    else
        assert (o_duart_rw = '1')
            report "duart read/write asserted" severity error;
        assert (o_we = '1') report "write enable asserted" severity error;
    end if;

    assert (o_oe = '0')
        report "output enable not enabled on address strobe" severity error;
    -- ==========   END AS TESTS   ==========
    wait for test_clk_period/4;
    i_as <= '1';
    wait for test_clk_period/4;
    -- ========== BEGIN !AS TESTS ==========
    assert (o_oe = '1')
        report "output enable signal not latched up"  severity error;
    assert (o_we = '1') report "write enable asserted" severity error;
    assert (o_duart_rw = '1')
        report "duart read/write asserted" severity error;
    assert (s_out = "111111")
        report "berr & chip select signals not latched up" severity error;
    assert (o_dtack = '1') report "dtack asserted" severity error;
    -- ==========  END !AS TESTS  ==========
    s_in <= s_in + 1;
    end loop;

    assert false report "accepted" severity note;
wait;

end process;

i_rw       <= s_in(4);
i_addr(1)  <= s_in(3);
i_addr(0)  <= s_in(2);
i_uds      <= s_in(1);
i_lds      <= s_in(0);

s_out(5) <= o_berr;
s_out(4) <= o_cs_romh;
s_out(3) <= o_cs_roml;
s_out(2) <= o_cs_ramh;
s_out(1) <= o_cs_raml;
s_out(0) <= o_cs_duart;

end;
