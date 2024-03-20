
-- VHDL Instantiation Created from source file AddressDecoder.vhd -- 20:07:38 03/18/2024
--
-- Notes: 
-- 1) This instantiation template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the instantiated module
-- 2) To use this template to instantiate this entity, cut-and-paste and then edit

	COMPONENT AddressDecoder
	PORT(
		i_duart_dtack : IN std_logic;
		i_duart_irq : IN std_logic;
		i_rw : IN std_logic;
		i_lds : IN std_logic;
		i_uds : IN std_logic;
		i_as : IN std_logic;
		i_addr : IN std_logic_vector(7 downto 0);          
		o_oe : OUT std_logic;
		o_we : OUT std_logic;
		o_duart_rw : OUT std_logic;
		o_cs_roml : OUT std_logic;
		o_cs_romh : OUT std_logic;
		o_cs_raml : OUT std_logic;
		o_cs_ramh : OUT std_logic;
		o_cs_duart : OUT std_logic;
		o_duart_iack : OUT std_logic;
		o_berr : OUT std_logic
		);
	END COMPONENT;

	Inst_AddressDecoder: AddressDecoder PORT MAP(
		o_oe => ,
		o_we => ,
		o_duart_rw => ,
		o_cs_roml => ,
		o_cs_romh => ,
		o_cs_raml => ,
		o_cs_ramh => ,
		o_cs_duart => ,
		o_duart_iack => ,
		i_duart_dtack => ,
		i_duart_irq => ,
		i_rw => ,
		i_lds => ,
		i_uds => ,
		i_as => ,
		i_addr => ,
		o_berr => 
	);


