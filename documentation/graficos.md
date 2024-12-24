1. O TIA (Television Interface Adapter) controla a geração da imagem, que é dividida em:

Playfield (Campo de Jogo):

Representa o fundo e objetos estáticos.
Largura de 40 bits e espelhamento horizontal.
Players (Jogadores):

Sprites controláveis, com largura de 8 pixels.
Missiles (Mísseis):

Objetos pequenos (1 pixel de largura) usados como projéteis.
Ball (Bola):

Objeto circular usado como elemento central em jogos como Pong.


2. Organização da Tela
160x192 pixels: Resolução padrão do Atari 2600.
Divisão em Scanlines: Cada linha é processada individualmente.
Sprites e Playfields: São desenhados linha por linha, exigindo controle preciso durante o ciclo de execução.


Interpretação dos Registradores do TIA
Principais Registradores:
Endereço	Registrador	Função
0x00	COLUP0	Cor do jogador 0.
0x01	COLUP1	Cor do jogador 1.
0x02	COLUPF	Cor do Playfield e da bola.
0x03	COLUBK	Cor de fundo.
0x04	CTRLPF	Controle do Playfield (espelhamento, prioridade).
0x05	REFP0	Reflete horizontalmente o jogador 0.
0x06	REFP1	Reflete horizontalmente o jogador 1.
0x07	PF0	Primeiro byte do Playfield (gráficos).
0x08	PF1	Segundo byte do Playfield.
0x09	PF2	Terceiro byte do Playfield.
0x0A	RESP0	Reseta a posição do jogador 0 (sincroniza horizontalmente).
0x0B	RESP1	Reseta a posição do jogador 1.
0x0C	RESM0	Reseta a posição do míssil 0.
