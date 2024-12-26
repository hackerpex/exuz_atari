
https://en.wikipedia.org/wiki/Atari_2600_hardware

O hardware do Atari 2600 foi baseado no chip MOS Technology 6507 , oferecendo uma resolução máxima de 160 x 192 pixels (NTSC), 128 cores, 128 bytes de RAM com 4 KB em cartuchos (64 KB via troca de banco). O design passou por muitas transformações e revisões durante sua história de produção de 14 anos, do "heavy sixer" original ao Atari 2600 Jr. no final. O sistema também tem muitos controladores e periféricos de terceiros.


https://alienbill.com/2600/101/docs/stella.html#tiaprog


Fluxo Correto de Execução
Carregar a ROM.
Executar instruções da CPU (6507).
Configurar os registradores do TIA.
Atualizar o framebuffer com base nos valores do TIA.
Renderizar o conteúdo na tela.
Repetir o ciclo para manter a execução contínua.


Atari 2600 - Mapas de Memória Típicos:
0x00 - 0x3F: TIA (Television Interface Adapter) - Controla gráficos e som.
0x40 - 0x7F: RIOT (RAM, I/O e Timer) - Entrada de controles (joysticks, switches).
0x80 - 0xFF: Espelhamento (Mirroring) ou RAM adicional.
0x1000 e acima: ROM (Programa principal)