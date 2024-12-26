# sobre

Olá me chamo Rodrigo Camargo e sou um programador que gosta de aprender.
Como tive uma historia muito legal com os games criei um carinho especial por emuladores.
Decidir iniciar um projeto de emulador porém como não tenho muito conhecimento pensei que a melhor forma é iniciar po um console de arquitetura mais simples e depois ir subindo.

Este projeto tem também como objetivo motivar a outros programadores a se aventurarem am projetos de estudo.
Qualquer um pode fazer uso academico deste projeto mas o uso comercial é proibido.
O projeto é aberto e qualquer um pode contribuir.
O projeto é feito em C++ e utiliza a biblioteca SDL para a interface gráfica

licença
Este projeto é licenciado sob a licença propria.
Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
Aqui está a licença:
Copyright (c) 2023 Rodrigo Camargo
O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.



##  build on a mac with apple silicon

1. Configuração do Ambiente
Instalar Xcode Command Line Tools:
``` 
xcode-select --install
``` 
Instalar o Homebrew (se ainda não tiver):
``` 
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
``` 

Instalar Bibliotecas Necessárias:

``` 
brew install sdl2
brew install sdl2_ttf
brew install cmake
``` 


para que o comando make encontre as dependencias do sdl certifique de ter adicionado as variaveis de ambiente corretamente:

```
echo 'export CPATH=/opt/homebrew/include' >> ~/.zshrc
echo 'export LIBRARY_PATH=/opt/homebrew/lib' >> ~/.zshrc
source ~/.zshrc
``` 


# proximos passos


Implementar o Processador 6502:
- [ ] Emular a CPU MOS 6507 (uma versão simplificada do 6502)
- [ ] Suporte a instruções básicas e endereçamento

Memória e ROM:
  - [ ] Implementar mapeamento de memória
  - [ ] Carregamento de ROMs

Gráficos (TIA):
  - [ ] Processar os gráficos do Television Interface Adapter (TIA)

Entrada (Controles):
  - [ ] Emular os joysticks e switches

Som:
  - [ ] Usar a API de áudio do SDL2 para reproduzir sons