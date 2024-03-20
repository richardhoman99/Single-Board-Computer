-- MCD SBC Project
-- Richard Homan
-- 03/18/2023
-- AddressDecoder_Bench.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Test bench file for AddressDecoder.vhd
-- dependancies:
--		none

library ieee;
use ieee.std_logic_1164.all;
--use ieee.numeric_std.all;
 
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

    o_duart_iack  : out  std_logic;
    i_duart_dtack :  in  std_logic;
    i_duart_irq   :  in  std_logic;

    i_rw          :  in  std_logic;
    i_lds         :  in  std_logic;
    i_uds         :  in  std_logic;
    i_as          :  in  std_logic;

    i_addr        :  in  std_logic_vector(7 downto 0);

    o_berr        : out  std_logic
);
end component;
    
-- input value instantiations
signal i_duart_dtack : std_logic := '0';
signal i_duart_irq   : std_logic := '0';
signal i_rw          : std_logic := '0';
signal i_lds         : std_logic := '0';
signal i_uds         : std_logic := '0';
signal i_as          : std_logic := '0';
signal i_addr        : std_logic_vector(7 downto 0) := (others => '0');

signal o_oe          : std_logic;
signal o_we          : std_logic;
signal o_duart_rw    : std_logic;
signal o_cs_roml     : std_logic;
signal o_cs_romh     : std_logic;
signal o_cs_raml     : std_logic;
signal o_cs_ramh     : std_logic;
signal o_cs_duart    : std_logic;
signal o_duart_iack  : std_logic;
signal o_berr        : std_logic;

signal test_clk      : std_logic;
constant test_clk_period : time := 10 ns;

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
    o_duart_iack => o_duart_iack,
    i_duart_dtack => i_duart_dtack,
    i_duart_irq => i_duart_irq,
    i_rw => i_rw,
    i_lds => i_lds,
    i_uds => i_uds,
    i_as => i_as,
    i_addr => i_addr,
    o_berr => o_berr
);

test_clk_proc :process
begin
	test_clk <= '0';
	wait for test_clk_period/2;
	test_clk <= '1';
	wait for test_clk_period/2;
end process;

-- Stimulus process
stim_proc: process
begin		
  -- hold reset state for 100 ns.
  wait for 100 ns;	

  wait for test_clk_period*10;

  -- insert stimulus here 

  wait;
end process;

end;
