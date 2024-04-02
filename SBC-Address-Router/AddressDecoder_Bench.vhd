-- MCD SBC Project
-- Richard Homan
-- 03/18/2023
-- AddressDecoder_Bench.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Test bench file for AddressDecoder.vhd
-- dependencies:
--		AddressDecoder.vhd

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity AddressDecoder_Bench is
end AddressDecoder_Bench;

architecture behavior of AddressDecoder_Bench is  
component AddressDecoder port(
    i_rw          :  in std_logic;
    i_lds         :  in std_logic;
    i_uds         :  in std_logic;
    i_addr        :  in std_logic_vector(1 downto 0);

    o_cs_duart    : out std_logic;
    o_cs_ramh     : out std_logic;
    o_cs_raml     : out std_logic;
    o_cs_romh     : out std_logic;
    o_cs_roml     : out std_logic;
    
    o_err         : out std_logic
);
end component;

-- input value instantiations
signal i_rw          : std_logic := '1';
signal i_lds         : std_logic := '1';
signal i_uds         : std_logic := '1';
signal i_addr        : std_logic_vector(1 downto 0) := (others => '0');

signal o_cs_roml     : std_logic;
signal o_cs_romh     : std_logic;
signal o_cs_raml     : std_logic;
signal o_cs_ramh     : std_logic;
signal o_cs_duart    : std_logic;
signal o_err         : std_logic;

signal test_clk      : std_logic;
constant test_clk_pd : time := 10 ns;

signal s_in          : unsigned(4 downto 0) := (others=>'0');
signal s_out         : unsigned(4 downto 0);

begin

-- Instantiate the Unit Under Test (UUT)
uut: entity work.AddressDecoder(complete) port map (
    i_rw       => i_rw,
    i_lds      => i_lds,
    i_uds      => i_uds,
    i_addr     => i_addr,
    o_cs_duart => o_cs_duart,
    o_cs_ramh  => o_cs_ramh,
    o_cs_raml  => o_cs_raml,
    o_cs_romh  => o_cs_romh,
    o_cs_roml  => o_cs_roml,
    o_err      => o_err
    );

test_clk_proc :process
begin
	--test_clk <= '0';
	--wait for test_clk_pd/2;
	--test_clk <= '1';
	--wait for test_clk_pd/2;
	wait;
    end process;

-- Stimulus process
stim_proc: process
begin
    while not(s_in = "11111") loop
    wait for test_clk_pd/4;
    wait for test_clk_pd/4;
    -- ==========  BEGIN AS TESTS  ==========

    -- ==========   END AS TESTS   ==========
    wait for test_clk_pd/4;
    wait for test_clk_pd/4;
    -- ========== BEGIN !AS TESTS ==========
    
    -- ==========  END !AS TESTS  ==========
    s_in <= s_in + 1;
    end loop;
wait;

end process;

i_rw       <= s_in(4);
i_addr(1)  <= s_in(3);
i_addr(0)  <= s_in(2);
i_uds      <= s_in(1);
i_lds      <= s_in(0);

s_out(4)   <= o_cs_duart;
s_out(3)   <= o_cs_ramh;
s_out(2)   <= o_cs_raml;
s_out(1)   <= o_cs_romh;
s_out(0)   <= o_cs_roml;

end;
