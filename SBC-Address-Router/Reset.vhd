-- MCD SBC Project
-- Richard Homan
-- 03/28/2023
-- AddressRouter.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Reset circuit and debouncer
-- dependencies:
--		none

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Reset is
port(
	i_clk :  in std_logic;
	i_rst :  in std_logic;

	o_hlt : out std_logic
);
end Reset;

architecture stock of Reset is
signal s_counter : unsigned(11 downto 0) := "000000000000";
signal s_rst_l   : std_logic := '1';
signal s_st_cnt  : std_logic := '1'; -- active low
signal s_hlt     : std_logic := '0';
begin

process(i_clk, i_rst)
begin
	if falling_edge(i_clk) then
		if i_rst = '0' then
			s_rst_l <= '0';
			s_hlt <= '0';
		else
			if s_counter(11) = '1' then
				s_rst_l <= '1';
				s_hlt <= 'Z';
			end if;
		end if;
	end if;
end process;

process(i_clk, s_rst_l)
begin
	if rising_edge(i_clk) then
		if s_rst_l = '0' then
			s_counter <= s_counter + 1;
		else
			s_counter <= "000000000000";
		end if;
	end if;
end process;

o_hlt    <= s_hlt;

end stock;

