-- MCD SBC Project
-- Richard Homan
-- 03/28/2023
-- AddressRouter.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--      Reset circuit and debouncer bench
-- dependencies:
--      none

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity Reset_Bench is
end Reset_Bench;
 
architecture behavior of Reset_Bench is 
component Reset
port(
     i_clk : in  std_logic;
     i_rst : in  std_logic;
     o_hlt : out  std_logic
    );
end component;

--Inputs
signal i_clk : std_logic := '0';
signal i_rst : std_logic := '0';

	--Outputs
signal o_hlt : std_logic;

-- Clock period definitions
constant i_clk_period : time := 200 ns;
 
begin
    uut: Reset port map (
      i_clk => i_clk,
      i_rst => i_rst,
      o_hlt => o_hlt
    );

-- Clock process definitions
i_clk_process :process
begin
	i_clk <= '0';
	wait for i_clk_period/2;
	i_clk <= '1';
	wait for i_clk_period/2;
end process;


-- Stimulus process
stim_proc: process
begin
  i_rst <= '1';
    wait for 100 us;

  i_rst <= '0';
  -- insert stimulus here
    wait for i_clk_period*10;
  i_rst <= '1';
    wait for 800 us;
    i_rst <= '0';
  -- insert stimulus here
  wait for i_clk_period*10;
  i_rst <= '1';
  wait;
end process;

end;
