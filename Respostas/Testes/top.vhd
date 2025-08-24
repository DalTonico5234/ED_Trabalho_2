------------------------------------------------------------------------------------
---- Company: 
---- Engineer: 
---- 
---- Create Date: 21.08.2025 15:16:37
---- Design Name: 
---- Module Name: top - arch
---- Project Name: 
---- Target Devices: 
---- Tool Versions: 
---- Description: 
---- 
---- Dependencies: 
---- 
---- Revision:
---- Revision 0.01 - File Created
---- Additional Comments:
---- 
------------------------------------------------------------------------------------


--library IEEE;
--use IEEE.STD_LOGIC_1164.ALL;

---- Uncomment the following library declaration if using
---- arithmetic functions with Signed or Unsigned values
----use IEEE.NUMERIC_STD.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx leaf cells in this code.
----library UNISIM;
----use UNISIM.VComponents.all;

--entity top is
--    Port ( clk : in STD_LOGIC;
--           sw : in STD_LOGIC_VECTOR (0 downto 0);
--           btn : in STD_LOGIC_VECTOR (1 downto 0);
--           an : out STD_LOGIC_VECTOR (7 downto 0);
--           sseg : out STD_LOGIC_VECTOR (7 downto 0));
--end top;

--architecture arch of top is
--    signal tens_hex : STD_LOGIC_VECTOR (3 downto 0);
--    signal units_hex: STD_LOGIC_VECTOR (3 downto 0);
--    signal sseg1, sseg2: STD_LOGIC_VECTOR (7 downto 0);
--        signal btn_debounced : STD_LOGIC;

--begin

--    debounce_unit: entity work.db_fsm(arch)      
--         port map(
--                clk => clk,
--                reset => '0', -- O reset do debouncer não é necessário aqui, pois a FSM tem um estado inicial
--                sw => btn(0), -- Conecta o botão 0 à entrada do FSM
--                db => btn_debounced -- Conecta a saída debounced a um sinal interno
--            );
            
--        -- Instanciação do contador BCD
--        bcd_unity: entity work.bcd_counter(arch)
--            port map(
--            clk => clk,
--            reset => sw(0), -- Usa o SW(0) para resetar o contador
--            cont => btn_debounced, -- Usa o sinal debounced para a contagem
--            units_hex => units_hex,
--            tens_hex => tens_hex
--            );
    
--    hex_1: entity work.hex_to_sseg(arch)
--        port map(
--            hex => units_hex,
--            dp => '1',
--            sseg => sseg1
--        );

--    hex_2: entity work.hex_to_sseg(arch)
--        port map(
--            hex => tens_hex,
--            dp => '1',
--            sseg => sseg2
--        );
        
--    display: entity work.led_mux8(arch)
--        port map(
--             clk => clk,
--               reset => '0',
--               in1 => sseg2,
--               in0 => sseg1,
--               in2 => "01000000",
--               in3 => "01000000",
--               in4 => "01000000",
--               in5 => "01000000",
--               in6 => "01000000",
--               in7 => "01000000",
--               an => an,  -- Adicione esta linha
--               sseg => sseg -- Adicione esta linha
--        );
        
--end arch;


----------------------------------------------------------------------------------
-- Company:
-- Engineer:
--
-- Create Date: 21.08.2025 15:16:37
-- Design Name:
-- Module Name: top - arch
-- Project Name:
-- Target Devices:
-- Tool Versions:
-- Description:
--
-- Dependencies:
--
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Adicione a biblioteca numérica, pois o bcd_counter precisa dela
use IEEE.NUMERIC_STD.ALL;

entity top is
    Port ( clk : in STD_LOGIC;
           sw : in STD_LOGIC_VECTOR (0 downto 0);
           btn : in STD_LOGIC_VECTOR (1 downto 0);
           an : out STD_LOGIC_VECTOR (7 downto 0);
           sseg : out STD_LOGIC_VECTOR (7 downto 0));
end top;

architecture arch of top is
    -- Sinais internos para a lógica de contagem e display
    signal tens_hex : STD_LOGIC_VECTOR (3 downto 0);
    signal units_hex: STD_LOGIC_VECTOR (3 downto 0);
    signal sseg1, sseg2: STD_LOGIC_VECTOR (7 downto 0);
    
    -- Sinal para a saída debounced do botão de contagem
    signal btn_debounced : STD_LOGIC;
    
    -- Sinais para a detecção de borda
    signal btn_debounced_prev : STD_LOGIC;
    signal btn_tick : STD_LOGIC;

begin
    -- Instanciação do módulo de debounce
    debounce_unit: entity work.db_fsm(arch)      
         port map(
            clk => clk,
            reset => '0', 
            sw => btn(0), 
            db => btn_debounced -- Conecta a saída debounced a um sinal interno
         );
    
    -- Lógica de detecção de borda de subida (rising edge)
    -- Isso converte o sinal de nível (`btn_debounced`) em um pulso de um ciclo de clock
    process(clk)
    begin
        if rising_edge(clk) then
            -- Armazena o valor anterior do sinal debounced
            btn_debounced_prev <= btn_debounced;
        end if;
    end process;
    
    -- Gera um pulso '1' somente na borda de subida do sinal debounced
    btn_tick <= btn_debounced and not btn_debounced_prev;
    
    -- Instanciação do contador BCD [cite: 32]
    bcd_unity: entity work.bcd_counter(arch)
        port map(
        clk => clk,
        reset => sw(0),  
        cont => btn_tick, -- Usa o pulso de borda para a contagem
        units_hex => units_hex,
        tens_hex => tens_hex
        );
        
    hex_1: entity work.hex_to_sseg(arch)
        port map(
            hex => units_hex,
            dp => '1',
            sseg => sseg1
        );

    hex_2: entity work.hex_to_sseg(arch)
        port map(
            hex => tens_hex,
            dp => '1',
            sseg => sseg2
        );
    
    display: entity work.led_mux8(arch)
        port map(
            clk => clk,
            reset => '0',
            in1 => sseg2,
            in0 => sseg1,
            in2 => "01000000",
            in3 => "01000000",
            in4 => "01000000",
            in5 => "01000000",
            in6 => "01000000",
            in7 => "01000000",
            an => an,
            sseg => sseg
        );
    
end arch;